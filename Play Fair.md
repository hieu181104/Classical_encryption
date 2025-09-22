# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Playfair Cipher
### A. Lý thuyết
#### 1. Khái niệm
Playfair cipher được Charles Wheatstone phát minh năm 1854, nhưng được đặt theo tên của Lord Playfair (người đã quảng bá nó). Đây là một trong những mã khối (block cipher) cổ điển, hoạt động trên cặp chữ cái (digraphs) thay vì từng chữ cái riêng lẻ.

So với Caesar hay Affine (mã hóa trên từng ký tự), Playfair an toàn hơn vì khó phân tích tần suất.
#### 2. Nguyên tắc chính của phương pháp Playfair
Playfair sử dụng một bảng 5x5 chứa 25 chữ cái tiếng Anh (gộp I và J vào một ô).

Cách tạo bảng: Viết khóa vào bảng theo thứ tự, bỏ trùng lặp. Sau đó điền các chữ cái còn thiếu của bảng chữ cái.
#### 3. Quy tắc mã hóa và giải mã
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
#### 4. Ưu điểm và nhược điểm
##### Ưu điểm
- Khó phân tích tần suất vì mã hóa theo cặp, không theo từng chữ.
- Dễ dùng với giấy bút.
##### Nhược điểm
- Vẫn có thể bị phá bằng phân tích tần suất trên digraph (ví dụ “TH”, “ER”, “ON”…).
- Ngày nay không còn an toàn với máy tính, chỉ dùng trong nghiên cứu lịch sử mật mã.
### B. Cài đặt
Em sẽ cài đặt demo Playfair Cipher bằng JavaScript với giao diện đơn giản: nhập bản rõ + khóa → bấm nút để mã hóa hoặc giải mã.
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
