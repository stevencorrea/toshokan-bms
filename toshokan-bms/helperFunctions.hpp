// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Helper Functions Header

// Capturing characters without waiting for enter from:
// https://stackoverflow.com/a/67363091

#ifndef TOSHOKAN_BMS_HELPERFUNCTIONS_HPP_
#define TOSHOKAN_BMS_HELPERFUNCTIONS_HPP_

#include <functional>
#include <string>
#include <vector>

std::vector<std::string> splitLine(std::string input);
int getScreenColumns();
int getScreenRows();
void initTerminalInput();
int kbhit();
char getChar(std::function<bool(char)> validationFunction);
bool anyKey(char inputChar);
bool isLetter(char inputChar);
bool isNumber(char inputChar);
bool isPrintable(char inputChar);
bool mainMenuOpts(char inputChar);
bool searchOpts(char inputChar);
bool userOpts(char inputChar);
std::string capturePrintable();
std::string captureText();
std::string capturePassword();
uint32_t captureNumber();

#endif  // TOSHOKAN_BMS_HELPERFUNCTIONS_HPP_
