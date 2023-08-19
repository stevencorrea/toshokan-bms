// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// String Table Header

#ifndef TOSHOKAN_BMS_STRINGTABLE_HPP_
#define TOSHOKAN_BMS_STRINGTABLE_HPP_

#include <array>
#include <string_view>
#include <vector>

extern std::string_view user_filename;
extern std::string_view novels_filename;
extern std::string_view textbooks_filename;
extern std::string_view graphicnovels_filename;
extern std::array<std::string_view, 7> banner;
extern std::array<std::vector<std::string_view>, 5> options;
extern std::array<std::string_view, 7> screenTitles;

#endif  // TOSHOKAN_BMS_STRINGTABLE_HPP_
