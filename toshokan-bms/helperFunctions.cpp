// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Helper Functions Header

#include <toshokan-bms/helperFunctions.hpp>

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> splitLine(std::string input) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string temp;

    while (getline(ss, temp, ',')) {
        result.push_back(temp);
    }

    return result;
}

int getScreenColumns() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int getScreenRows() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row;
}

void initTerminalInput() {
    // Disable internal buffering.
    std::cout << std::unitbuf;

    // Turn off line buffering.
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term);
    setbuf(stdin, NULL);
}

int kbhit() {
    static int nbbytes;
    ioctl(0, FIONREAD, &nbbytes);
    return nbbytes;
}

char getChar(std::function<bool(char)> validationFunction) {
    static char inputChar;
    do {
        // Wait until there's an input character.
        while (!kbhit()) {
        }
        inputChar = getchar();
        // Validate the input character.
        if (validationFunction(inputChar)) {
            // Valid.
            break;
        } else {
            // Erase the invalid character.
            std::cout << "\b \b";
        }
    } while (true);
    return inputChar;
}

bool anyKey(char inputChar) {
    return inputChar >= 0 && inputChar <= 127;
}

bool isLetter(char inputChar) {
    return isalpha(inputChar) || inputChar == 10 || inputChar == 127;
}

bool isNumber(char inputChar) {
    return isdigit(inputChar) || inputChar == 10 || inputChar == 127;
}

bool isPrintable(char inputChar) {
    return isgraph(inputChar) || inputChar == 10 || inputChar == 127;
}

bool mainMenuOpts(char inputChar) {
    return isdigit(inputChar) && (inputChar == '0' || (inputChar >= '2' && inputChar <= '6'));
}

bool searchOpts(char inputChar) {
    return isdigit(inputChar) && (inputChar >= '0' && inputChar <= '7');
}

bool userOpts(char inputChar) {
    return inputChar >= '1' && inputChar <= '5';
}

std::string capturePrintable() {
    std::string entry;
    char c;
    while ((c = getChar(&isPrintable)) != 10) {
        if (c == 127 && !entry.empty()) {
            std::cout << "\b\b\b   \b\b\b";
            entry.pop_back();
        } else {
            entry.push_back(c);
        }
    }
    return entry;
}

std::string captureText() {
    std::string entry;
    char c;
    while ((c = getChar(&isLetter)) != 10) {
        if (c == 127 && !entry.empty()) {
            std::cout << "\b\b\b   \b\b\b";
            entry.pop_back();
        } else {
            entry.push_back(c);
        }
    }
    return entry;
}

std::string capturePassword() {
    // Disable echo from https://stackoverflow.com/a/6899073
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    char c;
    while ((c = getChar(&isPrintable)) != 10) {
        if (c == 127 && !password.empty()) {
            password.pop_back();
        } else {
            password.push_back(c);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}

uint32_t captureNumber() {
    std::string entry;
    char c;
    while ((c = getChar(&isNumber)) != 10) {
        if (c == 127 && !entry.empty()) {
            std::cout << "\b\b\b   \b\b\b";
            entry.pop_back();
        } else {
            entry.push_back(c);
        }
    }

    if (entry.empty()) {
        return 0;
    }

    return stoi(entry);
}
