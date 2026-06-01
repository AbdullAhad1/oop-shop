#include "../include/Customer.hpp"
#include <iostream>

Customer::Customer(string u, string p) : User(u, p) {}

void Customer::displayMenu() const {
    cout << "\n===== CUSTOMER MENU =====" << endl;
    cout << "1. Browse Products" << endl;
    cout << "2. View Cart" << endl;
    cout << "3. Add to Cart" << endl;
    cout << "4. Remove from Cart" << endl;
    cout << "5. Checkout" << endl;
    cout << "6. My Orders" << endl;
    cout << "0. Logout" << endl;
}

string Customer::getRole() const {
    return "customer";
}
