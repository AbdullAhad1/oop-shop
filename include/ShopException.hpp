#ifndef SHOPEXCEPTION_HPP
#define SHOPEXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

class ShopException : public exception {
private:
    string message;
public:
    ShopException(string msg);
    ~ShopException() throw();
    const char* what() const throw();
};

#endif
