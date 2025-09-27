# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Caesar Cipher
### A. Lý thuyết
#### 1. Tên gọi
  Caesar Cipher là một trong những phương pháp mã hóa cổ điển đơn giản nhất, được Julius Caesar (La Mã cổ đại) sử dụng để trao đổi thông tin quân sự. Đây là dạng mã hóa thay thế đơn bảng (monoalphabetic substitution cipher), trong đó mỗi ký tự trong bản rõ (plaintext) được thay thế bằng một ký tự khác trong bảng chữ cái theo một số bước dịch chuyển cố định.
#### 2. Thuật toán mã hóa và giải mã
Giả sử ta có bảng chữ cái gồm m ký tự (ví dụ: tiếng Anh có m = 26):
- Chọn một số nguyên k (0 <= k <= m) làm khóa (key)
##### Mã hóa:
Với P là bản rõ, C là bản mã, ta có:
- <strong>C = (P+k) mod m</strong>
##### Giải mã:
- <strong>P = (C-k) mod m</strong>

Độ phức tạp thuật toán: mã hóa/giải mã đều O(n) với n = số ký tự
#### 3. Không gian khóa
- Nếu chỉ dịch trong bảng chữ cái tiếng Anh (A–Z): m = 26.

Khóa khả dĩ: k = 0,1,…,25 → 25 khóa hữu ích (k = 0 là khóa vô tác dụng).
- Nếu áp dụng lên chữ + số (ví dụ A–Z + 0–9) kích thước tăng lên tương ứng.
- Nếu áp dụng trên từng byte (0–255): m = 256 → 256 khóa.

Kết luận: keyspace rất nhỏ → dễ tấn công bằng brute-force.
#### 4. Cách phá mã (mà không cần khóa)
Ta có thể dùng Brute-force (thử tất cả khóa)
- Thử mọi k trong keyspace, giải mã và kiểm tra kết quả. Với m=26, chỉ 25 thử — cực nhanh.
- Thường dùng để lấy ra bản rõ đọc được bằng mắt người hoặc bằng kiểm tra ngôn ngữ (dictionary / heuristic).
Thời gian: O(m · n).
### B. Cài đặt
#### Demo HTML+CSS+JS
Em đã thực hiện demo phương pháp này với HTML+CSS+JS để thực hiện mã hóa/ giải mã. Dưới đây là một số đoạn code chính:
```html
<body>
  <div class="container">
    <h1>Caesar Cipher Demo</h1>

    <!-- Phần 1: Mã hóa/Giải mã chuỗi ký tự -->
    <div class="section">
      <h2>🔤 Mã hóa / Giải mã Chuỗi</h2>
      <div class="form-group">
        <label>Chuỗi nhập vào:</label>
        <input type="text" id="inputText" placeholder="Nhập văn bản cần mã hóa/giải mã...">
      </div>
      <div class="form-group">
        <label>Khóa (số dịch chuyển):</label>
        <input type="number" id="shiftText" value="3" min="0" max="25">
      </div>
      <div class="button-group">
        <button onclick="encryptText()">🔒 Mã hóa</button>
        <button onclick="decryptText()">🔓 Giải mã</button>
      </div>
      <div class="output">
        <strong>Kết quả:</strong>
        <p id="resultText">Kết quả sẽ hiển thị ở đây...</p>
      </div>
    </div>

    <!-- Phần 2: Mã hóa/Giải mã ảnh -->
    <div class="section">
      <h2>🖼️ Mã hóa / Giải mã Ảnh</h2>
      <div class="form-group">
        <label>Chọn ảnh:</label>
        <input type="file" id="fileInput" accept="image/*">
      </div>
      <div class="form-group">
        <label>Khóa dịch chuyển:</label>
        <input type="number" id="shiftImg" value="50" min="1" max="255">
      </div>
      <div class="button-group">
        <button onclick="encryptImage()">🔒 Mã hóa Ảnh</button>
        <button onclick="decryptImage()">🔓 Giải mã Ảnh</button>
      </div>
      <div class="output">
        <strong>Xem trước ảnh gốc:</strong><br>
        <img id="preview" alt="Ảnh gốc sẽ hiển thị ở đây" style="display: none;">
      </div>
    </div>
  </div>

  <script>
    function caesarCipher(str, shift) {
      return str.split('').map(char => {
        let code = char.charCodeAt(0);

        // Chữ hoa A-Z
        if (code >= 65 && code <= 90) {
          return String.fromCharCode(((code - 65 + shift) % 26 + 26) % 26 + 65);
        }
        // Chữ thường a-z
        else if (code >= 97 && code <= 122) {
          return String.fromCharCode(((code - 97 + shift) % 26 + 26) % 26 + 97);
        }
        // Số 0-9
        else if (code >= 48 && code <= 57) {
          return String.fromCharCode(((code - 48 + shift) % 10 + 10) % 10 + 48);
        }
        // Giữ nguyên ký tự khác
        return char;
      }).join('');
    }

    function encryptText() {
      let text = document.getElementById("inputText").value;
      let shift = parseInt(document.getElementById("shiftText").value);
      let result = caesarCipher(text, shift);
      document.getElementById("resultText").innerText = result;
    }

    function decryptText() {
      let text = document.getElementById("inputText").value;
      let shift = parseInt(document.getElementById("shiftText").value);
      let result = caesarCipher(text, -shift);
      document.getElementById("resultText").innerText = result;
    }

    let originalBuffer = null;

    document.getElementById("fileInput").addEventListener("change", function(e) {
      const file = e.target.files[0];
      if (file) {
        const reader = new FileReader();
        reader.onload = function(evt) {
          originalBuffer = evt.target.result;
          const preview = document.getElementById("preview");
          preview.src = URL.createObjectURL(file);
          preview.style.display = "block";
        };
        reader.readAsArrayBuffer(file);
      }
    });

    function caesarCipherBuffer(buffer, shift) {
      const data = new Uint8Array(buffer);
      for (let i = 0; i < data.length; i++) {
        data[i] = (data[i] + shift + 256) % 256;
      }
      return data;
    }

    function downloadFile(data, filename) {
      const blob = new Blob([data], { type: "application/octet-stream" });
      const url = URL.createObjectURL(blob);
      const a = document.createElement("a");
      a.href = url;
      a.download = filename;
      a.click();
      URL.revokeObjectURL(url);
    }

    function encryptImage() {
      if (!originalBuffer) return alert("Chưa chọn ảnh!");
      const shift = parseInt(document.getElementById("shiftImg").value);
      const encrypted = caesarCipherBuffer(originalBuffer, shift);
      downloadFile(encrypted, "encrypted.jpg");
    }

    function decryptImage() {
      if (!originalBuffer) return alert("Chưa chọn ảnh!");
      const shift = parseInt(document.getElementById("shiftImg").value);
      const decrypted = caesarCipherBuffer(originalBuffer, -shift);
      downloadFile(decrypted, "decrypted.jpg");
    }
  </script>
</body>
```
##### Cách thực hiện:
Phần 1: Mã hóa/ Giải mã chuỗi
- Nhập chuỗi, nhập khóa rồi nhấn nút Mã hóa/ Giải mã để nhận kết quả

