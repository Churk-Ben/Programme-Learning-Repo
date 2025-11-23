# pragma  once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "contact.hpp"

// 通讯录类
class ContactBook {
public:
    void add(const std::string &name, const std::string &phone); // 添加联系人
    void remove(const std::string &name); // 移除联系人
    void find(const std::string &name) const; // 查找联系人
    void display() const; // 显示所有联系人
    size_t size() const;
    
private:
    int index(const std::string &name) const;  // 返回联系人在contacts内索引，如不存在，返回-1
    void sort(); // 按姓名字典序升序排序通讯录

private:
    std::vector<Contact> contacts;
};

void ContactBook::add(const std::string &name, const std::string &phone) {
    if(index(name) == -1) {
        contacts.push_back(Contact(name, phone));
        std::cout << name << " add successfully.\n";
        sort();
        return;
    }

    std::cout << name << " already exists. fail to add!\n"; 
}

void ContactBook::remove(const std::string &name) {
    int i = index(name);

    if(i == -1) {
        std::cout << name << " not found, fail to remove!\n";
        return;
    }

    contacts.erase(contacts.begin()+i);
    std::cout << name << " remove successfully.\n";
}

void ContactBook::find(const std::string &name) const {
    int i = index(name);

    if(i == -1) {
        std::cout << name << " not found!\n";
        return;
    }

    contacts[i].display(); 
    std::cout << '\n';
}

void ContactBook::display() const {
    for(auto &c: contacts) {
        c.display(); 
        std::cout << '\n';
    }
}

size_t ContactBook::size() const {
    return contacts.size();
}

// 待补足1：int index(const std::string &name) const;实现
// 返回联系人在contacts内索引; 如不存在，返回-1



// 待补足2：void ContactBook::sort();实现
// 按姓名字典序升序排序通讯录