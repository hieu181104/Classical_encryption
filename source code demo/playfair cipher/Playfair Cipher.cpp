#include <iostream>
#include <string>
#include <cctype>
#include <vector>

class PlayfairCipher {
private:
    std::vector<std::vector<char>> matrix; // 5x5 matrix
    std::string prepareKey(const std::string& key) {
        std::string cleanedKey;
        for (char c : key) {
            if (std::isalpha(c)) {
                cleanedKey += std::toupper(c) == 'J' ? 'I' : std::toupper(c);
            }
        }
        return cleanedKey;
    }

    void generateMatrix(const std::string& key) {
        matrix = std::vector<std::vector<char>>(5, std::vector<char>(5));
        std::string uniqueKey = prepareKey(key);
        std::vector<bool> used(26, false);
        used['J' - 'A'] = true; // Treat J as I

        // Fill matrix with key
        int row = 0, col = 0;
        for (char c : uniqueKey) {
            if (!used[c - 'A']) {
                matrix[row][col] = c;
                used[c - 'A'] = true;
                col++;
                if (col == 5) {
                    col = 0;
                    row++;
                }
            }
        }

        // Fill remaining matrix with alphabet
        for (char c = 'A'; c <= 'Z'; c++) {
            if (!used[c - 'A'] && c != 'J') {
                matrix[row][col] = c;
                col++;
                if (col == 5) {
                    col = 0;
                    row++;
                }
            }
        }
    }

    std::string prepareText(const std::string& text) {
        std::string result;
        for (char c : text) {
            if (std::isalpha(c)) {
                result += std::toupper(c) == 'J' ? 'I' : std::toupper(c);
            }
        }

        // Insert X between duplicate letters in a digraph
        std::string formatted;
        for (size_t i = 0; i < result.length(); i++) {
            formatted += result[i];
            if (i + 1 < result.length() && result[i] == result[i + 1]) {
                formatted += 'X';
            }
        }
        if (formatted.length() % 2 != 0) {
            formatted += 'X'; // Pad with X if odd length
        }
        return formatted;
    }

    void findPosition(char c, int& row, int& col) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (matrix[i][j] == c) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

public:
    PlayfairCipher(const std::string& key) {
        generateMatrix(key);
    }

    std::string encrypt(const std::string& plaintext) {
        std::string formattedText = prepareText(plaintext);
        std::string ciphertext;

        for (size_t i = 0; i < formattedText.length(); i += 2) {
            int row1, col1, row2, col2;
            findPosition(formattedText[i], row1, col1);
            findPosition(formattedText[i + 1], row2, col2);

            if (row1 == row2) {
                // Same row: shift right
                ciphertext += matrix[row1][(col1 + 1) % 5];
                ciphertext += matrix[row2][(col2 + 1) % 5];
            } else if (col1 == col2) {
                // Same column: shift down
                ciphertext += matrix[(row1 + 1) % 5][col1];
                ciphertext += matrix[(row2 + 1) % 5][col2];
            } else {
                // Rectangle: swap columns
                ciphertext += matrix[row1][col2];
                ciphertext += matrix[row2][col1];
            }
        }
        return ciphertext;
    }

    std::string decrypt(const std::string& ciphertext) {
        std::string formattedText = prepareText(ciphertext);
        std::string plaintext;

        for (size_t i = 0; i < formattedText.length(); i += 2) {
            int row1, col1, row2, col2;
            findPosition(formattedText[i], row1, col1);
            findPosition(formattedText[i + 1], row2, col2);

            if (row1 == row2) {
                // Same row: shift left
                plaintext += matrix[row1][(col1 - 1 + 5) % 5];
                plaintext += matrix[row2][(col2 - 1 + 5) % 5];
            } else if (col1 == col2) {
                // Same column: shift up
                plaintext += matrix[(row1 - 1 + 5) % 5][col1];
                plaintext += matrix[(row2 - 1 + 5) % 5][col2];
            } else {
                // Rectangle: swap columns
                plaintext += matrix[row1][col2];
                plaintext += matrix[row2][col1];
            }
        }
        return plaintext;
    }
};

int main() {
    std::string key;
    std::cout << "Enter the key (e.g., KEYWORD): ";
    std::getline(std::cin, key);

    if (key.empty()) {
        std::cout << "Key cannot be empty. Exiting." << std::endl;
        return 1;
    }

    PlayfairCipher cipher(key);

    int choice;
    std::cout << "Select operation: 1 for Encrypt, 2 for Decrypt: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear newline after reading choice

    std::string input;
    if (choice == 1) {
        std::cout << "Enter plaintext: ";
        std::getline(std::cin, input);
        std::string ciphertext = cipher.encrypt(input);
        std::cout << "Ciphertext: " << ciphertext << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter ciphertext: ";
        std::getline(std::cin, input);
        std::string decrypted = cipher.decrypt(input);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    return 0;
}