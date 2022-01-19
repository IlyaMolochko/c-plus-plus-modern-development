#pragma once

#include "synchronized.h"

#include <deque>
#include <future>
#include <istream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>


using namespace std;

class InvertedIndex {
public:
    InvertedIndex() = default;
    void Add(istream& document_input);
    const vector<pair<size_t, size_t>>& Lookup(string_view word) const;

    const list<string>& GetDocuments() const {
        return docs;
    }

//    const string& GetDocument(size_t id) const {
//        return docs[id];
//    }

    size_t GetDocumentCount() const {
        return docs.size();
    }

private:
    map<string_view, vector<pair<size_t, size_t>>> index;
    list<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    Synchronized<InvertedIndex> index;
    vector<future<void>> async_tasks;
};
