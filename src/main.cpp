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
        cout << "Warning: could not save users." << endl;
        return;
    }
    for (int i = 0; i < users.size(); i++) {
        file << users[i]->getRole() << "|" << users[i]->getUsername() << endl;
    }
    file.close();
}

// Load users from file (passwords are not stored for simplicity in this demo)
// In a real system, you would store hashed passwords
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

        // Default password same as username for demo
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
    cout << "\n--- Register ---" << endl;
    cout << "Enter username: ";
    string uname;
    cin >> uname;

    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getUsername() == uname) {
            cout << "Username already exists." << endl;
            return;
        }
    }

    cout << "Enter password: ";
    string pass;
    cin >> pass;

    cout << "Role (1=Customer, 2=Admin): ";
    int roleChoice;
    cin >> roleChoice;

    if (roleChoice == 2) {
        users.push_back(new Admin(uname, pass));
    } else {
        users.push_back(new Customer(uname, pass));
    }

    saveUsers();
    cout << "Registration successful." << endl;
}

// Login: returns pointer to User (runtime polymorphism)
User* login() {
    cout << "\n--- Login ---" << endl;
    cout << "Username: ";
    string uname;
    cin >> uname;
    cout << "Password: ";
    string pass;
    cin >> pass;

    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getUsername() == uname && users[i]->checkPassword(pass)) {
            cout << "Login successful. Welcome, " << uname << "!" << endl;
            return users[i];
        }
    }

    cout << "Invalid username or password." << endl;
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
    for (int i = 0; i < orders.size(); i++) {
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
    cout << "\n----- ALL ORDERS -----" << endl;
    if (orders.empty()) {
        cout << "No orders yet." << endl;
        return;
    }
    for (int i = 0; i < orders.size(); i++) {
        cout << "Order #" << orders[i].getOrderId()
             << " | Customer: " << orders[i].getCustomer()
             << " | Date: " << orders[i].getStatus()
             << " | Total: $" << fixed << setprecision(2) << orders[i].getTotal() << endl;
    }
}

// View customer orders
void viewMyOrders(string username) {
    cout << "\n----- MY ORDERS -----" << endl;
    bool found = false;
    for (int i = 0; i < orders.size(); i++) {
        if (orders[i].getCustomer() == username) {
            found = true;
            cout << "Order #" << orders[i].getOrderId()
                 << " | Date: " << orders[i].getStatus()
                 << " | Total: $" << fixed << setprecision(2) << orders[i].getTotal() << endl;
        }
    }
    if (!found) {
        cout << "No orders found." << endl;
    }
}

// Customer operations
void customerBrowse(Inventory& inv) {
    inv.displayAvailable();
}

void customerAddToCart(Cart& cart, Inventory& inv) {
    cout << "Enter Product ID: ";
    int pid;
    cin >> pid;
    cout << "Enter Quantity: ";
    int qty;
    cin >> qty;

    try {
        cart.addItem(pid, qty, inv);
    } catch (ShopException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void customerRemoveFromCart(Cart& cart) {
    cout << "Enter Product ID to remove: ";
    int pid;
    cin >> pid;
    try {
        cart.removeItem(pid);
    } catch (ShopException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void customerCheckout(Cart& cart, Inventory& inv, string username) {
    if (cart.isEmpty()) {
        cout << "Cart is empty." << endl;
        return;
    }

    cart.viewCart(inv);
    cout << "\nConfirm checkout? (1=Yes, 0=No): ";
    int confirm;
    cin >> confirm;
    if (confirm != 1) {
        cout << "Checkout cancelled." << endl;
        return;
    }

    // Deduct stock
    vector<CartItem> items = cart.getItems();
    for (int i = 0; i < items.size(); i++) {
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
    cout << "Order placed successfully! Order #" << newOrder.getOrderId() << endl;
}

// Admin operations
void adminAddProduct(Inventory& inv) {
    cin.ignore();
    cout << "Enter product name: ";
    string name;
    getline(cin, name);
    cout << "Enter description: ";
    string desc;
    getline(cin, desc);
    cout << "Enter price: ";
    double price;
    cin >> price;
    cout << "Enter stock quantity: ";
    int qty;
    cin >> qty;

    Product p(inv.getNextId(), name, desc, price, qty);
    inv.addProduct(p);
    cout << "Product added with ID: " << p.getId() << endl;
}

void adminUpdateStock(Inventory& inv) {
    cout << "Enter Product ID: ";
    int pid;
    cin >> pid;
    Product* p = inv.findProduct(pid);
    if (p == NULL) {
        cout << "Product not found." << endl;
        return;
    }
    cout << "Enter new stock quantity: ";
    int qty;
    cin >> qty;
    p->setStock(qty);
    inv.saveToFile();
    cout << "Stock updated." << endl;
}

void adminDeleteProduct(Inventory& inv) {
    cout << "Enter Product ID to delete: ";
    int pid;
    cin >> pid;
    try {
        inv.deleteProduct(pid);
        cout << "Product deleted." << endl;
    } catch (ShopException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    Inventory inventory("data/products.txt");
    Cart cart;

    loadUsers();
    loadOrders();

    if (users.empty()) {
        // Create default admin
        users.push_back(new Admin("admin", "admin"));
        saveUsers();
    }

    cout << "=================================" << endl;
    cout << "  ONLINE SHOP & INVENTORY SYSTEM" << endl;
    cout << "=================================" << endl;

    User* currentUser = NULL;
    bool running = true;

    while (running) {
        if (currentUser == NULL) {
            cout << "\n1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "0. Exit" << endl;
            cout << "Choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                currentUser = login();
            } else if (choice == 2) {
                registerUser(inventory);
            } else if (choice == 0) {
                running = false;
            } else {
                cout << "Invalid choice." << endl;
            }
        } else {
            // Runtime polymorphism: base pointer calls derived class function
            currentUser->displayMenu();
            cout << "Choice: ";
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
                } else {
                    cout << "Invalid choice." << endl;
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
                } else {
                    cout << "Invalid choice." << endl;
                }
            }
        }
    }

    // Cleanup
    for (int i = 0; i < users.size(); i++) {
        delete users[i];
    }
    users.clear();

    cout << "Goodbye!" << endl;
    return 0;
}
