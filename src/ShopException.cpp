#include "../include/ShopException.hpp"

ShopException::ShopException(string msg) {
    message = msg;
}

ShopException::~ShopException() throw() {
}

const char* ShopException::what() const throw() {
    return message.c_str();
}
