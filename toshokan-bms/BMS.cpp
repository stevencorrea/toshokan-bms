// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// BMS-class Source Code

#include <toshokan-bms/BMS.hpp>

#include <cstdint>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <toshokan-bms/Item.hpp>
#include <toshokan-bms/Book.hpp>
#include <toshokan-bms/Novel.hpp>
#include <toshokan-bms/GraphicNovel.hpp>
#include <toshokan-bms/TextBook.hpp>

#include <toshokan-bms/helperFunctions.hpp>
#include <toshokan-bms/StringTable.hpp>

BMS::BMS() : m_auth_user(0), m_status(MAINMENU) {
    std::ifstream inFS;
    std::string data;

    // Add each group with no users
    for (uint32_t i = 0; i < 4; ++i) {
        m_groups.push_back(Group(static_cast<GroupName>(i)));
    }

    // Add each user and place into Group
    inFS.open(static_cast<std::string>(user_filename));
    if (!inFS.is_open()) {
        std::cerr << "File error: " << user_filename << std::endl;
        exit(1);
    }
    while (getline(inFS, data)) {
        User u(data);
        m_users.insert({u.getID(), u});
        m_groups.at(u.getGroup()).addMember(u.getID());
    }
    inFS.close();
    data.clear();

    // Read in novels data
    inFS.open(static_cast<std::string>(novels_filename));
    if (!inFS.is_open()) {
        std::cerr << "File error: " << novels_filename << std::endl;
        exit(1);
    }
    while (getline(inFS, data)) {
        std::vector<std::string> input = splitLine(data);
        Book* tempNov = new Novel(stoull(input.at(0)), input.at(1), input.at(2), input.at(3),
        stoi(input.at(4)), input.at(5));
        Item* tempItem = new Item(tempNov, stod(input.at(6)), stoul(input.at(7)));
        m_items.push_back(tempItem);
    }
    data.clear();
    inFS.close();

    // Read in graphic novels data
    inFS.open(static_cast<std::string>(graphicnovels_filename));
    if (!inFS.is_open()) {
        std::cerr << "File error: " << graphicnovels_filename << std::endl;
        exit(1);
    }
    while (getline(inFS, data)) {
        std::vector<std::string> input = splitLine(data);
        Book* tempNov = new GraphicNovel(stoull(input.at(0)), input.at(1), input.at(2), input.at(3),
        stoi(input.at(4)), input.at(5));
        Item* tempItem = new Item(tempNov, stod(input.at(6)), stoul(input.at(7)));
        m_items.push_back(tempItem);
    }
    data.clear();
    inFS.close();

    // Read in textbook data
    inFS.open(static_cast<std::string>(textbooks_filename));
    if (!inFS.is_open()) {
        std::cerr << "File error: " << textbooks_filename << std::endl;
        exit(1);
    }
    while (getline(inFS, data)) {
        std::vector<std::string> input = splitLine(data);
        Book* tempNov = new TextBook(stoull(input.at(0)), input.at(1), input.at(2), input.at(3),
        stoi(input.at(4)), input.at(5));
        Item* tempItem = new Item(tempNov, stod(input.at(6)), stoul(input.at(7)));
        m_items.push_back(tempItem);
    }
    data.clear();
    inFS.close();
}

BMS::~BMS() {
    std::ofstream outFS(static_cast<std::string>(user_filename));

    for (auto it : m_users) {
        outFS << it.second.saveUserInfo() << '\n';
    }
}

void BMS::runBMS() {
    while (true) {
        m_width = getScreenColumns();
        m_height = getScreenRows();
        m_screen_space = m_height - 17;

        if (m_width < min_width || m_height < min_height) {
            small();
            continue;
        }

        drawBanner();
        switch (m_status) {
            case EXIT:
                system("clear");
                return;
                break;
            case MAINMENU:
                mainMenu();
                break;
            case SEARCH:
                search();
                break;
            case INVOICE:
                invoice();
                break;
            case DATA_MNGT:
                data();
                break;
            case USER_MNGT:
                user();
                break;
            case LOGIN:
                login();
                break;
            default:
                std::cerr << "Something went wrong\n";
                exit(-1);
        }
    }
}

void BMS::mainMenu() {
    if (m_auth_user == 0) {
        std::cout << "Press X to exit or another key to login";
        char c = getChar(&anyKey);
        if (c == 'X' || c == 'x') {
            switchStatus(EXIT);
        } else {
            switchStatus(LOGIN);
        }
        return;
    }

    auto it = m_users.find(m_auth_user);

    std::cout << "Welcome " << it->second.getDisplayName() << "\n";

    drawMenu();

    uint32_t choice = getChar(&mainMenuOpts) - '0';
    if (choice == 6) {
        m_auth_user = 0;
    } else {
        switchStatus(static_cast<Status>(choice));
    }
}

