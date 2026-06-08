#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
using namespace std;

class Product {
private:
    int productId;
    string name;
    string description;
    double price;
    int stockQuantity;
public:
    Product(int id, string n, string d, double p, int qty);

    int getId() const { return productId; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    int getStock() const { return stockQuantity; }

    void setStock(int qty) { stockQuantity = qty; }
    void reduceStock(int qty) { stockQuantity -= qty; }

    string toFileString();
    static Product fromFileString(string line);
};

#endif
