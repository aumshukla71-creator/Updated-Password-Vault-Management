#ifndef VAULT_MANAGER_H
#define VAULT_MANAGER_H

#include <vector>
#include <string>
#include "VaultItem.h"

class VaultManager {
private:
    std::vector<VaultItem*> items;
    std::string filename;
    int nextId;

    void clearMemory();

public:
    VaultManager(const std::string& dbFile = "vault.dat");
    ~VaultManager();

    void addItem(VaultItem* item);
    void displayAll() const;
    void searchByTitle(const std::string& keyword) const;
    void searchWeakPasswords(int threshold) const;
    void deleteItem(int id);
    void generateSecurityReport() const;

    void saveToFile();
    void loadFromFile();

    bool isEmpty() const { return items.empty(); }
    int generateNextId() { return nextId++; }
};

#endif