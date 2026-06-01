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
    void updateQuantity(int pid, int qty, Inventory& inv);
    void clear();
    void viewCart(Inventory& inv) const;
    double getTotal(Inventory& inv) const;
    vector<CartItem> getItems() const;
    bool isEmpty() const;
};

#endif
