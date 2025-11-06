#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::string encrypt(const std::string& plaintext, const std::string& key) {
    int cols = key.length();
    int rows = std::ceil(static_cast<double>(plaintext.length()) / cols);
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols, 'X')); // Pad with 'X' if needed

    // Fill the matrix row-wise
    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (index < plaintext.length()) {
                matrix[r][c] = plaintext[index++];
            }
        }
    }

    // Create permutation based on key
    std::vector<std::pair<char, int>> key_pairs;
    for (int i = 0; i < cols; ++i) {
        key_pairs.emplace_back(key[i], i);
    }
    std::sort(key_pairs.begin(), key_pairs.end());

    // Read column-wise in the order of the sorted key
    std::string ciphertext;
    for (const auto& pair : key_pairs) {
        int col = pair.second;
        for (int r = 0; r < rows; ++r) {
            ciphertext += matrix[r][col];
        }
    }
    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, const std::string& key) {
    int cols = key.length();
    int rows = std::ceil(static_cast<double>(ciphertext.length()) / cols);
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols, 'X'));

    // Create permutation based on key
    std::vector<std::pair<char, int>> key_pairs;
    for (int i = 0; i < cols; ++i) {
        key_pairs.emplace_back(key[i], i);
    }
    std::sort(key_pairs.begin(), key_pairs.end());

    // Fill the matrix column-wise in the order of the sorted key
    int index = 0;
    for (const auto& pair : key_pairs) {
        int col = pair.second;
        for (int r = 0; r < rows; ++r) {
            if (index < ciphertext.length()) {
                matrix[r][col] = ciphertext[index++];
            }
        }
    }

    // Read row-wise to get plaintext
    std::string plaintext;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            plaintext += matrix[r][c];
        }
    }
    // Remove trailing 'X' padding if any
    while (!plaintext.empty() && plaintext.back() == 'X') {
        plaintext.pop_back();
    }
    return plaintext;
}

int main() {
    std::string key;
    std::cout << "Enter the key (e.g., KEY): ";
    std::getline(std::cin, key);

    if (key.empty()) {
        std::cout << "Key cannot be empty. Exiting." << std::endl;
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