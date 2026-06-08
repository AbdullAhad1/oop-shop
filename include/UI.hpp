#ifndef UI_HPP
#define UI_HPP

#include <string>
using namespace std;

namespace UI {
    void clearScreen();
    void header(string title);
    void separator();
    void prompt(string text);
    void success(string text);
    void error(string text);
    void info(string text);

    string inputString(string label);
    int inputInt(string label);
    double inputDouble(string label);
}

#endif
