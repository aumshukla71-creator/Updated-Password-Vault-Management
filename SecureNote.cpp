#include "../include/SecureNote.h"
#include "../include/CryptoUtils.h"

SecureNote::SecureNote(int id, const char* t, const char* content, const char* cat)
    : VaultItem(id, t) {
    std::strncpy(noteContent, content, sizeof(noteContent) - 1);
    noteContent[sizeof(noteContent) - 1] = '\0';
    std::strncpy(category, cat, sizeof(category) - 1);
    category[sizeof(category) - 1] = '\0';
}

void SecureNote::displayDetails() const {
    std::cout << "[Note]  ID: " << id 
              << " | Title: " << title 
              << " | Category: " << category 
              << " | Content: " << noteContent 
              << " | Entropy: " << calculateStrength() << "/100\n";
}

int SecureNote::calculateStrength() const {
    size_t len = std::strlen(noteContent);
    return (len > 100) ? 100 : static_cast<int>(len);
}

void SecureNote::writeBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(title, sizeof(title));
    out.write(reinterpret_cast<const char*>(&createdAt), sizeof(createdAt));

    char encNote[sizeof(noteContent)];
    char encCat[sizeof(category)];

    std::memcpy(encNote, noteContent, sizeof(noteContent));
    std::memcpy(encCat, category, sizeof(category));

    CryptoUtils::cipher(encNote, sizeof(encNote));
    CryptoUtils::cipher(encCat, sizeof(encCat));

    out.write(encNote, sizeof(encNote));
    out.write(encCat, sizeof(encCat));
}

void SecureNote::readBinary(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(title, sizeof(title));
    in.read(reinterpret_cast<char*>(&createdAt), sizeof(createdAt));

    in.read(noteContent, sizeof(noteContent));
    in.read(category, sizeof(category));

    CryptoUtils::cipher(noteContent, sizeof(noteContent));
    CryptoUtils::cipher(category, sizeof(category));
}