// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Helper Functions Header

#include <toshokan-bms/helperFunctions.hpp>

#include <string>
#include <sstream>
#include <vector>

#include <sys/ioctl.h>
#include <unistd.h>

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