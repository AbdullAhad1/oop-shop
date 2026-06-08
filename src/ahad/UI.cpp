#include "../../include/UI.hpp"
#include <iostream>

using namespace std;

void UI::clearScreen() {
    cout << "\n\n\n\n\n\n\n\n\n\n";
}

void UI::header(string title) {
    cout << "\n===== " << title << " =====" << endl;
}

void UI::separator() {
    cout << "==========================" << endl;
}

void UI::prompt(string text) {
    cout << text << ": ";
}

void UI::success(string text) {
    cout << "[OK] " << text << endl;
}

void UI::error(string text) {
    cout << "[ERROR] " << text << endl;
}

void UI::info(string text) {
    cout << "[INFO] " << text << endl;
}

string UI::inputString(string label) {
    prompt(label);
    string val;
    cin >> val;
    return val;
}

int UI::inputInt(string label) {
    prompt(label);
    int val;
    cin >> val;
    return val;
}

double UI::inputDouble(string label) {
    prompt(label);
    double val;
    cin >> val;
    return val;
}
