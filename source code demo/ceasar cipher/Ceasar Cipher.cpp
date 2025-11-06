#include <iostream>
#include <string>
#include <cctype>

std::string encrypt(const std::string& plaintext, int shift) {
    std::string result;
    shift = shift % 26; // Normalize shift to 0-25
    for (char c : plaintext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            result += static_cast<char>((c - base + shift) % 26 + base);
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

std::string decrypt(const std::string& ciphertext, int shift) {
    std::string result;
    shift = shift % 26; // Normalize shift to 0-25
    for (char c : ciphertext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            result += static_cast<char>((c - base - shift + 26) % 26 + base);
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

int main() {
    int shift;
    std::cout << "Enter shift value (e.g., 3 for Caesar Cipher): ";
    std::cin >> shift;
    std::cin.ignore(); // Clear newline after reading shift

    int choice;
    std::cout << "Select operation: 1 for Encrypt, 2 for Decrypt: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear newline after reading choice

    std::string input;
    if (choice == 1) {
        std::cout << "Enter plaintext: ";
        std::getline(std::cin, input);
        std::string ciphertext = encrypt(input, shift);
        std::cout << "Ciphertext: " << ciphertext << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter ciphertext: ";
        std::getline(std::cin, input);
        std::string decrypted = decrypt(input, shift);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    return 0;
}