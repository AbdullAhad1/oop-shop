#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../include/User.hpp"
#include "../include/Customer.hpp"
#include "../include/Admin.hpp"
#include "../include/Product.hpp"
#include "../include/Inventory.hpp"
#include "../include/Cart.hpp"
#include "../include/Order.hpp"
#include "../include/ShopException.hpp"
#include "../include/UI.hpp"

using namespace std;

vector<User*> users;
vector<Order> orders;
int nextOrderId = 1;
string usersFile = "data/users.txt";
string ordersFile = "data/orders.txt";

// Save users to file
void saveUsers() {
    ofstream file(usersFile);
    if (!file.is_open()) {
        UI::drawWarning("Could not save users.");
        return;
    }
    for (int i = 0; i < (int)users.size(); i++) {
        file << users[i]->getRole() << "|" << users[i]->getUsername() << endl;
    }
    file.close();
}

// Load users from file
void loadUsers() {
    ifstream file(usersFile);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string role, uname;
        getline(ss, role, '|');
        getline(ss, uname, '|');

        if (role == "admin") {
            users.push_back(new Admin(uname, uname));
        } else {
            users.push_back(new Customer(uname, uname));
        }
    }
    file.close();
}

// Register a new user
void registerUser(Inventory& inv) {
    UI::drawHeader("REGISTER NEW USER");

    string uname = UI::inputString("Username");

    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i]->getUsername() == uname) {
            UI::drawError("Username already exists.");
            return;
        }
    }

    string pass = UI::inputString("Password");

    UI::drawSubHeader("SELECT ACCOUNT TYPE");
    UI::drawMenuItem(1, "Customer  -- Browse, Buy, Order");
    UI::drawMenuItem(2, "Admin     -- Manage Stock, View Orders");
    int roleChoice = UI::inputInt("Role");

    if (roleChoice == 2) {
        users.push_back(new Admin(uname, pass));
    } else {
        users.push_back(new Customer(uname, pass));
    }

    saveUsers();
    UI::drawSuccess("Registration successful.");
}

// Login: returns pointer to User (runtime polymorphism)
User* login() {
    UI::drawHeader("LOGIN");

    string uname = UI::inputString("Username");
    string pass = UI::inputString("Password");

    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i]->getUsername() == uname && users[i]->checkPassword(pass)) {
            UI::drawSuccess("Welcome, " + uname + "!");
            return users[i];
        }
    }

    UI::drawError("Invalid username or password.");
    return NULL;
}

// Get current date string
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << 1 + ltm->tm_mon << "-"
       << ltm->tm_mday;
    return ss.str();
}

// Save orders to file
void saveOrders() {
    ofstream file(ordersFile);
    if (!file.is_open()) return;
    for (int i = 0; i < (int)orders.size(); i++) {
        file << orders[i].toFileString() << endl;
    }
    file.close();
}

// Load orders from file
void loadOrders() {
    ifstream file(ordersFile);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Order o = Order::fromFileString(line);
        orders.push_back(o);
        if (o.getOrderId() >= nextOrderId) {
            nextOrderId = o.getOrderId() + 1;
        }
    }
    file.close();
}

// View all orders (admin)
void viewAllOrders() {
    UI::drawHeader("ALL ORDERS");
    if (orders.empty()) {
        UI::drawInfo("No orders yet.");
        return;
    }
    UI::drawTableHeader("Order#", "Customer", "Date", "Total");
    for (int i = 0; i < (int)orders.size(); i++) {
        stringstream ss;
        ss << fixed << setprecision(2) << orders[i].getTotal();
        UI::drawTableRow(
            to_string(orders[i].getOrderId()),
            orders[i].getCustomer(),
            orders[i].getStatus(),
            "$" + ss.str()
        );
    }
}

