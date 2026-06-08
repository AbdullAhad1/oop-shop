#ifndef CART_HPP
#define CART_HPP

#include <vector>
#include "Product.hpp"
#include "Inventory.hpp"

struct CartItem {
    int productId;
    int quantity;
};

class Cart {
private:
    vector<CartItem> items;
public:
    void addItem(int pid, int qty, Inventory& inv);
    void removeItem(int pid);
    void clear() { items.clear(); }
    void viewCart(Inventory& inv);
    double getTotal(Inventory& inv);
    vector<CartItem> getItems() { return items; }
    bool isEmpty() { return items.empty(); }
};

#endif
