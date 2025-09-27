# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Affine Cipher
### A. Lý thuyết
#### 1. Tên gọi
Affine Cipher là một dạng mã hóa thay thế đơn bảng (monoalphabetic substitution cipher), tức là mỗi ký tự trong bản rõ (plaintext) sẽ được ánh xạ thành một ký tự khác trong bản mã (ciphertext) theo một công thức toán học. Nó được xem là sự mở rộng của Caesar Cipher (vốn chỉ là phép dịch chuyển đơn giản).
#### 2. Thuật toán mã hóa và giải mã
##### a, Mã hóa
- Mỗi ký tự trong bản rõ được gán với một số tương ứng trong bảng chữ cái.
- Công thức mã hóa: <strong>C ≡ (aP + b) (mod 26) </strong>

Trong đó:
- P là kí tự bản rõ (dạng số)
- C là kí tự bản mã (dạng số)
- a,b là khóa, với điều kiện a và 26 phải nguyên tố cùng nhau để giải mã được
###### Thuật toán bằng lời:
- Chọn m. Chọn khóa a,b với gcd(a,m) = 1.

Với mỗi ký tự char trong plaintext:
- Lấy mã số P = code(char) trong khoảng 0..m-1.
- Tính C = (a * P + b) % m.
- Chuyển C về ký tự ciphertext bằng cách cộng offset ban đầu.
- Nối các ký tự để thành ciphertext.
##### b, Giải mã
Công thức giải mã: <strong>P ≡ a^-1 (C-b) (mod 26)</strong>

Trong đó a^-1 thỏa mãn: a.a^-1 ≡ 1 (mod 26)
###### Thuật toán bằng lời:
- Tính a^-1 modulo m (nghịch đảo của a).Nếu không tồn tại → dừng (khóa sai).

Với mỗi ký tự ciphertext char:
- C = code(ch) → 0..m-1.
- P = (a_inv * (C - b + m)) % m.
- Chuyển P về ký tự plaintext.
- Nối lại thành plaintext.
#### 3. Ưu điểm và nhược điểm
##### Ưu điểm:
- Dễ cài đặt, dễ hiểu.
- An toàn hơn Caesar Cipher (có nhiều khóa hơn).
- Sử dụng công thức toán học rõ ràng.
##### Nhược điểm:
- Vẫn thuộc nhóm mã hóa thay thế đơn bảng → dễ bị phá vỡ bằng tần suất chữ cái (frequency analysis).
- Không dùng được trong các hệ thống bảo mật hiện đại.
### B. Cài đặt
- Em thực hiện demo một file HTML + JavaScript đơn giản, có giao diện nhập chuỗi, chọn khóa a,b rồi bấm Mã hóa hoặc Giải mã để xem kết quả ngay, có thể nhập cả chữ thường, chữ hoa, số và ký tự đặc biệt. Thay vì chỉ làm việc với bảng chữ cái A–Z (26 ký tự), ta sẽ coi tất cả ký tự in được trong bảng ASCII (từ mã 32 → 126, tổng cộng 95 ký tự) đều tham gia mã hóa.
- Ngoài ra, em bổ sung thêm tính năng kiểm tra và gợi ý các giá trị a hợp lệ (những số nguyên tố cùng nhau với 95) ngay trên giao diện. Khi nhập khóa a không hợp lệ, chương trình sẽ báo lỗi và hiển thị danh sách các giá trị a có thể dùng.

