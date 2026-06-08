#ifndef USER_HPP
#define USER_HPP

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
public:
    User(string u, string p);
    virtual ~User();

    string getUsername() const;
    bool checkPassword(string p) const;

    virtual void displayMenu() const = 0;
    virtual string getRole() const = 0;
};

#endif
