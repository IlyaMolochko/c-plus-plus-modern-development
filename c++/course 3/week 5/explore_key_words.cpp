#include "test_runner.h"
#include "profile.h"

#include <fstream>
#include <future>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats &other) {
        for (auto &[word, frequence] : other.word_frequences) {
            word_frequences[word] += frequence;
        }
    }
};

//Stats ExploreLine(const set<string> &key_words,
//                  const string &line) {
//    stringstream ss(line);
//    string word;
//    Stats stats;
//    while (ss >> ws >> word) {
//        if (key_words.count(word)) {
//            ++stats.word_frequences[word];
//        }
//    }
//    return stats;
//}

Stats ExploreLine(const set<string> &key_words,
                  const string &line) {
    stringstream ss(line);
    string word;
    Stats stats;
    while (getline(ss, word, ' ')) {
        if (key_words.count(word)) {
            ++stats.word_frequences[word];
        }
    }
    return stats;
}

Stats ExploreKeyWordsSingleThread(
        const set<string> &key_words, istream &input
) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
    LogDuration("ExploreKeyWords");
    vector<future<Stats>> futures;
    size_t string_number = 0;
    size_t number_of_threads = thread::hardware_concurrency();
    vector<stringstream> streams(number_of_threads);
    string line;

    while (getline(input, line)) {
        streams[string_number % number_of_threads] << line << '\n';
        ++string_number;
    }

    futures.reserve(streams.size());
    for (auto &s : streams) {
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(s)));
    }
    Stats stats;
    for (auto &f : futures){
        stats += f.get();
    }
    return stats;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks",  2},
            {"sucks",  1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}