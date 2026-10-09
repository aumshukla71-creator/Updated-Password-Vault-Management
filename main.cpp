#include <iostream>
#include "../include/VaultManager.h"
#include "../include/LoginCredential.h"
#include "../include/SecureNote.h"
#include "../include/Validator.h"

int main() {
    VaultManager manager("vault.dat");
    int choice = 0;

    while (choice != 7) {
        std::cout << "\n======================================\n";
        std::cout << "       PASSWORD VAULT MANAGER         \n";
        std::cout << "======================================\n";
        std::cout << "1. Add New Login Credential\n";
        std::cout << "2. Add New Secure Note\n";
        std::cout << "3. View All Vault Items\n";
        std::cout << "4. Search by Title\n";
        std::cout << "5. Search Weak Passwords\n";
        std::cout << "6. Delete Record\n";
        std::cout << "7. Save & Exit\n";
        std::cout << "Enter choice (1-7): ";
        choice = Validator::getInteger(1, 7);

        if (choice == 1) {
            char title[64], user[64], pass[64], url[128];
            std::cout << "Title: "; Validator::getString(title, 64);
            std::cout << "Username: "; Validator::getString(user, 64);
            std::cout << "Password: "; Validator::getString(pass, 64);
            std::cout << "URL: "; Validator::getString(url, 128);

            manager.addItem(new LoginCredential(manager.generateNextId(), title, user, pass, url));
        } else if (choice == 2) {
            char title[64], content[256], category[32];
            std::cout << "Title: "; Validator::getString(title, 64);
            std::cout << "Category (PIN/License/Card): "; Validator::getString(category, 32);
            std::cout << "Secret Note: "; Validator::getString(content, 256);

            manager.addItem(new SecureNote(manager.generateNextId(), title, content, category));
        } else if (choice == 3) {
            manager.displayAll();
        } else if (choice == 4) {
            char kw[64];
            std::cout << "Search Keyword: "; Validator::getString(kw, 64);
            manager.searchByTitle(kw);
        } else if (choice == 5) {
            std::cout << "Strength threshold limit (e.g. 50): ";
            int thresh = Validator::getInteger(1, 100);
            manager.searchWeakPasswords(thresh);
        } else if (choice == 6) {
            if (manager.isEmpty()) {
                std::cout << "\nVault is currently empty. Nothing to delete.\n";
            } else {
                std::cout << "\n--- Current Records in Vault ---\n";
                manager.displayAll();
                std::cout << "\nEnter the ID of the record you want to delete (or 0 to cancel): ";
                int id = Validator::getInteger(0, 100000);
                if (id == 0) {
                    std::cout << "Deletion cancelled.\n";
                } else {
                    manager.deleteItem(id);
                }
            }
        } else if (choice == 7) {
            manager.saveToFile();
            manager.generateSecurityReport();
            std::cout << "Vault secured. Exiting.\n";
        }
    }

    return 0;
}