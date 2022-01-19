#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"
#include "profile.h"

#include <algorithm>
#include <iostream>
#include <numeric>

vector<string_view> SplitIntoWords(string_view line) {
    return SplitBy(line, ' ');
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void UpdateIndex(istream &document_input, Synchronized<InvertedIndex> &index) {
    InvertedIndex new_index;
    new_index.Add(document_input);
    swap(index.GetAccess().ref_to_value, new_index);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    if (index.GetAccess().ref_to_value.GetDocumentCount() == 0){
        UpdateIndex(document_input, index);
    } else {
        async_tasks.push_back(async(UpdateIndex, ref(document_input), ref(index)));
    }
}

void InvertedIndex::Add(istream &document_input) {
    for (string document; getline(document_input, document);) {
//        if (!document.empty()) {
            docs.push_back(move(document));
            const size_t docid = docs.size() - 1;
            map<string_view, size_t> word_count;
            for (string_view &word: SplitIntoWords(docs.back())) {
                if (!word.empty()) {
                    ++word_count[word];
                }
            }
            for (auto &[word, count]: word_count) {
                index[word].push_back({docid, count});
            }
//        }
    }
}

void RunQuery(istream &query_input, ostream &search_results_output, Synchronized<InvertedIndex> &index) {
    vector<size_t> docid_count;
    vector<int64_t> docids;
    docid_count.reserve(50000);
    docids.reserve(50000);
    for (string current_query; getline(query_input, current_query);) {
//        if (!current_query.empty()) {
            const auto words = SplitIntoWords(current_query);
            {
                auto access = index.GetAccess();
                const size_t size = access.ref_to_value.GetDocumentCount();
                docid_count.assign(size, 0);
                docids.resize(size);
                auto &idx = access.ref_to_value;
                for (const auto &word: words) {
                    if (!word.empty()){
                        for (const auto &[docid, hitcount]: idx.Lookup(word)) {
                            docid_count[docid] += hitcount;
                        }
                    }
                }
            }

            iota(docids.begin(), docids.end(), 0);
            {
                partial_sort(
                        begin(docids),
                        end(Head(docids, 5)),
                        end(docids),
                        [&docid_count](int64_t lhs, int64_t rhs) {
                            return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
                        }
                );
            }
            search_results_output << current_query << ':';
            for (auto docid: Head(docids, 5)) {
                if (docid_count[docid] == 0) {
                    break;
                }
                search_results_output << " {"
                                      << "docid: " << docid << ", "
                                      << "hitcount: " << docid_count[docid] << '}';
            }
            search_results_output << '\n';
//        }
    }
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
) {
    while (index.GetAccess().ref_to_value.GetDocumentCount() == 0){}
    async_tasks.push_back(async(RunQuery, ref(query_input), ref(search_results_output), ref(index)));
}

const vector<pair<size_t, size_t>> &InvertedIndex::Lookup(string_view word) const {
    static vector<pair<size_t, size_t>> empty;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty;
    }
}
