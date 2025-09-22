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
