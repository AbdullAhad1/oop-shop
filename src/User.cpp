#include "../include/User.hpp"

User::User(string u, string p) {
    username = u;
    password = p;
}

User::~User() {}

string User::getUsername() const {
    return username;
}

bool User::checkPassword(string p) const {
    return password == p;
}
