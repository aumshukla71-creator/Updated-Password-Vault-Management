# 🔐 Password Vault Manager (C++)

A secure, console-based credential storage and security analysis tool built with **Object-Oriented Programming (OOP)** principles in C++. The project demonstrates runtime polymorphism, abstract data types, direct binary file serialization (`std::ios::binary`), and an automated security auditing engine.

---

## 🌟 Key Features

* **Heterogeneous Vault Storage:** Manages both web/app credentials and encrypted notes within a unified polymorphic collection (`std::vector<VaultItem*>`).
* **Binary Serialization:** Direct byte streaming (`write()` / `read()`) to persistent `vault.dat` storage with type-tagging for reconstruction.
* **Security Audit Engine:** Generates comprehensive risk assessments, flagging weak passwords (strength < 50%) and computing an overall **Security Health Index**.
* **Targeted Search & Filtering:** Filter entries by keyword match or query credentials below customizable security thresholds.
* **Robust Input Sanitization:** Custom validation wrappers prevent stream state failures and buffer overruns.

---

## 🧱 OOP Architecture & Principles

| Concept | Implementation Details |
| :--- | :--- |
| **Abstract Base Class** | `VaultItem` defines the base blueprint with pure virtual functions (`displayDetails`, `calculateStrength`, `writeBinary`, `readBinary`). |
| **Inheritance** | `LoginCredential` (URLs, user/pass) and `SecureNote` (secret text, categories) extend `VaultItem`. |
| **Runtime Polymorphism** | Iterates over base class pointers (`VaultItem*`) to dynamically execute derived-class behaviors. |
| **Encapsulation & Safety** | Fixed-buffer data structures and private member variables accessed strictly via interfaces; virtual destructors ensure leak-free polymorphic deletion. |
| **Binary File Handling** | Avoids human-readable plain text by writing raw binary records with unique type identifiers. |

---

## 📁 Project Structure

```text
PasswordVault/
├── include/
│   ├── VaultItem.h         # Abstract base class
│   ├── LoginCredential.h   # Derived web credential class
│   ├── SecureNote.h        # Derived secret note class
│   ├── VaultManager.h      # Persistence controller & data manager
│   └── Validator.h         # Input validation utility
├── src/
│   ├── LoginCredential.cpp
│   ├── SecureNote.cpp
│   ├── VaultManager.cpp
│   └── main.cpp            # Interactive menu-driven console loop
├── .gitignore              # Ignores executables, objects, and local databases
└── README.md
