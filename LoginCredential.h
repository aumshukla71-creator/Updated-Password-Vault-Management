#ifndef LOGIN_CREDENTIAL_H
#define LOGIN_CREDENTIAL_H

#include "VaultItem.h"

class LoginCredential : public VaultItem {
private:
    char username[64];
    char password[64];
    char url[128];

public:
    LoginCredential(int id = 0, const char* t = "", const char* u = "", const char* p = "", const char* link = "");

    int getItemType() const override { return 1; }
    void displayDetails() const override;
    int calculateStrength() const override;
    void writeBinary(std::ofstream& out) const override;
    void readBinary(std::ifstream& in) override;
};

#endif