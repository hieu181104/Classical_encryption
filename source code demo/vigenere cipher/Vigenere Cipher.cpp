#include <iostream>
#include <string>
#include <cctype> // For isalpha, toupper

std::string encrypt(const std::string& plaintext, const std::string& key) {
    if (key.empty()) return plaintext; // No encryption if key is empty

    std::string result;
    std::string upperKey = key;
    for (char& c : upperKey) {
        c = std::toupper(c); // Convert key to uppercase for simplicity
    }

    size_t keyIndex = 0;
    for (char c : plaintext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char keyChar = upperKey[keyIndex % upperKey.length()];
            int shift = keyChar - 'A';
            result += static_cast<char>((c - base + shift) % 26 + base);
            keyIndex++;
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

std::string decrypt(const std::string& ciphertext, const std::string& key) {
    if (key.empty()) return ciphertext; // No decryption if key is empty

    std::string result;
    std::string upperKey = key;
    for (char& c : upperKey) {
        c = std::toupper(c); // Convert key to uppercase for simplicity
    }

    size_t keyIndex = 0;
    for (char c : ciphertext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char keyChar = upperKey[keyIndex % upperKey.length()];
            int shift = keyChar - 'A';
            result += static_cast<char>((c - base - shift + 26) % 26 + base);
            keyIndex++;
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

int main() {
    std::string key;
    std::cout << "Enter the key (e.g., KEY): ";
    std::getline(std::cin, key);

    int choice;
    std::cout << "Select operation: 1 for Encrypt, 2 for Decrypt: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear newline after reading choice

    std::string input;
    if (choice == 1) {
        std::cout << "Enter plaintext: ";
        std::getline(std::cin, input);
        std::string ciphertext = encrypt(input, key);
        std::cout << "Ciphertext: " << ciphertext << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter ciphertext: ";
        std::getline(std::cin, input);
        std::string decrypted = decrypt(input, key);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    return 0;
}