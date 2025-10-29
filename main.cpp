#include <iostream>
#include <map>
#include <string>
#include "csv.h"
#include "LinkedList.h"
#include "avl_map.h"
#include "utils.h"
#include "hashmap.h"
#include "InventoryItem.h"
//#include "TestHashMap.h"

using namespace std;
AVLTree<string, LinkedList<string>> tagTree;
HashMap<string, InventoryItem> inventoryMap;
void printHelp() {
    cout << "Supported list of commands: " << endl;
    cout <<
            " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'."
            << endl;
    cout <<
            " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
            << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(const string& line) {
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(const string& line) {
    if (line == ":help") {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0) {
        size_t pos = line.rfind("find", 0);
        string searchTerm = trim(line.substr(pos + 4));

        InventoryItem* item = inventoryMap.find(searchTerm);
        cout << "Searching for: " << searchTerm  << endl;
        if (item) {
            cout << "Inventory found!" << endl;
            cout << *item << endl;
        }

    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0) {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        size_t pos = line.rfind("listInventory", 0);
        string category = trim(line.substr(pos + 13));
        AVLTree<string, LinkedList<string>>::iterator it = tagTree.find(category);
        if (it == tagTree.end()) {
            cout << "Invalid Category" << endl;
        }else {
            cout << "Inventory found!" << endl;
            for (auto & it2 : (*it).second) {

                cout <<"Unique ID: " << it2 << endl;
                const string& searchTerm = it2;
                if (InventoryItem* item = inventoryMap.find(searchTerm)) {
                    cout << "Name: "  << item->data[1] << endl;
                }
                cout.flush();
            }
        }

    }
}



void bootStrap() {
    io::CSVReader<28, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'> > in("../inventory.csv");

    in.read_header(io::ignore_extra_column,
                   "Uniq Id",
                   "Product Name",
                   "Brand Name",
                   "Asin",
                   "Category",
                   "Upc Ean Code",
                   "List Price",
                   "Selling Price",
                   "Quantity",
                   "Model Number",
                   "About Product",
                   "Product Specification",
                   "Technical Details",
                   "Shipping Weight",
                   "Product Dimensions",
                   "Image",
                   "Variants",
                   "Sku",
                   "Product Url",
                   "Stock",
                   "Product Details",
                   "Dimensions",
                   "Color",
                   "Ingredients",
                   "Direction To Use",
                   "Is Amazon Seller",
                   "Size Quantity Variant",
                   "Product Description");

    string cols[28];
 //stupid
    while (in.read_row(
        cols[0],
        cols[1],
        cols[2],
        cols[3],
        cols[4],
        cols[5],
        cols[6],
        cols[7],
        cols[8],
        cols[9],
        cols[10],
        cols[11],
        cols[12],
        cols[13],
        cols[14],
        cols[15],
        cols[16],
        cols[17],
        cols[18],
        cols[19],
        cols[20],
        cols[21],
        cols[22],
        cols[23],
        cols[24],
        cols[25],
        cols[26],
        cols[27]
    )) {
        //insert into map
        InventoryItem item;
        for (int i = 0; i < 28; i++) {
            item.data[i] = cols[i];
        }
        inventoryMap.insert(cols[0], item);


        //insert into category tree
        string category;
        if (cols[4].empty()) {
            continue;
        }
        for (int i = 0; i < cols[4].size(); i++) {
            if (cols[4][i] != '|') {
                category.push_back(cols[4][i]);
            } else {
                category = trim(category);
                tagTree[category].insert_front(cols[0]);
                category.clear();
            }
        }
        category = trim(category);
        tagTree[category].insert_front(cols[0]);
        category.clear();
    }
    // for (AVLTree<string, LinkedList<string>>::iterator it = tagTree.begin(); it != tagTree.end(); ++it) {
    //        cout << (*it).first << ": ";
    //     for (LinkedList<string>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2) {
    //         cout << (*it2) << ", ";
    //     }
    //     cout << endl;
    // }


    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
}

int main(int argc, char const *argv[]) {

    //TestHashMap::testAll();

    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit") {
        if (validCommand(line)) {
            evalCommand(line);
        } else {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
