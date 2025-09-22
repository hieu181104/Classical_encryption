# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Caesar Cipher
### A. Lý thuyết
#### 1. Khái niệm
  Caesar Cipher là một trong những phương pháp mã hóa cổ điển đơn giản nhất, được Julius Caesar (La Mã cổ đại) sử dụng để trao đổi thông tin quân sự. Đây là dạng mã hóa thay thế đơn bảng (monoalphabetic substitution cipher), trong đó mỗi ký tự trong bản rõ (plaintext) được thay thế bằng một ký tự khác trong bảng chữ cái theo một số bước dịch chuyển cố định.
#### 2. Nguyên lý hoạt động
Giả sử ta có bảng chữ cái tiếng Anh gồm 26 kí tự (A-Z):

- Chọn một số nguyên k (0 <= k <= 25) làm khóa (key)

- Mỗi kí tự trong bản rõ sẽ được dịch sang phải k vị trí trong bảng chữ cái để tạo ra bản mã (ciphertext).

Ví dụ: Với k = 3 thì A => D, B => E, C => F,...

<strong>Công thức toán học:</strong>

Với P là bản rõ:

-  C (bản mã): <strong>C = (P+k) mod 26</strong>

- Giải mã: <strong>P = (C-k) mod 26</strong>

#### 3. Ưu điểm và nhược điểm
##### Ưu điểm:
- Đơn giản, dễ hiểu và dễ thực hiện.
- Là nền tảng nghiên cứu các phương pháp mã hóa phức tạp hơn.
##### Nhược điểm:
- Độ an toàn rất thấp bởi chỉ có 25 khóa khả dĩ, dễ dàng bị phá bằng thử hết (brute-force).
- Có thể bị phân tích tần suất chữ cái để đoán ra bản rõ.
### B. Cài đặt
