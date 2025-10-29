//
// Created by winstonthebaker on 10/28/25.
//

#ifndef INVENTORYMANAGEMENT_TESTHASHMAP_H
#define INVENTORYMANAGEMENT_TESTHASHMAP_H
#include <iostream>
#include <cassert>
#include <string>
#include "hashmap.h"

using namespace std;
namespace TestHashMap {
    inline void test_insert() {
        HashMap<string, int> map;

        // Normal case: insert one key-value pair
        map.insert("apple", 10);
        assert(*map.find("apple") == 10);

        // Edge case: insert duplicate key should overwrite value
        map.insert("apple", 20);
        assert(*map.find("apple") == 20);
    }

    inline void test_find() {
        HashMap<string, int> map;
        map.insert("banana", 5);

        // Normal case: find existing key
        int* val = map.find("banana");
        assert(val && *val == 5);

        // Edge case: find non-existing key should return nullptr
        assert(map.find("grape") == nullptr);
    }

    inline void test_erase() {
        HashMap<string, int> map;
        map.insert("cat", 1);
        map.insert("dog", 2);

        // Normal case: erase existing key
        bool erased = map.erase("cat");
        assert(erased && map.find("cat") == nullptr);

        // Edge case: erase non-existing key should return false
        assert(map.erase("lion") == false);
    }

    inline void test_clear() {
        HashMap<string, int> map;
        map.insert("x", 10);
        map.insert("y", 20);

        // Normal case: clear removes all elements
        map.clear();
        assert(map.find("x") == nullptr && map.find("y") == nullptr);

        // Edge case: calling clear() on empty table is safe
        map.clear();
        assert(map.find("x") == nullptr);
    }

    inline void test_rehash() {
        HashMap<int, int> map;

        // Normal case: trigger rehash by inserting many items
        for (int i = 0; i < 20; ++i) map.insert(i, i * 2);
        for (int i = 0; i < 20; ++i) {
            int* val = map.find(i);
            assert(val && *val == i * 2);
        }

        // Edge case: rehash empty table shouldn't crash or change count
        HashMap<int, int> emptyMap;
        size_t before = emptyMap.size();
        emptyMap.rehash();
        assert(emptyMap.size() == before);
    }

    inline void testAll() {
        test_insert();
        test_find();
        test_erase();
        test_clear();
        test_rehash();

        cout << "✅ All HashMap tests passed successfully!\n";
    }
}


#endif //INVENTORYMANAGEMENT_TESTHASHMAP_H