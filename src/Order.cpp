#include "../include/Order.hpp"

Order::Order(int oid, string user, double total, vector<CartItem> its) {
    orderId = oid;
    customerUsername = user;
    totalAmount = total;
    items = its;
}
