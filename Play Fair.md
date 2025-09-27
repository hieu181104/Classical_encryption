# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Playfair Cipher
### A. Lý thuyết
#### 1. Tên gọi
- Playfair cipher được Charles Wheatstone phát minh năm 1854, nhưng được đặt theo tên của Lord Playfair (người đã quảng bá nó). Đây là một trong những mã khối (block cipher) cổ điển, hoạt động trên cặp chữ cái (digraphs) thay vì từng chữ cái riêng lẻ.
- So với Caesar hay Affine (mã hóa trên từng ký tự), Playfair an toàn hơn vì khó phân tích tần suất.
#### 2. Nguyên tắc chính của phương pháp Playfair
- Playfair sử dụng một bảng 5x5 chứa 25 chữ cái tiếng Anh (gộp I và J vào một ô).
- Cách tạo bảng: Viết khóa vào bảng theo thứ tự, bỏ trùng lặp. Sau đó điền các chữ cái còn thiếu của bảng chữ cái.
#### 3. Thuật toán mã hóa và giải mã
##### Mã hóa
Chia bản rõ thành các cặp chữ:
- Nếu hai chữ cái trùng nhau ( Ví dụ: MEET -> ME EX T) thì thêm chữ X vào giữa.
- Nếu còn dư một chữ, thêm X vào cuối.
Mã hóa theo từng cặp:
- Cùng hàng: thay mỗi chữ bằng chữ bên phải nó (nếu ở cuối hàng thì vòng lại đầu hàng).
- Cùng cột: thay mỗi chữ bằng chữ ngay dưới nó (nếu ở cuối cột thì vòng lại đầu cột).
- Khác hàng, khác cột: mỗi chữ được thay bằng chữ nằm cùng hàng nhưng ở cột của chữ còn lại (tạo thành hình chữ nhật).
##### Giải mã
Giải mã ngược lại:
- Cùng hàng: thay bằng chữ bên trái.
- Cùng cột: thay bằng chữ bên trên.
- Khác hàng, khác cột: áp dụng quy tắc chữ nhật như khi mã hóa.
#### 4. Không gian khóa
Về mặt lý thuyết, bảng 5×5 là một hoán vị của 25 chữ cái → có 25! (25 factorial) ma trận khác nhau.

25! ≈ 1.5511210043 × 10^25.

Tính bằng bit: log2(25!) ≈ 83.7 bits.

