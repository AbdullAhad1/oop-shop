#ifndef UI_HPP
#define UI_HPP

#include <string>
using namespace std;

namespace UI {
    // ANSI color codes
    extern const string RESET;
    extern const string BOLD;
    extern const string DIM;
    extern const string ITALIC;
    extern const string UNDERLINE;

    extern const string BLACK;
    extern const string RED;
    extern const string GREEN;
    extern const string YELLOW;
    extern const string BLUE;
    extern const string MAGENTA;
    extern const string CYAN;
    extern const string WHITE;

    extern const string BG_BLACK;
    extern const string BG_RED;
    extern const string BG_GREEN;
    extern const string BG_YELLOW;
    extern const string BG_BLUE;
    extern const string BG_MAGENTA;
    extern const string BG_CYAN;
    extern const string BG_WHITE;

    extern const string GOLD;      // Bright yellow-gold
    extern const string ORANGE;    // Orange accent
    extern const string DARK_GOLD;

    // Box drawing characters
    extern const char* HORIZONTAL;
    extern const char* VERTICAL;
    extern const char* TOP_LEFT;
    extern const char* TOP_RIGHT;
    extern const char* BOTTOM_LEFT;
    extern const char* BOTTOM_RIGHT;
    extern const char* T_LEFT;
    extern const char* T_RIGHT;
    extern const char* T_TOP;
    extern const char* T_BOTTOM;
    extern const char* CROSS;

    // Screen helpers
    void clearScreen();
    void setTitle(string title);

    // Drawing primitives
    void drawBox(int x, int y, int w, int h);
    void drawHorizontalLine(int x, int y, int w);
    void drawVerticalLine(int x, int y, int h);
    void printAt(int x, int y, string text);

    // Styled components
    void drawHeader(string title);
    void drawSubHeader(string text);
    void drawSeparator(char c = '=');
    void drawThinSeparator(char c = '-');
    void drawMenuItem(int num, string label);
    void drawMenuItem(int num, string label, string shortcut);
    void drawPortalMenu();
    void drawCustomerPortal();
    void drawPrompt(string text);
    void drawSuccess(string text);
    void drawError(string text);
    void drawWarning(string text);
    void drawInfo(string text);
    void drawBanner(string text);

    // Table-style output
    void drawTableHeader(string col1, string col2, string col3);
    void drawTableHeader(string col1, string col2, string col3, string col4);
    void drawTableRow(string col1, string col2, string col3);
    void drawTableRow(string col1, string col2, string col3, string col4);

    // Product card
    void drawProductCard(int id, string name, string desc, double price, int stock);

    // ASCII art
    void drawLogo();
    void drawSmallLogo();

    // Input helpers
    string inputString(string prompt);
    int inputInt(string prompt);
    double inputDouble(string prompt);
}

#endif
