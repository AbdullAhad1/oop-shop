#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <string>
#include "Product.hpp"

class Inventory {
private:
    vector<Product> products;
    string filename;
    int nextId;
public:
    Inventory(string fname);

    void addProduct(string n, string d, double p, int qty);
    void deleteProduct(int id);
    void updateStock(int id, int qty);
    Product* findProduct(int id);
    void displayAll();
    void displayAvailable();
    int getNextId() { return nextId++; }
    void saveToFile();
};

#endif
