#include "../include/Product.hpp"
#include <sstream>

Product::Product() {
    productId = 0;
    name = "";
    description = "";
    price = 0.0;
    stockQuantity = 0;
}

Product::Product(int id, string n, string d, double p, int qty) {
    productId = id;
    name = n;
    description = d;
    price = p;
    stockQuantity = qty;
}

int Product::getId() const { return productId; }
string Product::getName() const { return name; }
string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stockQuantity; }

void Product::setName(string n) { name = n; }
void Product::setDescription(string d) { description = d; }
void Product::setPrice(double p) { price = p; }
void Product::setStock(int qty) { stockQuantity = qty; }

void Product::reduceStock(int qty) {
    stockQuantity -= qty;
}

string Product::toFileString() const {
    stringstream ss;
    ss << productId << "|" << name << "|" << description << "|" << price << "|" << stockQuantity;
    return ss.str();
}

Product Product::fromFileString(string line) {
    stringstream ss(line);
    string idStr, n, d, pStr, qStr;
    getline(ss, idStr, '|');
    getline(ss, n, '|');
    getline(ss, d, '|');
    getline(ss, pStr, '|');
    getline(ss, qStr, '|');

    int id = 0;
    double p = 0.0;
    int q = 0;

    try {
        id = stoi(idStr);
        p = stod(pStr);
        q = stoi(qStr);
    } catch (...) {
        // Return default product if parsing fails
        return Product();
    }

    return Product(id, n, d, p, q);
}
