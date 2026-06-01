#include "../include/Cart.hpp"
#include "../include/ShopException.hpp"
#include <iostream>
#include <iomanip>

void Cart::addItem(int pid, int qty, Inventory& inv) {
    if (qty <= 0) {
        throw ShopException("Quantity must be greater than zero.");
    }

    Product* p = inv.findProduct(pid);
    if (p == NULL) {
        throw ShopException("Product not found.");
    }
    if (p->getStock() < qty) {
        throw ShopException("Not enough stock available.");
    }

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].productId == pid) {
            items[i].quantity += qty;
            return;
        }
    }

    CartItem item;
    item.productId = pid;
    item.quantity = qty;
    items.push_back(item);
}

void Cart::removeItem(int pid) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].productId == pid) {
            items.erase(items.begin() + i);
            return;
        }
    }
    throw ShopException("Product not in cart.");
}

void Cart::updateQuantity(int pid, int qty, Inventory& inv) {
    if (qty <= 0) {
        removeItem(pid);
        return;
    }

    Product* p = inv.findProduct(pid);
    if (p == NULL) {
        throw ShopException("Product not found.");
    }
    if (p->getStock() < qty) {
        throw ShopException("Not enough stock available.");
    }

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].productId == pid) {
            items[i].quantity = qty;
            return;
        }
    }
    throw ShopException("Product not in cart.");
}

void Cart::clear() {
    items.clear();
}

void Cart::viewCart(Inventory& inv) const {
    if (items.empty()) {
        cout << "Cart is empty." << endl;
        return;
    }

    cout << "\n----- YOUR CART -----" << endl;
    double total = 0;
    for (size_t i = 0; i < items.size(); i++) {
        Product* p = inv.findProduct(items[i].productId);
        if (p != NULL) {
            double subtotal = p->getPrice() * items[i].quantity;
            total += subtotal;
            cout << "ID: " << items[i].productId
                 << " | " << p->getName()
                 << " | Qty: " << items[i].quantity
                 << " | Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
        }
    }
    cout << "TOTAL: $" << fixed << setprecision(2) << total << endl;
}

double Cart::getTotal(Inventory& inv) const {
    double total = 0;
    for (size_t i = 0; i < items.size(); i++) {
        Product* p = inv.findProduct(items[i].productId);
        if (p != NULL) {
            total += p->getPrice() * items[i].quantity;
        }
    }
    return total;
}

vector<CartItem> Cart::getItems() const {
    return items;
}

bool Cart::isEmpty() const {
    return items.empty();
}
