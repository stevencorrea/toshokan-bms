// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// User-class Header

#include <toshokan-bms/User.hpp>

#include <toshokan-bms/base64.hpp>
#include <toshokan-bms/Group.hpp>
#include <toshokan-bms/helperFunctions.hpp>

#include <cstdint>
#include <string>
#include <vector>

User::User(std::string first, std::string last, std::string display, uint32_t id) :
    m_fName(first), m_lName(last), m_displayName(display), m_employeeID(id) {
    
    std::string tempPW = "password";
    m_password = base64_encode(tempPW);
    m_group = CLERK;
}

User::User(std::string data) {
    data = base64_decode(data);
    std::vector<std::string> tokens = splitLine(data);

    m_fName = tokens.at(0);
    m_lName = tokens.at(1);
    m_displayName = tokens.at(2);
    m_password = tokens.at(3);
    m_employeeID = stoi(tokens.at(4));
    m_group = static_cast<GroupName>(stoi(tokens.at(5)));
}

std::string User::getName() const {
    return m_fName + " " + m_lName;
}

std::string User::getDisplayName() const {
    return m_displayName;
}

uint32_t User::getID() const {
    return m_employeeID;
}

GroupName User::getGroup() const {
    return m_group;
}

bool User::checkGroupMembership(GroupName g) const {
    if (g != m_group) {
        return false;
    }

    return true;
}

bool User::verifyPW(std::string pw) const {
    if (base64_encode(pw) != m_password) {
        return false;
    }

    return true;
}

bool User::changePW(std::string newPW, std::string oldPW, uint32_t id) {
    if (id != m_employeeID) {
        return false;
    }

    if (base64_encode(oldPW) != m_password) {
        return false;
    }

    m_password = base64_encode(newPW);
    return true;
}

void User::changeGroupMembership(GroupName g) {
    m_group = g;
}

std::string User::saveUserInfo() const {
    std::string data;
    std::string delimiter = ",";
    
    data.append(m_fName);
    data.append(delimiter);
    data.append(m_lName);
    data.append(delimiter);
    data.append(m_displayName);
    data.append(delimiter);
    data.append(m_password);
    data.append(delimiter);
    data.append(std::to_string(m_employeeID));
    data.append(delimiter);
    data.append(std::to_string(m_group));
    
    return base64_encode(data);
}


bool operator<(const User &lhs, const User &rhs) {
    return lhs.m_employeeID < rhs.m_employeeID;
}

bool operator==(const User &lhs, const User &rhs) {
    return lhs.m_employeeID == rhs.m_employeeID;
}

