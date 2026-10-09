#include "../include/VaultManager.h"
#include "../include/LoginCredential.h"
#include "../include/SecureNote.h"
#include <iostream>

VaultManager::VaultManager(const std::string& dbFile) : filename(dbFile), nextId(1) {
    loadFromFile();
}

VaultManager::~VaultManager() {
    clearMemory();
}

void VaultManager::clearMemory() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
}

void VaultManager::addItem(VaultItem* item) {
    items.push_back(item);
    std::cout << "Record added successfully with ID: " << item->getId() << "\n";
    saveToFile();
}

void VaultManager::displayAll() const {
    if (items.empty()) {
        std::cout << "\n[Notice] No records found in the vault. Try adding one first (Options 1 or 2).\n";
        return;
    }
    std::cout << "\n-------------------- ALL VAULT RECORDS --------------------\n";
    for (const auto& item : items) {
        item->displayDetails();
    }
    std::cout << "----------------------------------------------------------\n";
}

void VaultManager::searchByTitle(const std::string& keyword) const {
    bool found = false;
    for (const auto& item : items) {
        std::string t = item->getTitle();
        if (t.find(keyword) != std::string::npos) {
            item->displayDetails();
            found = true;
        }
    }
    if (!found) std::cout << "No matching records found for: " << keyword << "\n";
}

void VaultManager::searchWeakPasswords(int threshold) const {
    bool found = false;
    std::cout << "\n--- Credentials With Strength Below " << threshold << "% ---\n";
    for (const auto& item : items) {
        if (item->calculateStrength() < threshold) {
            item->displayDetails();
            found = true;
        }
    }
    if (!found) std::cout << "All items meet or exceed the security threshold!\n";
}

void VaultManager::deleteItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            items.erase(it);
            std::cout << "Item ID " << id << " deleted successfully.\n";
            saveToFile();
            return;
        }
    }
    std::cout << "Item ID " << id << " not found.\n";
}

void VaultManager::generateSecurityReport() const {
    int total = items.size();
    int loginCount = 0;
    int noteCount = 0;
    int weakCount = 0;

    for (const auto& item : items) {
        if (item->getItemType() == 1) loginCount++;
        else if (item->getItemType() == 2) noteCount++;

        if (item->calculateStrength() < 50) weakCount++;
    }

    std::cout << "\n================ VAULT AUDIT REPORT ================\n";
    std::cout << "Total Encrypted Records : " << total << "\n";
    std::cout << "Total Login Accounts    : " << loginCount << "\n";
    std::cout << "Total Secure Notes      : " << noteCount << "\n";
    std::cout << "At-Risk Items (< 50%)   : " << weakCount << "\n";
    std::cout << "Security Health Index   : " 
              << (total == 0 ? 100 : (100 - (weakCount * 100 / total))) << "%\n";
    std::cout << "====================================================\n";
}

void VaultManager::saveToFile() {
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Error writing to binary database!\n";
        return;
    }

    size_t count = items.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& item : items) {
        int type = item->getItemType();
        out.write(reinterpret_cast<const char*>(&type), sizeof(type));
        item->writeBinary(out);
    }
    out.close();
}

void VaultManager::loadFromFile() {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;

    clearMemory();
    size_t count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        int type = 0;
        in.read(reinterpret_cast<char*>(&type), sizeof(type));

        VaultItem* item = nullptr;
        if (type == 1) {
            item = new LoginCredential();
        } else if (type == 2) {
            item = new SecureNote();
        }

        if (item) {
            item->readBinary(in);
            items.push_back(item);
            if (item->getId() >= nextId) {
                nextId = item->getId() + 1;
            }
        }
    }
    in.close();
}