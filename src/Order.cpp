#include "../include/Order.hpp"
#include <sstream>
#include <iomanip>

Order::Order() {
    orderId = 0;
    customerUsername = "";
    orderDate = "";
    totalAmount = 0.0;
    status = "pending";
}

Order::Order(int oid, string user, string date, double total, string stat, vector<CartItem> its) {
    orderId = oid;
    customerUsername = user;
    orderDate = date;
    totalAmount = total;
    status = stat;
    items = its;
}

int Order::getOrderId() const { return orderId; }
string Order::getCustomer() const { return customerUsername; }
double Order::getTotal() const { return totalAmount; }
string Order::getStatus() const { return status; }
vector<CartItem> Order::getItems() const { return items; }

string Order::toFileString() const {
    stringstream ss;
    ss << orderId << "|" << customerUsername << "|" << orderDate << "|"
       << fixed << setprecision(2) << totalAmount << "|" << status;

    ss << "|";
    for (int i = 0; i < items.size(); i++) {
        if (i > 0) ss << ",";
        ss << items[i].productId << ":" << items[i].quantity;
    }
    return ss.str();
}

Order Order::fromFileString(string line) {
    stringstream ss(line);
    string oidStr, user, date, totalStr, stat, itemStr;
    getline(ss, oidStr, '|');
    getline(ss, user, '|');
    getline(ss, date, '|');
    getline(ss, totalStr, '|');
    getline(ss, stat, '|');
    getline(ss, itemStr, '|');

    int oid = stoi(oidStr);
    double total = stod(totalStr);

    vector<CartItem> its;
    stringstream itemSS(itemStr);
    string pair;
    while (getline(itemSS, pair, ',')) {
        stringstream ps(pair);
        string pidStr, qtyStr;
        getline(ps, pidStr, ':');
        getline(ps, qtyStr, ':');
        CartItem ci;
        ci.productId = stoi(pidStr);
        ci.quantity = stoi(qtyStr);
        its.push_back(ci);
    }

    return Order(oid, user, date, total, stat, its);
}
