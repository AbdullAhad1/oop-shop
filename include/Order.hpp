#ifndef ORDER_HPP
#define ORDER_HPP

#include <vector>
#include <string>
#include "Cart.hpp"

class Order {
private:
    int orderId;
    string customerUsername;
    double totalAmount;
    vector<CartItem> items;
public:
    Order(int oid, string user, double total, vector<CartItem> its);

    int getOrderId() const { return orderId; }
    string getCustomer() const { return customerUsername; }
    double getTotal() const { return totalAmount; }
    vector<CartItem> getItems() const { return items; }
};

#endif
