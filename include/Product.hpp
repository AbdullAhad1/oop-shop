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
    Product();
    Product(int id, string n, string d, double p, int qty);

    int getId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    int getStock() const;

    void setName(string n);
    void setDescription(string d);
    void setPrice(double p);
    void setStock(int qty);

    void reduceStock(int qty);

    string toFileString() const;
    static Product fromFileString(string line);
};

#endif
