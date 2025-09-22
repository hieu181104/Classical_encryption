# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Affine Cipher
### A. Lý thuyết
#### 1. Khái niệm
Affine Cipher là một dạng mã hóa thay thế đơn bảng (monoalphabetic substitution cipher), tức là mỗi ký tự trong bản rõ (plaintext) sẽ được ánh xạ thành một ký tự khác trong bản mã (ciphertext) theo một công thức toán học.

Nó được xem là sự mở rộng của Caesar Cipher (vốn chỉ là phép dịch chuyển đơn giản).
#### 2. Công thức mã hóa và giải mã
##### a, Mã hóa
Mỗi ký tự trong bản rõ được gán với một số tương ứng trong bảng chữ cái.

Ví dụ: A = 0, B = 1, …, Z = 25.

Công thức mã hóa: <strong>C ≡ (aP + b) (mod 26) </strong>

Trong đó:

- P là kí tự bản rõ (dạng số)
- C là kí tự bản mã (dạng số)
- a,b là khóa, với điều kiện a và 26 phải nguyên tố cùng nhau để giải mã được
##### b, Giải mã
Để giải mã, ta cần tìm nghịch đảo modulo của a, gọi là a^-1

Công thức giải mã: <strong>P ≡ a^-1 (C-b) (mod 26)</strong>

Trong đó a^-1 thỏa mãn: a.a^-1 ≡ 1 (mod 26)
#### 3. Ưu điểm và nhược điểm
##### Ưu điểm:
- Dễ cài đặt, dễ hiểu.
- An toàn hơn Caesar Cipher (có nhiều khóa hơn).
- Sử dụng công thức toán học rõ ràng.
##### Nhược điểm:
- Vẫn thuộc nhóm mã hóa thay thế đơn bảng → dễ bị phá vỡ bằng tần suất chữ cái (frequency analysis).
- Không dùng được trong các hệ thống bảo mật hiện đại.
### B. Cài đặt