// View customer orders
void viewMyOrders(string username) {
    UI::drawHeader("MY ORDERS");
    bool found = false;
    for (int i = 0; i < (int)orders.size(); i++) {
        if (orders[i].getCustomer() == username) {
            found = true;
            stringstream ss;
            ss << fixed << setprecision(2) << orders[i].getTotal();
            UI::drawTableRow(
                to_string(orders[i].getOrderId()),
                orders[i].getStatus(),
                "$" + ss.str()
            );
        }
    }
    if (!found) {
        UI::drawInfo("No orders found.");
    }
}

// Customer operations
void customerBrowse(Inventory& inv) {
    UI::drawHeader("AVAILABLE PRODUCTS");
    inv.displayAvailable();
}

void customerAddToCart(Cart& cart, Inventory& inv) {
    UI::drawHeader("ADD TO CART");
    int pid = UI::inputInt("Product ID");
    int qty = UI::inputInt("Quantity");

    try {
        cart.addItem(pid, qty, inv);
    } catch (ShopException& e) {
        UI::drawError(e.what());
    }
}

void customerRemoveFromCart(Cart& cart) {
    UI::drawHeader("REMOVE FROM CART");
    int pid = UI::inputInt("Product ID to remove");
    try {
        cart.removeItem(pid);
    } catch (ShopException& e) {
        UI::drawError(e.what());
    }
}

void customerCheckout(Cart& cart, Inventory& inv, string username) {
    UI::drawHeader("CHECKOUT");
    if (cart.isEmpty()) {
        UI::drawWarning("Cart is empty.");
        return;
    }

    cart.viewCart(inv);
    UI::drawPrompt("Confirm checkout? (1=Yes, 0=No)");
    int confirm;
    cin >> confirm;
    if (confirm != 1) {
        UI::drawInfo("Checkout cancelled.");
        return;
    }

    // Deduct stock
    vector<CartItem> items = cart.getItems();
    for (int i = 0; i < (int)items.size(); i++) {
        Product* p = inv.findProduct(items[i].productId);
        if (p != NULL) {
            p->reduceStock(items[i].quantity);
        }
    }
    inv.saveToFile();

    // Create order
    double total = cart.getTotal(inv);
    string date = getCurrentDate();
    Order newOrder(nextOrderId++, username, date, total, date, items);
    orders.push_back(newOrder);
    saveOrders();

    cart.clear();
    UI::drawSuccess("Order placed! Order #" + to_string(newOrder.getOrderId()));
}

// Admin operations
void adminAddProduct(Inventory& inv) {
    UI::drawHeader("ADD NEW PRODUCT");
    cin.ignore();
    UI::drawPrompt("Product name");
    string name;
    getline(cin, name);
    UI::drawPrompt("Description");
    string desc;
    getline(cin, desc);
    double price = UI::inputDouble("Price");
    int qty = UI::inputInt("Stock quantity");

    Product p(inv.getNextId(), name, desc, price, qty);
    inv.addProduct(p);
    UI::drawSuccess("Product added with ID: " + to_string(p.getId()));
}

void adminUpdateStock(Inventory& inv) {
    UI::drawHeader("UPDATE STOCK");
    int pid = UI::inputInt("Product ID");
    Product* p = inv.findProduct(pid);
    if (p == NULL) {
        UI::drawError("Product not found.");
        return;
    }
    int qty = UI::inputInt("New stock quantity");
    p->setStock(qty);
    inv.saveToFile();
    UI::drawSuccess("Stock updated.");
}

void adminDeleteProduct(Inventory& inv) {
    UI::drawHeader("DELETE PRODUCT");
    int pid = UI::inputInt("Product ID to delete");
    try {
        inv.deleteProduct(pid);
        UI::drawSuccess("Product deleted.");
    } catch (ShopException& e) {
        UI::drawError(e.what());
    }
}

