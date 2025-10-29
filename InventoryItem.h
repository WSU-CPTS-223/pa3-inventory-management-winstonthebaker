//
// Created by winstonthebaker on 10/28/25.
//

#ifndef INVENTORYMANAGEMENT_INVENTORYITEM_H
#define INVENTORYMANAGEMENT_INVENTORYITEM_H
#include <string>
#include <iostream>
using std::ostream;
using std::string;
using std::cout;
using std::endl;

struct InventoryItem {
    string data[28];
    InventoryItem() {
        for (auto & i : data) {
            i = "";
        }
    }
    InventoryItem(const InventoryItem& other) {
        for (int i = 0; i < 28; i++) {
            data[i] = other.data[i];
        }
    }
    InventoryItem& operator=(const InventoryItem& other) {
        if (this != &other) {
            for (int i = 0; i < 28; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    InventoryItem(InventoryItem&& other) noexcept{
        for (int i = 0; i < 28; i++) {
            data[i] = other.data[i];
        }
    }
    InventoryItem& operator=(InventoryItem&& other) noexcept{
        if (this != &other) {
            for (int i = 0; i < 28; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& os, const InventoryItem& item) {

        os << "Uniq Id: " << item.data[0] << endl;
        os << "Product Name: " << item.data[1] << endl;
        os << "Brand Name: " << item.data[2] << endl;
        os << "Asin: " << item.data[3] << endl;
        os << "Category: " << item.data[4] << endl;
        os << "Upc Ean Code: " << item.data[5] << endl;
        os << "List Price: " << item.data[6] << endl;
        os << "Selling Price: " << item.data[7] << endl;
        os << "Quantity: " << item.data[8] << endl;
        os << "Model Number: " << item.data[9] << endl;
        os << "About Product: " << item.data[10] << endl;
        os << "Product Specification: " << item.data[11] << endl;
        os << "Technical Details: " << item.data[12] << endl;
        os << "Shipping Weight: " << item.data[13] << endl;
        os << "Product Dimensions: " << item.data[14] << endl;
        os << "Image: " << item.data[15] << endl;
        os << "Variants: " << item.data[16] << endl;
        os << "Sku: " << item.data[17] << endl;
        os << "Product Url: " << item.data[18] << endl;
        os << "Stock: " << item.data[19] << endl;
        os << "Product Details: " << item.data[20] << endl;
        os << "Dimensions: " << item.data[21] << endl;
        os << "Color: " << item.data[22] << endl;
        os << "Ingredients: " << item.data[23] << endl;
        os << "Direction To Use: " << item.data[24] << endl;
        os << "Is Amazon Seller: " << item.data[25] << endl;
        os << "Size Quantity Variant: " << item.data[26] << endl;
        os << "Product Description: " << item.data[27] << endl;
        return os;
    }

};
#endif //INVENTORYMANAGEMENT_INVENTORYITEM_H