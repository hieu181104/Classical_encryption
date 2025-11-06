#include <iostream>
#include <string>
#include <cctype>

int gcd(int a, int b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

std::string encrypt(const std::string& plaintext, int a, int b) {
    std::string result;
    for (char c : plaintext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int x = c - base;
            result += static_cast<char>((a * x + b) % 26 + base);
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

std::string decrypt(const std::string& ciphertext, int a, int b) {
    std::string result;
    // Find modular multiplicative inverse of a
    int a_inv = -1;
    for (int i = 0; i < 26; ++i) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }
    if (a_inv == -1) {
        return "Error: Invalid 'a' value (must be coprime with 26).";
    }

    for (char c : ciphertext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int y = c - base;
            result += static_cast<char>((a_inv * (y - b + 26)) % 26 + base);
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

int main() {
    int a, b;
    std::cout << "Enter key 'a' (must be coprime with 26, e.g., 3, 5, 7, 11, 15): ";
    std::cin >> a;
    std::cout << "Enter key 'b' (0-25): ";
    std::cin >> b;
    std::cin.ignore(); // Clear newline after reading numbers

    // Validate 'a' (must be coprime with 26)
    if (gcd(a, 26) != 1) {
        std::cout << "Invalid 'a': Must be coprime with 26. Exiting." << std::endl;
        return 1;
    }

    int choice;
    std::cout << "Select operation: 1 for Encrypt, 2 for Decrypt: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear newline after reading choice

    std::string input;
    if (choice == 1) {
        std::cout << "Enter plaintext: ";
        std::getline(std::cin, input);
        std::string ciphertext = encrypt(input, a, b);
        std::cout << "Ciphertext: " << ciphertext << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter ciphertext: ";
        std::getline(std::cin, input);
        std::string decrypted = decrypt(input, a, b);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    return 0;
}