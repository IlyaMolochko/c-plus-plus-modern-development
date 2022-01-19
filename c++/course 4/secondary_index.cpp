#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

// Реализуйте этот класс
class Database {
public:
    bool Put(const Record& record) {
        auto [it, result] = data.insert({record.id, Data{record, {}, {}, {}}});

        if (!result){
            return false;
        }

        Record *pointer = &it->second.record;
        it->second.timestamp_iter = timestamp_index.insert({record.timestamp, pointer});
        it->second.karma_iter = karma_index.insert({record.karma, pointer});
        it->second.user_iter = user_index.insert({record.user, pointer});
        return true;
    }

    const Record* GetById(const string& id) const {
        auto it = data.find(id);
        if (it != data.end()){
            return &it->second.record;
        }
        return nullptr;
    }

    bool Erase(const string& id) {
        auto it = data.find(id);
        if (it != data.end()){
            timestamp_index.erase(it->second.timestamp_iter);
            karma_index.erase(it->second.karma_iter);
            user_index.erase(it->second.user_iter);
            data.erase(it);
            return true;
        }
        return false;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        for (auto it = timestamp_index.lower_bound(low); it != timestamp_index.end() and it->first <= high; ++it){
            if (!callback(*it->second)){
                break;
            }
        }
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        for (auto it = karma_index.lower_bound(low); it != karma_index.end() and it->first <= high; ++it){
            if (!callback(*it->second)){
                break;
            }
        }
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        for (auto it = user_index.find(user); it != user_index.end() and it->first == user; ++it){
            if (!callback(*it->second)){
                break;
            }
        }
    }

private:
    struct Data{
        Record record;
        multimap<int, const Record*>::iterator timestamp_iter;
        multimap<int, const Record*>::iterator karma_iter;
        multimap<string, const Record*>::iterator user_iter;
    };

    unordered_map<string, Data> data;
    multimap<int, const Record*> timestamp_index;
    multimap<int, const Record*> karma_index;
    multimap<string, const Record*> user_index;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

struct st{
    int s;
    int e;
    int p;
};

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}