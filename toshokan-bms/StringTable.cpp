// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// String Table Source Code

#include <toshokan-bms/StringTable.hpp>

#include <string_view>
#include <vector>

std::string_view user_filename = "../data/users.dat";
std::string_view novels_filename = "../data/novels.dat";
std::string_view textbooks_filename = "../data/textbooks.dat";
std::string_view graphicnovels_filename = "../data/graphicnovels.dat";

std::array<std::string_view, 7> banner = {
" ___________  ______    ________  __    __     ______    __   ___       __      _____  ___ ",
"(\"     _   \")/    \" \\  /\"       )/\" |  | \"\\   /    \" \\  |/\"| /  \")     /\"\"\\    (\"   \\|\\\"  \\ ",  // NOLINT
" )__/  \\\\__/// ____  \\(:   \\___/(:  (__)  :) // ____  \\ (: |/   /     /    \\   |.\\\\   \\    |",  // NOLINT
"    \\\\_ /  /  /    ) :)\\___  \\   \\/      \\/ /  /    ) :)|    __/     /' /\\  \\  |: \\.   \\\\  |",  // NOLINT
"    |.  | (: (____/ //  __/  \\\\  //  __  \\\\(: (____/ // (// _  \\    //  __'  \\ |.  \\    \\. |",  // NOLINT
"    \\:  |  \\        /  /\" \\   :)(:  (  )  :)\\        /  |: | \\  \\  /   /  \\\\  \\|    \\    \\ |",  // NOLINT
"     \\__|   \\\"_____/  (_______/  \\__|  |__/  \\\"_____/   (__|  \\__)(___/    \\___)\\___|\\____\\)"  // NOLINT
};

std::array<std::vector<std::string_view>, 5> options = {
    // Main Menu Options
    std::vector<std::string_view> {"2 - Search", "3 - Invoice", "4 - Data", "5 - Users", "6 - Logout", "0 - Exit"}, //NOLINT
    // Search Options
    std::vector<std::string_view> {"1 - General Search", "2 - ISBN Search", "3 - Title Search", "4 - Author Search", "5 - Publisher Search", "6 - Year Search", "7 - Other Search", "0 - Main Menu"}, //NOLINT
    // Invoice Options
    std::vector<std::string_view>{},
    // Data Management Options
    std::vector<std::string_view>{},
    // User Management Options
    std::vector<std::string_view>{"1 - Change PW", "2 - Add User", "3 - Remove User", "4 - Change Users Group", "5 - Main Menu"}  //NOLINT
};

std::array<std::string_view, 7> screenTitles = {
    "Exit",
    "Main Menu",
    "Search",
    "Invoice",
    "Data Management",
    "User Management",
    "Login"
};