// Main entry
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
    UI::drawLogo();
    UI::drawBanner("ONLINE SHOP & INVENTORY SYSTEM");

    User* currentUser = NULL;
    bool running = true;

    while (running) {
        if (currentUser == NULL) {
            UI::drawPortalMenu();
            UI::drawPrompt("Choice");
            int portalChoice;
            cin >> portalChoice;

            if (portalChoice == 1) {
                // CUSTOMER PORTAL
                bool inCustomerPortal = true;
                while (inCustomerPortal) {
                    UI::drawHeader("CUSTOMER PORTAL");
                    UI::drawCustomerPortal();
                    UI::drawPrompt("Choice");
                    int cChoice;
                    cin >> cChoice;

                    if (cChoice == 1) {
                        currentUser = login();
                        if (currentUser != NULL) {
                            if (currentUser->getRole() != "customer") {
                                UI::drawError("This account is not a Customer account.");
                                currentUser = NULL;
                            } else {
                                UI::drawBanner("WELCOME, " + currentUser->getUsername());
                                inCustomerPortal = false;
                            }
                        }
                    } else if (cChoice == 2) {
                        registerUser(inventory);
                    } else if (cChoice == 0) {
                        inCustomerPortal = false;
                    } else {
                        UI::drawError("Invalid choice.");
                    }
                }
            } else if (portalChoice == 2) {
                // ADMIN PORTAL - login only
                UI::drawHeader("ADMIN PORTAL");
                currentUser = login();
                if (currentUser != NULL) {
                    if (currentUser->getRole() != "admin") {
                        UI::drawError("This account is not an Admin account.");
                        currentUser = NULL;
                    } else {
                        UI::drawBanner("WELCOME, " + currentUser->getUsername());
                    }
                }
            } else if (portalChoice == 0) {
                running = false;
            } else {
                UI::drawError("Invalid choice.");
            }
        } else {
            // Runtime polymorphism: base pointer calls derived class function
            UI::clearScreen();
            UI::drawSmallLogo();
            currentUser->displayMenu();
            UI::drawSeparator('=');

            UI::drawPrompt("Choice");
            int choice;
            cin >> choice;

            string role = currentUser->getRole();

            if (role == "customer") {
                if (choice == 1) {
                    customerBrowse(inventory);
                } else if (choice == 2) {
                    cart.viewCart(inventory);
                } else if (choice == 3) {
                    customerAddToCart(cart, inventory);
                } else if (choice == 4) {
                    customerRemoveFromCart(cart);
                } else if (choice == 5) {
                    customerCheckout(cart, inventory, currentUser->getUsername());
                } else if (choice == 6) {
                    viewMyOrders(currentUser->getUsername());
                } else if (choice == 0) {
                    currentUser = NULL;
                    UI::clearScreen();
                    UI::drawLogo();
                    UI::drawBanner("ONLINE SHOP & INVENTORY SYSTEM");
                } else {
                    UI::drawError("Invalid choice.");
                }
            } else if (role == "admin") {
                if (choice == 1) {
                    inventory.displayAll();
                } else if (choice == 2) {
                    adminAddProduct(inventory);
                } else if (choice == 3) {
                    adminUpdateStock(inventory);
                } else if (choice == 4) {
                    adminDeleteProduct(inventory);
                } else if (choice == 5) {
                    viewAllOrders();
                } else if (choice == 0) {
                    currentUser = NULL;
                    UI::clearScreen();
                    UI::drawLogo();
                    UI::drawBanner("ONLINE SHOP & INVENTORY SYSTEM");
                } else {
                    UI::drawError("Invalid choice.");
                }
            }

            if (currentUser != NULL) {
                UI::drawThinSeparator('-');
                UI::drawInfo("Press Enter to continue...");
                cin.ignore();
                cin.get();
            }
        }
    }

    // Cleanup
    for (int i = 0; i < (int)users.size(); i++) {
        delete users[i];
    }
    users.clear();

    UI::clearScreen();
    UI::drawBanner("GOODBYE!");
    return 0;
}
