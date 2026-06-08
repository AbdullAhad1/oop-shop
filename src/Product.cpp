#include "../include/Product.hpp"
#include <sstream>

Product::Product(int id, string n, string d, double p, int qty) {
    productId = id;
    name = n;
    description = d;
    price = p;
    stockQuantity = qty;
}

string Product::toFileString() {
    stringstream ss;
    ss << productId << "|" << name << "|" << description
       << "|" << price << "|" << stockQuantity;
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
        return Product(0, "", "", 0, 0);
    }
    return Product(id, n, d, p, q);
}
