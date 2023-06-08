#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <toshokan-bms/base64.hpp>
#include <toshokan-bms/Group.hpp>
#include <toshokan-bms/User.hpp>

int main() {
    std::vector<Group> groups;
    std::map<uint32_t,User> users;
    std::string data;

    for (uint32_t i = 0; i < 4; ++i) {
        groups.push_back(Group(static_cast<GroupName>(i)));
    }

    std::cout << "Finished creating groups\n";

    std::ifstream inFS("../data/users.dat");

    if (!inFS.is_open()) {
        std::cout << "Could not open users.dat" << std::endl;
        exit(-1);
    }

    while (getline(inFS, data)) {
        User u(data);
        users.insert({u.getID(),u});
        std::cout << "added user" << std::endl;
    }
    std::cout << "Size of users after reading from file: " << users.size() << std::endl;
    inFS.close();
    User u("Elton", "John", "EJ", 12345);
    users.insert({u.getID(),u});
    std::cout << "Size of users after adding EJ: " << users.size() << std::endl;

    auto it = users.begin();
    if (it->second.verifyPW("password")) {
            std::cout << "pw match\n";
            std::cout << it->second.getDisplayName() << '\n';
            std::cout << it->second.getName() << '\n';
            std::cout << it->second.getID() << '\n';
            std::cout << it->second.getGroup() << '\n';
    }
    if (!(it->second.checkGroupMembership(SUPERUSER))) {
        it->second.changeGroupMembership(SUPERUSER);
    }
    std::cout << it->second.getGroup() << '\n';

    if (it->second.changePW("test123", "password", it->second.getID())) {
        std::cout << "pw changed" << std::endl;
    }

    std::ofstream outFS("../data/users.dat");

    for (auto it : users) {
        outFS << it.second.saveUserInfo() << '\n';
    }

}