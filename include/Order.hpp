#ifndef ORDER_HPP
#define ORDER_HPP

#include <vector>
#include <string>
#include "Cart.hpp"

class Order {
private:
    int orderId;
    string customerUsername;
    string orderDate;
    double totalAmount;
    string status;
    vector<CartItem> items;
public:
    Order();
    Order(int oid, string user, string date, double total, string stat, vector<CartItem> its);

    int getOrderId() const;
    string getCustomer() const;
    double getTotal() const;
    string getStatus() const;
    vector<CartItem> getItems() const;

    string toFileString() const;
    static Order fromFileString(string line);
};

#endif
