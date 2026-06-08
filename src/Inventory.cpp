#include "../include/Inventory.hpp"
#include <fstream>
#include <iostream>

Inventory::Inventory(string fname) {
    filename = fname;
    nextId = 1;
    ifstream file(filename.c_str());
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Product p = Product::fromFileString(line);
        if (p.getId() == 0) continue;
        products.push_back(p);
        if (p.getId() >= nextId) nextId = p.getId() + 1;
    }
    file.close();
}

void Inventory::saveToFile() {
    ofstream file(filename.c_str());
    for (size_t i = 0; i < products.size(); i++) {
        file << products[i].toFileString() << endl;
    }
    file.close();
}

void Inventory::addProduct(string n, string d, double p, int qty) {
    products.push_back(Product(nextId++, n, d, p, qty));
    saveToFile();
}

void Inventory::deleteProduct(int id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            products.erase(products.begin() + i);
            saveToFile();
            return;
        }
    }
}

void Inventory::updateStock(int id, int qty) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            products[i].setStock(qty);
            saveToFile();
            return;
        }
    }
}

Product* Inventory::findProduct(int id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            return &products[i];
        }
    }
    return NULL;
}

void Inventory::displayAll() {
    cout << "\n===== ALL PRODUCTS =====" << endl;
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }
    for (size_t i = 0; i < products.size(); i++) {
        cout << "ID: " << products[i].getId()
             << " | " << products[i].getName()
             << " | $" << products[i].getPrice()
             << " | Stock: " << products[i].getStock() << endl;
    }
}

void Inventory::displayAvailable() {
    cout << "\n===== AVAILABLE PRODUCTS =====" << endl;
    bool any = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getStock() > 0) {
            any = true;
            cout << "ID: " << products[i].getId()
                 << " | " << products[i].getName()
                 << " | $" << products[i].getPrice()
                 << " | Stock: " << products[i].getStock() << endl;
        }
    }
    if (!any) cout << "No products in stock." << endl;
}
