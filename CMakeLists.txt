cmake_minimum_required(VERSION 3.16)
project(InventoryManagement)

set(CMAKE_CXX_STANDARD 17)

add_executable(InventoryManagement
        main.cpp
        csv.h
        avl_map.h
        hashmap.h
        LinkedList.h
        utils.h
        InventoryItem.h
        TestHashMap.h
)