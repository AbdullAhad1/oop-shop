#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "User.hpp"

class Customer : public User {
public:
    Customer(string u, string p);
    void displayMenu() const;
    string getRole() const;
};

#endif
