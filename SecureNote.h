#ifndef SECURE_NOTE_H
#define SECURE_NOTE_H

#include "VaultItem.h"

class SecureNote : public VaultItem {
private:
    char noteContent[256];
    char category[32];

public:
    SecureNote(int id = 0, const char* t = "", const char* content = "", const char* cat = "");

    int getItemType() const override { return 2; }
    void displayDetails() const override;
    int calculateStrength() const override;
    void writeBinary(std::ofstream& out) const override;
    void readBinary(std::ifstream& in) override;

    const char* getCategory() const { return category; }
};

#endif