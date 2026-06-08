#include "../include/Cart.hpp"
#include <iostream>
using namespace std;

void Cart::addItem(int pid, int qty, Inventory& inv) {
    if (qty <= 0) { cout << "Quantity must be > 0." << endl; return; }
    Product* p = inv.findProduct(pid);
    if (p == NULL) { cout << "Product not found." << endl; return; }
    if (p->getStock() < qty) { cout << "Not enough stock." << endl; return; }
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].productId == pid) { items[i].quantity += qty; return; }
    }
    CartItem item; item.productId = pid; item.quantity = qty;
    items.push_back(item);
    cout << "Added to cart." << endl;
}

void Cart::removeItem(int pid) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].productId == pid) {
            items.erase(items.begin() + i);
            cout << "Removed from cart." << endl;
            return;
        }
    }
    cout << "Product not in cart." << endl;
}

void Cart::viewCart(Inventory& inv) {
    if (items.empty()) { cout << "Cart is empty." << endl; return; }
    cout << "\n===== YOUR CART =====" << endl;
    double total = 0;
    for (size_t i = 0; i < items.size(); i++) {
        Product* p = inv.findProduct(items[i].productId);
        if (p != NULL) {
            double sub = p->getPrice() * items[i].quantity;
            total += sub;
            cout << items[i].productId << " | " << p->getName()
                 << " | Qty: " << items[i].quantity
                 << " | $" << sub << endl;
        }
    }
    cout << "TOTAL: $" << total << endl;
}

double Cart::getTotal(Inventory& inv) {
    double total = 0;
    for (size_t i = 0; i < items.size(); i++) {
        Product* p = inv.findProduct(items[i].productId);
        if (p != NULL) total += p->getPrice() * items[i].quantity;
    }
    return total;
}
