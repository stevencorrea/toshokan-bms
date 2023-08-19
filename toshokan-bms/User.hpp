// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// User-class Header

#ifndef TOSHOKAN_BMS_USER_HPP_
#define TOSHOKAN_BMS_USER_HPP_

#include <cstdint>
#include <string>

#include <toshokan-bms/Group.hpp>

class User {
 private:
    std::string m_fName;
    std::string m_lName;
    std::string m_displayName;
    std::string m_password;
    uint32_t m_employeeID;
    GroupName m_group;

 public:
    User(std::string, std::string, std::string, uint32_t);
    explicit User(std::string);

    std::string getName() const;
    std::string getDisplayName() const;
    uint32_t getID() const;
    GroupName getGroup() const;

    bool checkGroupMembership(GroupName) const;
    bool checkPermissions(GroupName) const;
    bool verifyPW(std::string) const;
    bool changePW(std::string, std::string, uint32_t);
    void changeGroupMembership(GroupName);
    std::string saveUserInfo() const;

    friend bool operator< (const User& lhs, const User& rhs);
    friend bool operator== (const User& lhs, const User& rhs);
};

#endif  // TOSHOKAN_BMS_USER_HPP_
