#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

#include "../include/User.hpp"
#include "../include/Customer.hpp"
#include "../include/Admin.hpp"
#include "../include/Product.hpp"
#include "../include/Inventory.hpp"
#include "../include/Cart.hpp"
#include "../include/Order.hpp"
#include "../include/UI.hpp"

using namespace std;

vector<User*> users;
vector<Order> orders;
int nextOrderId = 1;

// ===== File helpers =====
void saveUsers() {
    ofstream file("data/users.txt");
    for (int i = 0; i < (int)users.size(); i++) {
        file << users[i]->getRole() << "|" << users[i]->getUsername() << endl;
    }
    file.close();
}

void loadUsers() {
    ifstream file("data/users.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t pos = line.find('|');
        string role = line.substr(0, pos);
        string uname = line.substr(pos + 1);
        if (role == "admin") users.push_back(new Admin(uname, uname));
        else users.push_back(new Customer(uname, uname));
    }
    file.close();
}

void saveOrders() {
    ofstream file("data/orders.txt");
    for (int i = 0; i < (int)orders.size(); i++) {
        file << orders[i].getOrderId() << "|" << orders[i].getCustomer()
             << "|" << orders[i].getTotal();
        vector<CartItem> its = orders[i].getItems();
        for (int j = 0; j < (int)its.size(); j++) {
            file << "|" << its[j].productId << ":" << its[j].quantity;
        }
        file << endl;
    }
    file.close();
}

void loadOrders() {
    ifstream file("data/orders.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string oidStr, user, totalStr;
        getline(ss, oidStr, '|');
        getline(ss, user, '|');
        getline(ss, totalStr, '|');

        int oid = stoi(oidStr);
        double total = stod(totalStr);
        vector<CartItem> its;
        string pair;
        while (getline(ss, pair, '|')) {
            size_t col = pair.find(':');
            CartItem ci;
            ci.productId = stoi(pair.substr(0, col));
            ci.quantity = stoi(pair.substr(col + 1));
            its.push_back(ci);
        }
        orders.push_back(Order(oid, user, total, its));
        if (oid >= nextOrderId) nextOrderId = oid + 1;
    }
    file.close();
}

// ===== Auth =====
User* login() {
    UI::header("LOGIN");
    string uname = UI::inputString("Username");
    string pass = UI::inputString("Password");
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i]->getUsername() == uname && users[i]->checkPassword(pass)) {
            UI::success("Welcome, " + uname + "!");
            return users[i];
        }
    }
    UI::error("Invalid username or password.");
    return NULL;
}

void registerUser() {
    UI::header("REGISTER");
    string uname = UI::inputString("Username");
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i]->getUsername() == uname) {
            UI::error("Username already exists.");
            return;
        }
    }
    string pass = UI::inputString("Password");
    UI::info("1. Customer  2. Admin");
    int roleChoice = UI::inputInt("Role");
    if (roleChoice == 2) users.push_back(new Admin(uname, pass));
    else users.push_back(new Customer(uname, pass));
    saveUsers();
    UI::success("Registration successful.");
}

// ===== Order display =====
void viewAllOrders() {
    UI::header("ALL ORDERS");
    if (orders.empty()) { UI::info("No orders yet."); return; }
    for (int i = 0; i < (int)orders.size(); i++) {
        cout << "Order#" << orders[i].getOrderId()
             << " | Customer: " << orders[i].getCustomer()
             << " | Total: $" << orders[i].getTotal() << endl;
    }
}

void viewMyOrders(string username) {
    UI::header("MY ORDERS");
    bool found = false;
    for (int i = 0; i < (int)orders.size(); i++) {
        if (orders[i].getCustomer() == username) {
            found = true;
            cout << "Order#" << orders[i].getOrderId()
                 << " | Total: $" << orders[i].getTotal() << endl;
        }
    }
    if (!found) UI::info("No orders found.");
}

