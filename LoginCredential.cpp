#include "../include/LoginCredential.h"
#include "../include/CryptoUtils.h"
#include <cctype>

LoginCredential::LoginCredential(int id, const char* t, const char* u, const char* p, const char* link)
    : VaultItem(id, t) {
    std::strncpy(username, u, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';
    std::strncpy(password, p, sizeof(password) - 1);
    password[sizeof(password) - 1] = '\0';
    std::strncpy(url, link, sizeof(url) - 1);
    url[sizeof(url) - 1] = '\0';
}

void LoginCredential::displayDetails() const {
    std::cout << "[Login] ID: " << id 
              << " | Title: " << title 
              << " | User: " << username 
              << " | Password: " << password
              << " | URL: " << url 
              << " | Strength: " << calculateStrength() << "/100\n";
}

int LoginCredential::calculateStrength() const {
    int score = 0;
    size_t len = std::strlen(password);
    if (len >= 8) score += 30;
    if (len >= 12) score += 20;

    bool hasDigit = false, hasSpecial = false, hasUpper = false;
    for (size_t i = 0; i < len; ++i) {
        if (std::isdigit(password[i])) hasDigit = true;
        if (std::ispunct(password[i])) hasSpecial = true;
        if (std::isupper(password[i])) hasUpper = true;
    }
    if (hasDigit) score += 20;
    if (hasSpecial) score += 20;
    if (hasUpper) score += 10;
    return score;
}

void LoginCredential::writeBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(title, sizeof(title));
    out.write(reinterpret_cast<const char*>(&createdAt), sizeof(createdAt));

    char encUser[sizeof(username)];
    char encPass[sizeof(password)];
    char encUrl[sizeof(url)];

    std::memcpy(encUser, username, sizeof(username));
    std::memcpy(encPass, password, sizeof(password));
    std::memcpy(encUrl, url, sizeof(url));

    CryptoUtils::cipher(encUser, sizeof(encUser));
    CryptoUtils::cipher(encPass, sizeof(encPass));
    CryptoUtils::cipher(encUrl, sizeof(encUrl));

    out.write(encUser, sizeof(encUser));
    out.write(encPass, sizeof(encPass));
    out.write(encUrl, sizeof(encUrl));
}

void LoginCredential::readBinary(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(title, sizeof(title));
    in.read(reinterpret_cast<char*>(&createdAt), sizeof(createdAt));

    in.read(username, sizeof(username));
    in.read(password, sizeof(password));
    in.read(url, sizeof(url));

    CryptoUtils::cipher(username, sizeof(username));
    CryptoUtils::cipher(password, sizeof(password));
    CryptoUtils::cipher(url, sizeof(url));
}