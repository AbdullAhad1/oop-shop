#include "../include/Admin.hpp"
#include <iostream>

Admin::Admin(string u, string p) : User(u, p) {}

void Admin::displayMenu() const {
    cout << "\n===== ADMIN MENU =====" << endl;
    cout << "1. View All Products" << endl;
    cout << "2. Add New Product" << endl;
    cout << "3. Update Product Stock" << endl;
    cout << "4. Delete Product" << endl;
    cout << "5. View All Orders" << endl;
    cout << "0. Logout" << endl;
}

string Admin::getRole() const {
    return "admin";
}
