#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <string>
#include "Product.hpp"

class Inventory {
private:
    vector<Product> products;
    string filename;
    int nextProductId;
public:
    Inventory(string fname);

    void loadFromFile();
    void saveToFile();

    void addProduct(Product p);
    void updateProduct(int id, Product p);
    void deleteProduct(int id);
    Product* findProduct(int id);
    void displayAll() const;
    void displayAvailable() const;
    vector<Product> getProducts() const;
    int getNextId();
};

#endif