#### Một số đoạn code chính trong chương trình cài đặt:
```html
  <script>
    const CHAR_START = 32; // khoảng trắng
    const CHAR_END = 126;  // ~
    const CHAR_RANGE = CHAR_END - CHAR_START + 1; // 95 ký tự

    // gcd
    function gcd(a, b) {
      return b === 0 ? a : gcd(b, a % b);
    }

    // nghịch đảo modulo
    function modInverse(a, m) {
      a = ((a % m) + m) % m;
      for (let x = 1; x < m; x++) {
        if ((a * x) % m === 1) return x;
      }
      return null;
    }

    // liệt kê tất cả giá trị a hợp lệ
    function validAValues() {
      let list = [];
      for (let i = 1; i < CHAR_RANGE; i++) {
        if (gcd(i, CHAR_RANGE) === 1) list.push(i);
      }
      return list;
    }

    function checkKeyA() {
      let a = parseInt(document.getElementById("keyA").value);
      let hintDiv = document.getElementById("keyAHint");

      if (isNaN(a)) {
        hintDiv.innerHTML = "<div class='bg-error/20 border border-error/30 rounded-lg p-3'><span class='text-red-200 font-medium'>⚠️ Vui lòng nhập số cho khóa a</span></div>";
        return;
      }

      if (gcd(a, CHAR_RANGE) !== 1) {
        hintDiv.innerHTML = "<div class='bg-error/20 border border-error/30 rounded-lg p-3'>" +
          "<span class='text-red-200 font-medium'>❌ a = " + a + " không hợp lệ</span><br>" +
          "<span class='text-red-100 text-sm'>👉 Các giá trị a hợp lệ: " + validAValues().slice(0, 20).join(", ") + "...</span></div>";
      } else {
        hintDiv.innerHTML = "<div class='bg-success/20 border border-success/30 rounded-lg p-3'>" +
          "<span class='text-green-200 font-medium'>✅ Hợp lệ (gcd(" + a + ", " + CHAR_RANGE + ") = 1)</span></div>";
      }
    }

    function encrypt() {
      let text = document.getElementById("inputText").value;
      let a = parseInt(document.getElementById("keyA").value);
      let b = parseInt(document.getElementById("keyB").value);

      if (gcd(a, CHAR_RANGE) !== 1) {
        document.getElementById("output").innerHTML = "<div class='text-red-300 font-semibold'>❌ Lỗi: Khóa 'a' không hợp lệ!</div>";
        return;
      }

      let result = "";
      for (let char of text) {
        let code = char.charCodeAt(0);
        if (code >= CHAR_START && code <= CHAR_END) {
          let P = code - CHAR_START;
          let C = (a * P + b) % CHAR_RANGE;
          result += String.fromCharCode(C + CHAR_START);
        } else {
          result += char;
        }
      }
      document.getElementById("output").innerHTML = "<div class='text-blue-200 font-semibold mb-2'>🔒 Bản mã:</div><div class='text-white'>" + result + "</div>";
    }

    function decrypt() {
      let text = document.getElementById("inputText").value;
      let a = parseInt(document.getElementById("keyA").value);
      let b = parseInt(document.getElementById("keyB").value);

      if (gcd(a, CHAR_RANGE) !== 1) {
        document.getElementById("output").innerHTML = "<div class='text-red-300 font-semibold'>❌ Lỗi: Khóa 'a' không hợp lệ!</div>";
        return;
      }

      let a_inv = modInverse(a, CHAR_RANGE);
      if (a_inv === null) {
        document.getElementById("output").innerHTML = "<div class='text-red-300 font-semibold'>❌ Lỗi: Không tìm được nghịch đảo modulo!</div>";
        return;
      }

      let result = "";
      for (let char of text) {
        let code = char.charCodeAt(0);
        if (code >= CHAR_START && code <= CHAR_END) {
          let C = code - CHAR_START;
          let P = (a_inv * (C - b + CHAR_RANGE)) % CHAR_RANGE;
          result += String.fromCharCode(P + CHAR_START);
        } else {
          result += char;
        }
      }
      document.getElementById("output").innerHTML = "<div class='text-green-200 font-semibold mb-2'>🔓 Bản rõ:</div><div class='text-white'>" + result + "</div>";
    }

    // hiển thị gợi ý ngay khi load
    window.onload = checkKeyA;
  </script>
```
#### Hình ảnh demo
Giao diện khởi chạy
<img width="3064" height="1824" alt="image" src="https://github.com/user-attachments/assets/20dd4ee9-adfd-4074-a199-332e698f6943" />

Với trường hợp khóa a hợp lệ và thực hiện mã hóa chuỗi "Hello everyone, I am Hieu and today I demo a program" thành bản mã:
<img width="3071" height="1823" alt="image" src="https://github.com/user-attachments/assets/e41ba52e-6740-4eae-9999-f61e73e47567" />
Copy bản mã vừa thu được rồi giải mã để kiểm tra chuỗi có đúng như ban đầu hay không:
<img width="3070" height="1821" alt="image" src="https://github.com/user-attachments/assets/ff8e9acb-b315-4d7e-b83e-330f8e690bff" />
Trong trường hợp nhập khóa a không hợp lệ, hệ thống sẽ cảnh báo và đề xuất:
<img width="3071" height="1817" alt="image" src="https://github.com/user-attachments/assets/8bc45b5f-39ae-41fa-91f0-7e063753bb20" />

#### Trên đây là toàn bộ bài làm của em. Tóm lại, Affine Cipher là một phương pháp mã hóa cổ điển dựa trên công thức tuyến tính trong số học modulo. Nó là bước phát triển cao hơn so với Caesar Cipher nhưng vẫn không đủ an toàn với công nghệ hiện nay.
