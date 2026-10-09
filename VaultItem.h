#ifndef VAULT_ITEM_H
#define VAULT_ITEM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

class VaultItem {
protected:
    int id;
    char title[64];
    time_t createdAt;

public:
    VaultItem(int itemId = 0, const char* itemTitle = "") : id(itemId) {
        std::strncpy(title, itemTitle, sizeof(title) - 1);
        title[sizeof(title) - 1] = '\0';
        createdAt = std::time(nullptr);
    }
    virtual ~VaultItem() {}

    int getId() const { return id; }
    const char* getTitle() const { return title; }

    virtual void displayDetails() const = 0;
    virtual int calculateStrength() const = 0;
    virtual int getItemType() const = 0; // 1 = Login, 2 = Note
    virtual void writeBinary(std::ofstream& out) const = 0;
    virtual void readBinary(std::ifstream& in) = 0;
};

#endif