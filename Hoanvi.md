# Classical_encryption
Bài tập về các phương pháp mã hóa cổ điển
## Thông tin cá nhân
#### Họ và tên : Nguyễn Trung Hiếu
#### Mã SV: K225480106019
#### Lớp: K58KTP
## Phương pháp mã hóa Transposition Cipher
### A. Lý thuyết
#### 1. Tên gọi
Hoán vị (Transposition cipher) còn gọi là mã hoán vị, mã tráo vị trí.

Ý tưởng: Giữ nguyên các ký tự (tần suất, ký tự không thay đổi) nhưng thay đổi vị trí của chúng theo một quy tắc (permute). Kết quả là một hoán vị của bản rõ — chữ cái không bị thay thế, chỉ bị tráo chỗ.

Các dạng phổ biến:

- Columnar transposition (chuyển cột) — xếp văn bản theo hàng vào một bảng có số cột dựa trên khóa dạng từ/chuỗi, rồi đọc theo thứ tự cột được sắp xếp theo khóa.

- Route transposition — viết vào lưới theo một “lộ trình” (row-major, spiral, zig-zag...) rồi đọc theo một lộ trình khác.

- General block permutation — chia thành khối cố định kích thước n, áp dụng một hoán vị perm của n ký tự trong mỗi khối.
#### 2. Thuật toán mã hóa và giải mã
Giả sử:
- Ta có plaintext: WEAREDISCOVEREDFLEEATONCE
- Khóa là từ "ZEBRAS" — ta dùng thứ tự chữ cái tăng dần của khóa để xác định thứ tự cột.
##### Mã hóa:
- Loại bỏ/hoặc giữ khoảng trắng theo quy ước (thường bỏ khoảng trắng, dấu chấm).
- Tạo một bảng với số cột = độ dài khóa (ở đây 6 vì "ZEBRAS"). Viết plaintext theo hàng.
- Đánh số các cột bằng thứ tự sắp chữ của các chữ trong khóa:
- Khóa "Z E B R A S" → chữ cái theo thứ tự: A(5), B(3), E(2), R(4), S(6), Z(1) → ta gán thứ tự cột tương ứng.
- Đọc ciphertext bằng cách lấy cột theo thứ tự số (1,2,3,...).
##### Giải mã:
Biết m (độ dài khóa) và thứ tự cột, ta chia ciphertext thành m đoạn độ dài rows (hoặc có thể khác nhau nếu padding không đều), rồi điền vào cột theo thứ tự và đọc hàng-wise để phục hồi plaintext.
#### 3. Không gian khóa
Không gian khóa phụ thuộc loại hoán vị:
- Hoán vị khối kích thước n (block permutation): mọi hoán vị của n phần tử → kích thước khóa = n! (giai thừa). VD n=8 → 8! = 40,320 khả năng.
- Columnar transposition với khóa độ dài m: nếu khóa là một sắp thứ tự duy nhất thì số khóa ≈ m! (nhiều khóa trùng có thể do lặp chữ trong khóa làm giảm số thực tế).
Ví dụ m=6 → 6! = 720.
- Route transposition: số lớp đường đi có thể lớn tùy định nghĩa, nhưng thường cũng nằm trong bậc O(m! ) hoặc nhiều hơn nếu kết hợp nhiều tham số.

Nhận xét: Vì n! tăng rất nhanh, với n lớn không gian khóa rất lớn. Tuy nhiên, trên văn bản dài, các phương pháp tấn công dựa trên thống kê (không brute-force toàn bộ) vẫn có thể phục hồi khóa có hiệu quả.
#### 4. Cách phá mã (mà không cần khóa)
Hoán vị bảo toàn tần suất ký tự — điều này vừa là điểm yếu, vừa tạo nền tảng cho tấn công. Dưới đây là một số chiến lược phá mã không cần khóa:
##### Phân tích thống kê / sử dụng crib (known plaintext / probable words)
vì tần suất chữ cái không đổi, ta có thể dùng cribs (đoán từ xuất hiện như "THE", "AND", tên riêng) và thử căn chỉnh crib vào nhiều vị trí của ciphertext để suy ra hoán vị cột/offset hợp lý.

“Crib-dragging”: thử dịch/hoán vị sao cho xuất hiện từ có nghĩa ở vị trí nào đó.
##### Hill-climbing / Simulated annealing / Genetic algorithms
Các thuật toán tìm kiếm heuristics (hill-climbing) dùng điểm số ngôn ngữ (log-likelihood theo mô hình n-gram) để đánh giá một giải mã tạm thời; sau đó thay đổi perm (swap cột, hoán vị) để cải thiện điểm.

Phương pháp này rất hiệu quả cho columnar transposition hoặc hoán vị khối lớn khi brute-force không khả thi. Nhiều công cụ mật mã cổ điển nổi tiếng dùng hill-climbing để phá transposition.

Ví dụ: Giả sử ciphertext dài ~ several hundred chữ: chạy hill-climbing với khởi tạo ngẫu nhiên perm, điểm đánh giá = log-probability theo trigram tiếng Việt/Anh; thao tác chuyển đổi = hoán đổi hai cột; giữ giải pháp tốt nhất; chạy nhiều lần với restarts. Kỹ thuật này thường hồi phục được hoán vị cột (khóa) và do đó giải mã thành bản rõ có nghĩa.
### B. Cài đặt
