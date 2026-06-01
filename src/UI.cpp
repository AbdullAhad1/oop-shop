#include "../include/UI.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace UI {

    const string RESET      = "\033[0m";
    const string BOLD       = "\033[1m";
    const string DIM        = "\033[2m";
    const string ITALIC     = "\033[3m";
    const string UNDERLINE  = "\033[4m";

    const string BLACK      = "\033[30m";
    const string RED        = "\033[31m";
    const string GREEN      = "\033[32m";
    const string YELLOW     = "\033[33m";
    const string BLUE       = "\033[34m";
    const string MAGENTA    = "\033[35m";
    const string CYAN       = "\033[36m";
    const string WHITE      = "\033[37m";

    const string BG_BLACK   = "\033[40m";
    const string BG_RED     = "\033[41m";
    const string BG_GREEN   = "\033[42m";
    const string BG_YELLOW  = "\033[43m";
    const string BG_BLUE    = "\033[44m";
    const string BG_MAGENTA = "\033[45m";
    const string BG_CYAN    = "\033[46m";
    const string BG_WHITE   = "\033[47m";

    const string GOLD       = "\033[38;5;220m";   // Bright gold
    const string ORANGE     = "\033[38;5;208m";   // Orange
    const string DARK_GOLD  = "\033[38;5;136m";   // Darker gold

    const char* HORIZONTAL  = "\u2500";
    const char* VERTICAL    = "\u2502";
    const char* TOP_LEFT    = "\u250C";
    const char* TOP_RIGHT   = "\u2510";
    const char* BOTTOM_LEFT = "\u2514";
    const char* BOTTOM_RIGHT= "\u2518";
    const char* T_LEFT      = "\u251C";
    const char* T_RIGHT     = "\u2524";
    const char* T_TOP       = "\u252C";
    const char* T_BOTTOM    = "\u2534";
    const char* CROSS       = "\u253C";

    void clearScreen() {
        cout << "\033[2J\033[H";
    }

    void setTitle(string title) {
        cout << "\033]0;" << title << "\007";
    }

    void drawBox(int x, int y, int w, int h) {
        // Simplified: just print border lines
        // Full cursor positioning would need ANSI escape sequences
    }

    void drawHorizontalLine(int x, int y, int w) {
        for (int i = 0; i < w; i++) {
            cout << HORIZONTAL;
        }
    }

    void drawVerticalLine(int x, int y, int h) {
        for (int i = 0; i < h; i++) {
            cout << VERTICAL << endl;
        }
    }

    void printAt(int x, int y, string text) {
        cout << "\033[" << y << ";" << x << "H" << text;
    }

    void drawHeader(string title) {
        int width = 60;
        cout << endl;
        cout << GOLD;
        cout << TOP_LEFT;
        for (int i = 0; i < width; i++) cout << HORIZONTAL;
        cout << TOP_RIGHT << endl;

        cout << VERTICAL;
        int padding = (width - title.length()) / 2;
        for (int i = 0; i < padding; i++) cout << " ";
        cout << BOLD << WHITE << title << RESET << GOLD;
        for (int i = 0; i < width - padding - (int)title.length(); i++) cout << " ";
        cout << VERTICAL << endl;

        cout << T_LEFT;
        for (int i = 0; i < width; i++) cout << HORIZONTAL;
        cout << T_RIGHT << RESET << endl;
    }

    void drawSubHeader(string text) {
        cout << GOLD << "  " << BOLD << text << RESET << endl;
    }

    void drawSeparator(char c) {
        cout << GOLD;
        for (int i = 0; i < 62; i++) cout << c;
        cout << RESET << endl;
    }

    void drawThinSeparator(char c) {
        cout << DIM;
        for (int i = 0; i < 62; i++) cout << c;
        cout << RESET << endl;
    }

    void drawMenuItem(int num, string label) {
        cout << "  " << GOLD << "[" << BOLD << num << RESET << GOLD << "]" << RESET
             << "  " << label << endl;
    }

    void drawMenuItem(int num, string label, string shortcut) {
        cout << "  " << GOLD << "[" << BOLD << num << RESET << GOLD << "]" << RESET
             << "  " << left << setw(35) << label
             << DIM << "  " << shortcut << RESET << endl;
    }

    void drawStatusBar(string left, string center, string right) {
        cout << endl;
        cout << BG_BLACK << GOLD;
        cout << " " << left;
        int pad = 58 - left.length() - center.length() - right.length();
        for (int i = 0; i < pad / 2; i++) cout << " ";
        cout << center;
        for (int i = 0; i < pad - pad / 2; i++) cout << " ";
        cout << right << " ";
        cout << RESET << endl;
    }

    void drawPrompt(string text) {
        cout << endl << GOLD << " \u25B6 " << RESET << text << " ";
    }

    void drawSuccess(string text) {
        cout << "  " << GREEN << "\u2714 " << RESET << text << endl;
    }

    void drawError(string text) {
        cout << "  " << RED << "\u2718 " << RESET << text << endl;
    }

    void drawWarning(string text) {
        cout << "  " << ORANGE << "\u26A0 " << RESET << text << endl;
    }

    void drawInfo(string text) {
        cout << "  " << CYAN << "\u2139 " << RESET << text << endl;
    }

    void drawBanner(string text) {
        cout << endl;
        cout << GOLD << BOLD;
        cout << "\u2554";
        for (int i = 0; i < 58; i++) cout << "\u2550";
        cout << "\u2557" << endl;

        cout << "\u2551";
        int pad = (58 - text.length()) / 2;
        for (int i = 0; i < pad; i++) cout << " ";
        cout << WHITE << text;
        for (int i = 0; i < 58 - pad - (int)text.length(); i++) cout << " ";
        cout << GOLD << "\u2551" << endl;

        cout << "\u255A";
        for (int i = 0; i < 58; i++) cout << "\u2550";
        cout << "\u255D" << RESET;
        cout << endl;
    }

    void drawTableHeader(string col1, string col2, string col3) {
        cout << endl;
        cout << GOLD << "  " << left << setw(8) << col1
             << setw(25) << col2
             << setw(15) << col3
             << RESET << endl;
        cout << DIM;
        for (int i = 0; i < 60; i++) cout << "-";
        cout << RESET << endl;
    }

    void drawTableHeader(string col1, string col2, string col3, string col4) {
        cout << endl;
        cout << GOLD << "  " << left << setw(8) << col1
             << setw(20) << col2
             << setw(15) << col3
             << setw(12) << col4
             << RESET << endl;
        cout << DIM;
        for (int i = 0; i < 60; i++) cout << "-";
        cout << RESET << endl;
    }

    void drawTableRow(string col1, string col2, string col3) {
        cout << "  " << left << setw(8) << col1
             << setw(25) << col2
             << setw(15) << col3
             << endl;
    }

    void drawTableRow(string col1, string col2, string col3, string col4) {
        cout << "  " << left << setw(8) << col1
             << setw(25) << col2
             << setw(12) << col3
             << setw(12) << col4
             << endl;
    }

    void drawProductCard(int id, string name, string desc, double price, int stock) {
        cout << endl;
        cout << GOLD << "  \u250C";
        for (int i = 0; i < 50; i++) cout << "\u2500";
        cout << "\u2510" << RESET << endl;

        cout << GOLD << "  \u2502" << RESET
             << " " << BOLD << WHITE << name << RESET
             << GOLD << "  (ID:" << id << ")" << RESET;
        int nameLen = name.length() + 10 + (id > 9 ? 2 : 1);
        for (int i = 0; i < 50 - nameLen; i++) cout << " ";
        cout << GOLD << "\u2502" << RESET << endl;

        cout << GOLD << "  \u2502" << RESET
             << "  " << DIM << desc << RESET;
        for (int i = 0; i < 50 - (int)desc.length() - 2; i++) cout << " ";
        cout << GOLD << "\u2502" << RESET << endl;

        string priceStr = "$" + to_string(price);
        priceStr = priceStr.substr(0, priceStr.find('.') + 3);
        string stockStr = "Stock: " + to_string(stock);

        cout << GOLD << "  \u2502" << RESET
             << "  " << GREEN << priceStr << RESET;
        int infoLen = priceStr.length() + stockStr.length() + 6;
        for (int i = 0; i < 50 - infoLen; i++) cout << " ";
        cout << (stock > 0 ? GREEN : RED) << stockStr << RESET;
        cout << GOLD << "  \u2502" << RESET << endl;

        cout << GOLD << "  \u2514";
        for (int i = 0; i < 50; i++) cout << "\u2500";
        cout << "\u2518" << RESET << endl;
    }

    void drawLogo() {
        int width = 50;
        string title = "BD STORE";
        int pad = (width - (int)title.length()) / 2;
        int rpad = width - pad - (int)title.length();

        cout << GOLD << endl;
        cout << "   ";
        for (int i = 0; i < width; i++) cout << "\u2593";
        cout << endl;

        cout << "   " << "\u2593" << RESET;
        for (int i = 0; i < width - 2; i++) cout << " ";
        cout << GOLD << "\u2593" << endl;

        cout << "   " << "\u2593" << RESET;
        for (int i = 0; i < pad; i++) cout << " ";
        cout << BOLD << WHITE << title;
        for (int i = 0; i < rpad; i++) cout << " ";
        cout << RESET << GOLD << "\u2593" << endl;

        cout << "   " << "\u2593" << RESET;
        for (int i = 0; i < width - 2; i++) cout << " ";
        cout << GOLD << "\u2593" << endl;

        cout << "   ";
        for (int i = 0; i < width; i++) cout << "\u2593";
        cout << RESET << endl;
        cout << endl;
    }

    void drawSmallLogo() {
        cout << GOLD << "  [== BD STORE ==]" << RESET << endl;
    }

    string inputString(string prompt) {
        drawPrompt(prompt);
        string val;
        cin >> val;
        return val;
    }

    int inputInt(string prompt) {
        drawPrompt(prompt);
        int val;
        cin >> val;
        return val;
    }

    double inputDouble(string prompt) {
        drawPrompt(prompt);
        double val;
        cin >> val;
        return val;
    }
}
