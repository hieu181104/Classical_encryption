# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Vigenere Cipher
### A. Lý thuyết
#### 1. Khái niệm
Vigenère Cipher là một phương pháp mã hóa cổ điển thuộc nhóm đa bảng (polyalphabetic cipher). Nó được Blaise de Vigenère giới thiệu vào thế kỷ 16. Điểm mạnh của Vigenère Cipher so với các phương pháp đơn bảng là sử dụng một khóa (key) gồm nhiều ký tự, giúp tăng tính bảo mật.
#### 2. Nguyên lý hoạt động
Bản rõ (Plaintext): Chuỗi thông tin gốc cần mã hóa.

Khóa (Key): Một từ hoặc cụm từ gồm các chữ cái. Khóa sẽ được lặp lại nhiều lần cho đến khi có cùng độ dài với bản rõ.

Bảng chữ cái Vigenère (Vigenère Table): Gồm 26 hàng, mỗi hàng là một phép dịch Caesar khác nhau.
##### Cách mã hóa:
Mỗi ký tự trong bản rõ sẽ được mã hóa bằng một phép dịch Caesar, trong đó số bước dịch phụ thuộc vào ký tự khóa tương ứng.

Công thức: <strong>Ci​=(Pi​+Ki​) mod 26</strong>

Trong đó: Ci là kí tự mã hóa, Pi là vị trí chữ cái của bản rõ, Ki là vị trí chữ cái của khóa.
##### Cách giải mã:
Thực hiện phép dịch ngược lại: <strong>Pi​=(Ci​−Ki​+26) mod 26</strong>
#### 3. Không gian khóa
Nếu dùng bảng chữ cái tiếng Anh 26 chữ (A–Z) và khóa dài k ký tự độc lập, thì số khóa khả dĩ: 26^k
#### 4. Cách phá mã mà không cần khóa
Dưới đây là một vài cách phá mã mà không cần khóa mà em tìm hiểu được:
##### Kasiski examination (tìm khoảng cách các cụm lặp) — để suy ra độ dài khóa 
Tìm các chuỗi con (ví dụ 3 ký tự trở lên) xuất hiện nhiều lần trong bản mã.
Ghi lại khoảng cách (số ký tự) giữa các lần lặp.
Lấy ước số chung (gcd) hoặc các ước số phổ biến của các khoảng cách đó — các ước khả dĩ là độ dài khóa m hoặc bội của nó.
Ví dụ: nếu thấy cụm “ABC” xuất hiện tại vị trí 10 và 34 → khoảng cách 24 → 24 = 2×12 = 3×8 … → ước số 2,3,4,6,8,12,24 là ứng viên cho m.
##### Friedman test — Index of Coincidence (IoC) — ước lượng độ dài khóa bằng chỉ số trùng lặp.
IoC cho một chuỗi ký tự là xác suất hai chữ cái ngẫu nhiên trùng nhau:
<img width="1617" height="212" alt="image" src="https://github.com/user-attachments/assets/82d41d57-8167-496f-a94f-eddd62f053ac" />

Giá trị tham khảo:

Văn bản tiếng Anh: 

IoC ≈ 0.066

IoC≈0.066 (thực tế ~0.065–0.073 tùy tập dữ liệu).

Chuỗi chữ cái ngẫu nhiên:

IoC ≈ 1/26 ≈0.03846

Có công thức ước lượng m (Friedman formula — dạng xấp xỉ):
<img width="1592" height="159" alt="image" src="https://github.com/user-attachments/assets/e9eb92f2-e549-4df6-895d-c15ebd7991ed" />
### B. Cài đặt
