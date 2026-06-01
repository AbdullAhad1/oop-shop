#include "../include/Admin.hpp"
#include "../include/UI.hpp"
#include <iostream>

Admin::Admin(string u, string p) : User(u, p) {}

void Admin::displayMenu() const {
    UI::drawHeader("ADMIN MENU");
    UI::drawMenuItem(1, "View All Products");
    UI::drawMenuItem(2, "Add New Product");
    UI::drawMenuItem(3, "Update Product Stock");
    UI::drawMenuItem(4, "Delete Product");
    UI::drawMenuItem(5, "View All Orders");
    UI::drawMenuItem(0, "Logout");
}

string Admin::getRole() const {
    return "admin";
}
