// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Group-class Header

#ifndef TOSHOKAN_BMS_GROUP_H_
#define TOSHOKAN_BMS_GROUP_H_

#include <cstdint>
#include <set>
#include <string>

enum GroupName {
    SUPERUSER,
    ADMIN,
    MANAGER,
    CLERK
};

class Group {
  private:
    GroupName m_name;
    std::set<uint32_t> m_users;

  public:
    Group(GroupName);
    bool addMember(uint32_t);
    bool removeMember(uint32_t);
    bool checkMember(uint32_t) const;
};

#endif  // TOSHOKAN_BMS_GROUP_H_
