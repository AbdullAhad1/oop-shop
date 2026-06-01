#include "../include/Inventory.hpp"
#include "../include/ShopException.hpp"
#include <fstream>
#include <iostream>

Inventory::Inventory(string fname) {
    filename = fname;
    nextProductId = 1;
    loadFromFile();
}

void Inventory::loadFromFile() {
    products.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Product p = Product::fromFileString(line);
        // Skip invalid products (id == 0 means parsing failed)
        if (p.getId() == 0) continue;
        products.push_back(p);
        if (p.getId() >= nextProductId) {
            nextProductId = p.getId() + 1;
        }
    }
    file.close();
}

void Inventory::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) {
        throw ShopException("Cannot open file for writing.");
    }
    for (size_t i = 0; i < products.size(); i++) {
        file << products[i].toFileString() << endl;
    }
    file.close();
}

void Inventory::addProduct(Product p) {
    products.push_back(p);
    saveToFile();
}

void Inventory::updateProduct(int id, Product p) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            products[i] = p;
            saveToFile();
            return;
        }
    }
    throw ShopException("Product not found for update.");
}

void Inventory::deleteProduct(int id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            products.erase(products.begin() + i);
            saveToFile();
            return;
        }
    }
    throw ShopException("Product not found for deletion.");
}

Product* Inventory::findProduct(int id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == id) {
            return &products[i];
        }
    }
    return NULL;
}

void Inventory::displayAll() const {
    cout << "\n----- ALL PRODUCTS -----" << endl;
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }
    for (size_t i = 0; i < products.size(); i++) {
        cout << "ID: " << products[i].getId()
             << " | Name: " << products[i].getName()
             << " | Price: $" << products[i].getPrice()
             << " | Stock: " << products[i].getStock() << endl;
        cout << "   Desc: " << products[i].getDescription() << endl;
    }
}

void Inventory::displayAvailable() const {
    cout << "\n----- AVAILABLE PRODUCTS -----" << endl;
    bool any = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getStock() > 0) {
            any = true;
            cout << "ID: " << products[i].getId()
                 << " | Name: " << products[i].getName()
                 << " | Price: $" << products[i].getPrice()
                 << " | Stock: " << products[i].getStock() << endl;
            cout << "   Desc: " << products[i].getDescription() << endl;
        }
    }
    if (!any) {
        cout << "No products in stock." << endl;
    }
}

vector<Product> Inventory::getProducts() const {
    return products;
}

int Inventory::getNextId() {
    return nextProductId++;
}