Phần 2: Mã hóa/ Giải mã ảnh
- Chọn một ảnh từ máy tính
- Nhập khóa
- Nhấn Mã hóa ảnh => tải về file ảnh đã mã hóa (vì sau khi mã hóa, dữ liệu của ảnh đã bị biến đổi nên không thể xem được ảnh)
- Nhấn Giải mã ảnh => tải về file ảnh sau khi giải mã (xem được bình thường).
##### Hình ảnh demo
##### 1. Giao diện demo
<img width="3070" height="1817" alt="image" src="https://github.com/user-attachments/assets/6d8dcb3b-9efb-41bf-b308-5b808fd66146" />

##### 2. Mã hóa một chuỗi "HELLO" với khóa = 3
<img width="3070" height="1817" alt="image" src="https://github.com/user-attachments/assets/350abd49-540f-4196-b96c-4666120ad5d1" />

##### 3. Giải mã ngược lại chuỗi đã mã hóa của bản rõ "HELLO"
<img width="3071" height="1814" alt="image" src="https://github.com/user-attachments/assets/fbba7e5f-ecea-4caa-9397-7ade5cef1705" />

##### 4. Thực hiện tương tự với dãy số
Mã hóa dãy số
<img width="3071" height="1812" alt="image" src="https://github.com/user-attachments/assets/eccfcf81-f3a8-40e9-a5cf-e2c762e6c0c7" />
Giải mã dãy số
<img width="3071" height="1817" alt="image" src="https://github.com/user-attachments/assets/fe6715ce-3f67-4565-8393-f7c7e11ef788" />

##### 5. Mã hóa ảnh và giải mã ảnh
Tải lên ảnh từ thiết bị và nhập khóa
<img width="3071" height="1816" alt="image" src="https://github.com/user-attachments/assets/802885a2-0039-4cad-a828-0b24eaa40048" />
<img width="3071" height="1817" alt="image" src="https://github.com/user-attachments/assets/ca1770ed-8539-4f9f-a622-6272b012cc0c" />
Sau khi bấm Mã hóa Ảnh thì file đã mã hóa sẽ tự động tải về máy.
<img width="3071" height="1814" alt="image" src="https://github.com/user-attachments/assets/e7641572-ff48-4a27-80b4-e70810a6fbe8" />
Bây giờ chọn lại file vừa tải xuống để thực hiện giải mã, ta sẽ thu về file ảnh giải mã giống với ảnh ban đầu.
<img width="3068" height="1817" alt="image" src="https://github.com/user-attachments/assets/46aa9bce-a0f4-4303-a212-a2d4e050e301" />
<img width="3071" height="1817" alt="image" src="https://github.com/user-attachments/assets/579271a1-670f-4119-abc8-a818c4f40f6c" />
<strong>Nhận thấy ở đây cả file mã hóa và giải mã có cùng kích thước tệp.</strong>
<img width="2445" height="495" alt="image" src="https://github.com/user-attachments/assets/e0fbdbc8-3478-495b-b59e-85472e65699b" />
<strong>Sau khi mở file giải mã ta thu được ảnh giống ban đầu. </strong>
<img width="3071" height="1820" alt="image" src="https://github.com/user-attachments/assets/333efe1a-c22d-4a18-9d99-9bac0628bf09" />

#### Demo C++
Ở chương trình này, em chỉ demo mã hóa/ giải mã chuỗi ký tự:
##### Một số đoạn code chính:
```cpp
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
```
##### Hình ảnh demo:
<img width="2338" height="1209" alt="Screenshot 2025-09-27 161331" src="https://github.com/user-attachments/assets/e8998428-eabc-482d-842e-6274fc83c633" />
<img width="2342" height="1215" alt="Screenshot 2025-09-27 161410" src="https://github.com/user-attachments/assets/adfb30b3-6239-4776-9d7d-68e4a7c0c450" />

### -------------------------------------------------HẾT-------------------------------------------------