void BMS::search() {
    drawMenu();

    uint32_t choice = getChar(&searchOpts) - '0';
    std::vector<Item*> searchResults;
    drawBanner();
    switch (choice) {
        case 1: {
            std::cout << "General Search\n";
            std::cout << "Enter search parameter: ";
            std::string searchParam = capturePrintable();
            for (auto i : m_items) {
                if (i->checkAll(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 2: {
            std::cout << "ISBN Search\n";
            std::cout << "Enter search parameter: ";
            uint32_t searchParam = captureNumber();
            for (auto i : m_items) {
                if (i->checkISBN(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 3: {
            std::cout << "Title Search\n";
            std::cout << "Enter search parameter: ";
            std::string searchParam = capturePrintable();
            for (auto i : m_items) {
                if (i->checkTitle(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 4: {
            std::cout << "Author Search\n";
            std::cout << "Enter search parameter: ";
            std::string searchParam = capturePrintable();
            for (auto i : m_items) {
                if (i->checkAuthor(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 5: {
            std::cout << "Publisher Search\n";
            std::cout << "Enter search parameter: ";
            std::string searchParam = capturePrintable();
            for (auto i : m_items) {
                if (i->checkPublisher(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 6: {
            std::cout << "Year Search\n";
            std::cout << "Enter search parameter: ";
            uint32_t searchParam = captureNumber();
            for (auto i : m_items) {
                if (i->checkYear(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 7: {
            std::cout << "Other Search\n";
            std::cout << "Enter search parameter: ";
            std::string searchParam = capturePrintable();
            for (auto i : m_items) {
                if (i->checkOther(searchParam)) {
                    searchResults.push_back(i);
                }
            }
            break;
        }
        case 0:
            switchStatus(MAINMENU);
        default:
            std::cerr << "Something went wrong with Search" << std::endl;
    }

    drawBanner();
    for (auto item : searchResults) {
        item->display();
    }
    getChar(&anyKey);
}

void BMS::invoice() {
    getChar(&anyKey);
    switchStatus(MAINMENU);
}

void BMS::data() {
    std::cout << "Feature coming soon!\n";
    getChar(&anyKey);
    switchStatus(MAINMENU);
}

void BMS::user() {
    drawMenu();

    uint32_t choice = getChar(&userOpts) - '0';

    drawBanner();
    switch (choice) {
        case 1: {
            std::cout << "Change Password\n";
            std::cout << "Enter current password: ";
            std::string oldPw = capturePassword();
            std::cout << "\nEnter new password: ";
            std::string newPw1 = capturePassword();
            std::cout << "\nConfirm new password: ";
            std::string newPw2 = capturePassword();

            if (newPw1 != newPw2) {
                std::cout << "\n\nNew password does not match";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            auto it = m_users.find(m_auth_user);

            if (!it->second.changePW(newPw1, oldPw, m_auth_user)) {
                std::cout << "\n\nPassword change FAILED.";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            std::cout << "\n\nPassword successfully changed!";
            std::cout << "\nPress any key to continue";
            getChar(&anyKey);
            break;
        }
        case 2: {
            auto authUser_it = m_users.find(m_auth_user);

            if (!authUser_it->second.checkPermissions(ADMIN)) {
                std::cout << "\n\nYou do not have permission for this operation";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            std::cout << "Enter first name: ";
            std::string fName = captureText();
            std::cout << "Enter last name: ";
            std::string lName = captureText();
            std::cout << "Enter display name: ";
            std::string dName = captureText();
            std::cout << "Enter employee ID: ";
            uint32_t empID = captureNumber();

            if (fName.empty() || lName.empty() || dName.empty()) {
                std::cout << "\n\nFields cannot be empty";
                std::cout <<" \nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            if (empID < 9999 || empID > 100000) {
                std::cout << "\n\nEmployee ID must be a 5 digit number between 10000 and 99999";
                std::cout <<" \nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            auto newUser_it = m_users.find(empID);

            if (newUser_it != m_users.end()) {
                std::cout << "\n\nEmployee ID already in use";
                std::cout <<" \nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            User u(fName, lName, dName, empID);
            m_users.insert({u.getID(), u});

            std::cout << "\nNew user added.";
            std::cout << "\nPress any key to continue";
            getChar(&anyKey);
            break;
        }
        case 3: {
            auto authUser_it = m_users.find(m_auth_user);

            if (!authUser_it->second.checkPermissions(ADMIN)) {
                std::cout << "\n\nYou do not have permission for this operation";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            std::cout << "\n\nEnter employee ID to remove: ";
            uint32_t empID = captureNumber();

            if (empID == m_auth_user) {
                std::cout << "You cannot remove yourself";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            auto delUser_it = m_users.find(empID);

            if (delUser_it->second.getGroup() == SUPERUSER && authUser_it->second.getGroup() != SUPERUSER) { //NOLINT
                std::cout << "\n\nYou must be a SUPERUSER to delete a SUPERUSER";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            if (delUser_it == m_users.end()) {
                std::cout << "\n\nEmployee number " << empID << " not found";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            std::cout << "Are you sure you want to remove user: ";
            std::cout << "\nName: " << delUser_it->second.getName();
            std::cout << "\nEmployee ID: " << delUser_it->second.getID();
            std::cout << "\n\nPress y to confirm, any other key to cancel";

            char c = toupper(getChar(&anyKey));

            if (c != 'Y') {
                std::cout << "User removal cancelled";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            m_users.erase(delUser_it);

            std::cout << "\n\nUser removed";
            std::cout << "\nPress any key to continue";
            getChar(&anyKey);

            break;
        }
        case 4: {
            auto authUser_it = m_users.find(m_auth_user);

            if (!authUser_it->second.checkPermissions(ADMIN)) {
                std::cout << "\n\nYou do not have permission for this operation";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            std::cout << "Enter employee ID to modify group membership: ";
            uint32_t empID = captureNumber();

            auto modUser_it = m_users.find(empID);

            if (modUser_it == m_users.end()) {
                std::cout << "\n\nEmployee number " << empID << " not found";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            std::cout << "Select new group:\n";
            std::cout << "1 - Super User\n";
            std::cout << "2 - Admin\n";
            std::cout << "3 - Manager\n";
            std::cout << "4 - Clerk\n";
            uint32_t newGroup = captureNumber();

            if (newGroup == 0 || newGroup > 4) {
                std::cout << "\n\nInvalid choice";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            if (newGroup == 1 && authUser_it->second.getGroup() != SUPERUSER) {
                std::cout << "\n\nYou must be a Super User to add a user to the Super User group";
                std::cout << "\nPress any key to continue";
                getChar(&anyKey);
                break;
            }

            modUser_it->second.changeGroupMembership(static_cast<GroupName>(newGroup-1));
            std::cout << "\n\nPress y to confirm, any other key to cancel";

            std::cout << "\n\nGroup Changed";
            std::cout << "\nPress any key to continue";
            getChar(&anyKey);

            break;
        }
        case 5:
            switchStatus(MAINMENU);
            break;
        default:
            std::cerr << "Something went wrong with User Management" << std::endl;
    }
}

void BMS::login() {
    std::cout << "Employee ID: ";
    uint32_t empID = captureNumber();
    std::cout << "Password: ";
    std::string password = capturePassword();

    if (empID == 0) {
        switchStatus(MAINMENU);
        return;
    }

    auto it = m_users.find(empID);
    if (it == m_users.end() || !it->second.verifyPW(password)) {
        std::cout << "Invalid ID and/or password\n";
        std::cout << "Press any key to continue" << std::endl;
        empID = -1;
        password.clear();
        getChar(&anyKey);
    } else {
        m_auth_user = empID;
        switchStatus(MAINMENU);
    }
}

void BMS::small() {
    system("clear");
    std::cout << "Terminal Window is too small\n";
    std::cout << "Current width: " << m_width << '\n';
    std::cout << "Minimum width: " << min_width << '\n';
    std::cout << "Current height: " << m_height << '\n';
    std::cout << "Minimum height: " << min_height << '\n';
    std::cout << '\n';
    std::cout << "Please resize then press any key" << std::endl;
    getChar(&anyKey);
}

void BMS::drawBanner() {
    system("clear");
    std::cout << "\n\n";
    std::cout << std::setw(m_width/2 - 34) << "Welcome to:\n";
    for (auto str : banner) {
        std::cout << std::setw(m_width/2 + str.size()/2)<< str << '\n';
    }
    std::cout << '\n';
    std::cout << std::setw(m_width/2+47) << "Book Management System\n";
    std::cout << "\n\n";
    std::string_view title = screenTitles.at(m_status);
    std::cout << std::setw(m_width/2 + title.size()/2) << title << '\n';
    std::cout << "\n\n";
}

void BMS::drawMenu() {
    for (auto opt : options[m_status-1]) {
        std::cout << opt << std::endl;
    }
}

void BMS::switchStatus(Status s) {
    m_status = s;
}
