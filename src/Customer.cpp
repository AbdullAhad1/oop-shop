#include "../include/Customer.hpp"
#include "../include/UI.hpp"
#include <iostream>

Customer::Customer(string u, string p) : User(u, p) {}

void Customer::displayMenu() const {
    UI::drawHeader("CUSTOMER MENU");
    UI::drawMenuItem(1, "Browse Products");
    UI::drawMenuItem(2, "View Cart");
    UI::drawMenuItem(3, "Add to Cart");
    UI::drawMenuItem(4, "Remove from Cart");
    UI::drawMenuItem(5, "Checkout");
    UI::drawMenuItem(6, "My Orders");
    UI::drawMenuItem(0, "Logout");
}

string Customer::getRole() const {
    return "customer";
}
