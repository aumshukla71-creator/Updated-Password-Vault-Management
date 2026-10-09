#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <cstring>
#include <string>

class CryptoUtils {
private:
    static inline const std::string SECRET_KEY = "Vault#SecKey!2026_IF3K_PolyMorph";

public:
    static void cipher(char* data, size_t length) {
        size_t keyLen = SECRET_KEY.length();
        for (size_t i = 0; i < length; ++i) {
            data[i] = data[i] ^ SECRET_KEY[i % keyLen] ^ static_cast<char>((i * 7) & 0xFF);
        }
    }
};

#endif