Trong thực tế khóa mạnh phụ thuộc lớn vào cách người dùng tạo khóa (passphrase dài & ngẫu nhiên → tốt hơn).
#### 5. Cách phá mã (mà không cần khóa)
###### Brute-force toàn bộ không gian
- Thử tất cả 25! ≈ 1.55e25 khóa là không thực tế bằng brute force thuần.
- Tuy nhiên nếu khóa giới hạn bởi passphrase ngắn (ví dụ người dùng gõ 6 chữ cái), thì không gian thử nghiệm nhỏ hơn nhiều — có thể thử dò passphrase nếu biết cấu trúc.
###### Phân tích tần suất digraph (thủ công / bán tự động)
- Thu thập tần suất digraph trong bản mã (mật văn): đếm số lần xuất hiện của mỗi cặp hai chữ.
- So sánh bảng tần suất với thống kê digraph tiếng mục tiêu (ví dụ tiếng Anh hay tiếng Việt): digraph phổ biến như TH, HE, IN, ER, AN (tiếng Anh) — trong Playfair, những digraph này sẽ bị ánh xạ thành một số cặp nhất định.
- Dò các ánh xạ khả dĩ dựa trên tần suất: ví dụ digraph mật văn có tần suất cao có thể tương ứng với TH/HE...
- Dùng suy luận về các cặp chữ xuất hiện cùng lúc (ví dụ các cặp lặp lại), xác lập từng phần của bảng 5×5 dần dần.
### B. Cài đặt
#### Demo HTML+CSS+JS
Em sẽ cài đặt demo Playfair Cipher với giao diện đơn giản: nhập bản rõ + khóa → bấm nút để mã hóa hoặc giải mã.
#### Một số đoạn code chính trong chương trình demo:
```html
  <script>
    function generateMatrix(key) {
      key = key.toUpperCase().replace(/J/g, "I").replace(/[^A-Z]/g, "");
      let seen = new Set();
      let matrix = [];
      let alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // I/J gộp chung
      let combined = key + alphabet;

      for (let ch of combined) {
        if (!seen.has(ch)) {
          seen.add(ch);
          matrix.push(ch);
        }
      }
      return matrix; // 25 ký tự
    }

    function preprocessText(text, forEncrypt = true) {
      text = text.toUpperCase().replace(/J/g, "I").replace(/[^A-Z]/g, "");
      if (!forEncrypt) return text;

      let result = "";
      for (let i = 0; i < text.length; i++) {
        let a = text[i];
        let b = text[i + 1] || "";
        if (a === b) {
          result += a + "X";
        } else {
          if (b) {
            result += a + b;
            i++;
          } else {
            result += a + "X";
          }
        }
      }
      return result;
    }

    function findPos(matrix, ch) {
      let index = matrix.indexOf(ch);
      return [Math.floor(index / 5), index % 5];
    }

    function encrypt() {
      let key = document.getElementById("key").value;
      let text = preprocessText(document.getElementById("inputText").value, true);
      let matrix = generateMatrix(key);
      let result = "";

      for (let i = 0; i < text.length; i += 2) {
        let a = text[i], b = text[i + 1];
        let [rowA, colA] = findPos(matrix, a);
        let [rowB, colB] = findPos(matrix, b);

        if (rowA === rowB) {
          result += matrix[rowA * 5 + (colA + 1) % 5];
          result += matrix[rowB * 5 + (colB + 1) % 5];
        } else if (colA === colB) {
          result += matrix[((rowA + 1) % 5) * 5 + colA];
          result += matrix[((rowB + 1) % 5) * 5 + colB];
        } else {
          result += matrix[rowA * 5 + colB];
          result += matrix[rowB * 5 + colA];
        }
      }
      document.getElementById("outputText").value = result;
    }

    function decrypt() {
      let key = document.getElementById("key").value;
      let text = preprocessText(document.getElementById("inputText").value, false);
      let matrix = generateMatrix(key);
      let result = "";

      for (let i = 0; i < text.length; i += 2) {
        let a = text[i], b = text[i + 1];
        let [rowA, colA] = findPos(matrix, a);
        let [rowB, colB] = findPos(matrix, b);

        if (rowA === rowB) {
          result += matrix[rowA * 5 + (colA + 4) % 5];
          result += matrix[rowB * 5 + (colB + 4) % 5];
        } else if (colA === colB) {
          result += matrix[((rowA + 4) % 5) * 5 + colA];
          result += matrix[((rowB + 4) % 5) * 5 + colB];
        } else {
          result += matrix[rowA * 5 + colB];
          result += matrix[rowB * 5 + colA];
        }
      }
      document.getElementById("outputText").value = result;
    }
  </script>
```
#### Hình ảnh demo
Giao diện demo:
<img width="3069" height="1818" alt="Screenshot 2025-09-22 213104" src="https://github.com/user-attachments/assets/54c9431f-f217-4a7f-ad36-7a0f4dc597f2" />

Nhập khóa và chuỗi chữ để Mã hóa:
<img width="3071" height="1823" alt="Screenshot 2025-09-22 213547" src="https://github.com/user-attachments/assets/bd0503d3-ff6f-46ab-aab5-be25bbf257e3" />

Thực hiện giải mã chuỗi vừa mã hóa để kiểm tra xem kết quả có giống bản rõ không:
<img width="3071" height="1820" alt="Screenshot 2025-09-22 213622" src="https://github.com/user-attachments/assets/6255886e-57eb-4df8-934b-d52b245b07a5" />

#### Demo C++:
##### Một số đoạn code chính:
```cpp
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
```
##### Hình ảnh demo:
<img width="2343" height="1220" alt="Screenshot 2025-09-27 161754" src="https://github.com/user-attachments/assets/b54a46b7-3cf9-43a4-9460-5c3b8ac5464f" />
<img width="2337" height="1221" alt="Screenshot 2025-09-27 161841" src="https://github.com/user-attachments/assets/b97cb45a-4c75-4184-a56b-dfd7618e281a" />

#### Như vậy Playfair Cipher là một trong những phương pháp mã hóa cổ điển quan trọng, ra đời sớm và được xem là bước tiến so với các hệ đơn bảng như Caesar hay Affine. Với cách mã hóa theo cặp ký tự, Playfair giúp hạn chế phân tích tần suất, tăng độ an toàn. Tuy nhiên, ngày nay nó không còn đủ mạnh để bảo mật thông tin.
