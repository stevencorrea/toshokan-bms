// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// BMS-class Header

#ifndef TOSHOKAN_BMS_BMS_HPP_
#define TOSHOKAN_BMS_BMS_HPP_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <toshokan-bms/base64.hpp>
#include <toshokan-bms/Group.hpp>
#include <toshokan-bms/helperFunctions.hpp>
#include <toshokan-bms/Item.hpp>
#include <toshokan-bms/User.hpp>

class BMS {
 private:
    enum Status {
        EXIT,
        MAINMENU,
        SEARCH,
        INVOICE,
        DATA_MNGT,
        USER_MNGT,
        LOGIN
    };

 private:
    std::map<uint32_t, User> m_users;
    std::vector<Group> m_groups;
    std::vector<Item*> m_items;
    uint32_t m_auth_user;
    Status m_status;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_screen_space;
    const uint32_t min_width = 150;
    const uint32_t min_height = 40;

 public:
    BMS();
    ~BMS();
    void runBMS();

 private:
    void mainMenu();
    void search();
    void invoice();
    void data();
    void user();
    void login();
    void small();

    void drawBanner();
    void drawMenu();
    void switchStatus(Status);
};

#endif  // TOSHOKAN_BMS_BMS_HPP_