// ===== Main =====
int main() {
    Inventory inventory("data/products.txt");
    Cart cart;

    loadUsers();
    loadOrders();

    if (users.empty()) {
        users.push_back(new Admin("admin", "admin"));
        saveUsers();
    }

    UI::clearScreen();
    UI::header("ONLINE SHOP");

    User* currentUser = NULL;
    bool running = true;

    while (running) {
        if (currentUser == NULL) {
            cout << "\n===== WELCOME =====" << endl;
            cout << "1. Customer Portal" << endl;
            cout << "2. Admin Portal" << endl;
            cout << "0. Exit" << endl;

            int portalChoice = UI::inputInt("Choice");

            if (portalChoice == 1) {
                bool inPortal = true;
                while (inPortal) {
                    cout << "\n===== CUSTOMER PORTAL =====" << endl;
                    cout << "1. Login" << endl;
                    cout << "2. Register" << endl;
                    cout << "0. Back" << endl;
                    int c = UI::inputInt("Choice");

                    if (c == 1) {
                        currentUser = login();
                        if (currentUser != NULL) {
                            if (currentUser->getRole() != "customer") {
                                UI::error("Not a customer account.");
                                currentUser = NULL;
                            } else inPortal = false;
                        }
                    } else if (c == 2) {
                        registerUser();
                    } else if (c == 0) {
                        inPortal = false;
                    } else UI::error("Invalid choice.");
                }
            } else if (portalChoice == 2) {
                currentUser = login();
                if (currentUser != NULL) {
                    if (currentUser->getRole() != "admin") {
                        UI::error("Not an admin account.");
                        currentUser = NULL;
                    }
                }
            } else if (portalChoice == 0) {
                running = false;
            } else UI::error("Invalid choice.");
        } else {
            currentUser->displayMenu();
            int choice = UI::inputInt("Choice");

            string role = currentUser->getRole();
            if (role == "customer") {
                if (choice == 1) inventory.displayAvailable();
                else if (choice == 2) cart.viewCart(inventory);
                else if (choice == 3)
                    cart.addItem(UI::inputInt("Product ID"), UI::inputInt("Quantity"), inventory);
                else if (choice == 4) {
                    cart.removeItem(UI::inputInt("Product ID to remove"));
                } else if (choice == 5) {
                    if (cart.isEmpty()) UI::error("Cart is empty.");
                    else {
                        cart.viewCart(inventory);
                        int confirm = UI::inputInt("Confirm checkout? (1=Yes, 0=No)");
                        if (confirm == 1) {
                            vector<CartItem> items = cart.getItems();
                            for (int i = 0; i < (int)items.size(); i++) {
                                Product* p = inventory.findProduct(items[i].productId);
                                if (p != NULL) p->reduceStock(items[i].quantity);
                            }
                            inventory.saveToFile();
                            double total = cart.getTotal(inventory);
                            orders.push_back(Order(nextOrderId++, currentUser->getUsername(), total, items));
                            saveOrders();
                            cart.clear();
                            UI::success("Order placed! Order #" + to_string(orders.back().getOrderId()));
                        } else UI::info("Checkout cancelled.");
                    }
                } else if (choice == 6) viewMyOrders(currentUser->getUsername());
                else if (choice == 0) currentUser = NULL;
                else UI::error("Invalid choice.");
            } else if (role == "admin") {
                if (choice == 1) inventory.displayAll();
                else if (choice == 2) {
                    UI::header("ADD PRODUCT");
                    string name = UI::inputString("Name");
                    string desc = UI::inputString("Description");
                    double price = UI::inputDouble("Price");
                    int qty = UI::inputInt("Stock");
                    inventory.addProduct(name, desc, price, qty);
                    UI::success("Product added.");
                } else if (choice == 3) {
                    UI::header("UPDATE STOCK");
                    int pid = UI::inputInt("Product ID");
                    int qty = UI::inputInt("New quantity");
                    inventory.updateStock(pid, qty);
                } else if (choice == 4) {
                    UI::header("DELETE PRODUCT");
                    inventory.deleteProduct(UI::inputInt("Product ID"));
                } else if (choice == 5) viewAllOrders();
                else if (choice == 0) currentUser = NULL;
                else UI::error("Invalid choice.");
            }

            if (currentUser != NULL) {
                cout << "\nPress Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
    }

    for (int i = 0; i < (int)users.size(); i++) {
        delete users[i];
    }
    users.clear();

    cout << "\nGoodbye!" << endl;
    return 0;
}
