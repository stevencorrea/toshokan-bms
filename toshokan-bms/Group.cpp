// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Group-class Header

#include <toshokan-bms/Group.hpp>

Group::Group(GroupName g) : m_name(g) {

}

bool Group::addMember(uint32_t user) {
    auto result = m_users.insert(user);
    return result.second;
}

bool Group::removeMember(uint32_t user) {
    auto it = m_users.find(user);
    if (it == m_users.end()) {
        return false;
    }

    m_users.erase(it);

    return true;
}

bool Group::checkMember(uint32_t user) const {
    auto it = m_users.find(user);
    if (it == m_users.end()) {
        return false;
    }

    return true;
}