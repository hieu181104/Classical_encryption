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
- Vì tần suất chữ cái không đổi, ta có thể dùng cribs (đoán từ xuất hiện như "THE", "AND", tên riêng) và thử căn chỉnh crib vào nhiều vị trí của ciphertext để suy ra hoán vị cột/offset hợp lý.
- “Crib-dragging”: thử dịch/hoán vị sao cho xuất hiện từ có nghĩa ở vị trí nào đó.
##### Hill-climbing / Simulated annealing / Genetic algorithms
- Các thuật toán tìm kiếm heuristics (hill-climbing) dùng điểm số ngôn ngữ (log-likelihood theo mô hình n-gram) để đánh giá một giải mã tạm thời; sau đó thay đổi perm (swap cột, hoán vị) để cải thiện điểm.
- Phương pháp này rất hiệu quả cho columnar transposition hoặc hoán vị khối lớn khi brute-force không khả thi. Nhiều công cụ mật mã cổ điển nổi tiếng dùng hill-climbing để phá transposition.

Ví dụ: Giả sử ciphertext dài ~ several hundred chữ: chạy hill-climbing với khởi tạo ngẫu nhiên perm, điểm đánh giá = log-probability theo trigram tiếng Việt/Anh; thao tác chuyển đổi = hoán đổi hai cột; giữ giải pháp tốt nhất; chạy nhiều lần với restarts. Kỹ thuật này thường hồi phục được hoán vị cột (khóa) và do đó giải mã thành bản rõ có nghĩa.
### B. Cài đặt
#### Demo JS+CSS+HTML
Em đã thực hiện demo phương pháp này bằng html+css+js.Dưới đây là một số đoạn code chính:
```html
<script>
function keyOrder(key) {
  const arr = [];
  for (let i = 0; i < key.length; ++i) arr.push({ch: key[i], idx: i});
  arr.sort((a,b) => {
    if (a.ch < b.ch) return -1;
    if (a.ch > b.ch) return 1;
    return a.idx - b.idx;
  });
  return arr.map(x => x.idx);
}

// encrypt: plaintext -> ciphertext
function encryptColumnar(plaintext, key, padChar='X') {
  if (!key || key.length === 0) return plaintext;
  const m = key.length;
  const L = plaintext.length;
  const rows = Math.ceil(L / m);
  // build matrix rows x m and fill row-wise
  const matrix = Array.from({length: rows}, () => Array.from({length: m}, () => padChar));
  let pos = 0;
  for (let r = 0; r < rows; ++r) {
    for (let c = 0; c < m; ++c) {
      if (pos < L) matrix[r][c] = plaintext[pos++];
      else matrix[r][c] = padChar;
    }
  }
  const order = keyOrder(key);
  let cipher = '';
  for (let k = 0; k < order.length; ++k) {
    const c = order[k];
    for (let r = 0; r < rows; ++r) cipher += matrix[r][c];
  }
  return {cipher, matrix, rows};
}

// decrypt: ciphertext -> plaintext
function decryptColumnar(ciphertext, key, padChar='X') {
  if (!key || key.length === 0) return ciphertext;
  const m = key.length;
  const L = ciphertext.length;
  const rows = Math.ceil(L / m);
  // create empty matrix rows x m
  const matrix = Array.from({length: rows}, () => Array.from({length: m}, () => ''));
  const order = keyOrder(key);
  // Fill columns in the order sequence; allow ciphertext shorter than rows*m
  let pos = 0;
  for (let k = 0; k < order.length; ++k) {
    const c = order[k];
    for (let r = 0; r < rows; ++r) {
      if (pos < L) matrix[r][c] = ciphertext[pos++];
      else matrix[r][c] = padChar; // fallback
    }
  }
  // read row-wise
  let plain = '';
  for (let r = 0; r < rows; ++r) {
    for (let c = 0; c < m; ++c) {
      plain += matrix[r][c];
    }
  }
  // strip trailing padding characters that were added during encryption
  while (plain.endsWith(padChar)) plain = plain.slice(0, -1);
  return {plain, matrix, rows};
}

// UI wiring
const inputText = document.getElementById('inputText');
const outputText = document.getElementById('outputText');
const keyInput = document.getElementById('keyInput');
const padInput = document.getElementById('padInput');
const encryptBtn = document.getElementById('encryptBtn');
const decryptBtn = document.getElementById('decryptBtn');
const showMatrixBtn = document.getElementById('showMatrixBtn');
const matrixWrap = document.getElementById('matrixWrap');
const matrixArea = document.getElementById('matrixArea');
const metaInfo = document.getElementById('metaInfo');
const copyOut = document.getElementById('copyOut');
const clearAll = document.getElementById('clearAll');
const exampleBtn = document.getElementById('exampleBtn');

function renderMatrix(matrix) {
  if (!matrix) { matrixArea.innerHTML = '<div class="small">Không có matrix để hiển thị.</div>'; return; }
  const rows = matrix.length;
  const cols = matrix[0].length;
  let html = '<table class="m">';
  for (let r = 0; r < rows; ++r) {
    html += '<tr>';
    for (let c = 0; c < cols; ++c) {
      const ch = matrix[r][c] === '' ? '&nbsp;' : escapeHtml(matrix[r][c]);
      html += `<td>${ch}</td>`;
    }
    html += '</tr>';
  }
  html += '</table>';
  matrixArea.innerHTML = html;
}

function escapeHtml(s) {
  return s.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/ /g, '&nbsp;');
}

encryptBtn.addEventListener('click', ()=> {
  const pt = inputText.value;
  const k = keyInput.value;
  const pad = (padInput.value && padInput.value[0]) ? padInput.value[0] : 'X';
  if (!k || k.length === 0) {
    alert('Vui lòng nhập khóa (key) trước khi mã hóa.');
    return;
  }
  const {cipher, matrix, rows} = encryptColumnar(pt, k, pad);
  outputText.value = cipher;
  metaInfo.textContent = `Đã mã hóa — chiều dài plaintext=${pt.length}, keyLength=${k.length}, rows=${rows}, cipherLength=${cipher.length}`;
  if (matrixWrap.style.display !== 'none') renderMatrix(matrix);
});

decryptBtn.addEventListener('click', ()=> {
  const ct = inputText.value;
  const k = keyInput.value;
  const pad = (padInput.value && padInput.value[0]) ? padInput.value[0] : 'X';
  if (!k || k.length === 0) {
    alert('Vui lòng nhập khóa (key) trước khi giải mã.');
    return;
  }
  const {plain, matrix, rows} = decryptColumnar(ct, k, pad);
  outputText.value = plain;
  metaInfo.textContent = `Đã giải mã — chiều dài ciphertext=${ct.length}, keyLength=${k.length}, rows=${rows}, plainLength=${plain.length}`;
  if (matrixWrap.style.display !== 'none') renderMatrix(matrix);
});

showMatrixBtn.addEventListener('click', ()=> {
  if (matrixWrap.style.display === 'none') {
    matrixWrap.style.display = 'block';
    showMatrixBtn.textContent = 'Ẩn matrix';
    // try to render last used (prefer output if exists)
    const last = outputText.value || inputText.value;
    const k = keyInput.value;
    const pad = (padInput.value && padInput.value[0]) ? padInput.value[0] : 'X';
    if (k && k.length > 0) {
      // if output exists, try to interpret as ciphertext and show matrix for decrypt attempt
      if (outputText.value) {
        const res = decryptColumnar(outputText.value, k, pad);
        renderMatrix(res.matrix);
      } else {
        const res = encryptColumnar(inputText.value, k, pad);
        renderMatrix(res.matrix);
      }
    } else {
      matrixArea.innerHTML = '<div class="small">Nhập khóa để xem matrix.</div>';
    }
  } else {
    matrixWrap.style.display = 'none';
    showMatrixBtn.textContent = 'Hiện/Ẩn matrix';
  }
});

copyOut.addEventListener('click', async ()=> {
  try {
    await navigator.clipboard.writeText(outputText.value || '');
    metaInfo.textContent = 'Đã copy kết quả vào clipboard.';
  } catch(e) {
    metaInfo.textContent = 'Không thể copy — trình duyệt không cho phép.';
  }
});

clearAll.addEventListener('click', ()=> {
  inputText.value = '';
  outputText.value = '';
  keyInput.value = '';
  padInput.value = 'X';
  metaInfo.textContent = 'Đã clear.';
  matrixArea.innerHTML = '';
});

exampleBtn.addEventListener('click', ()=> {
  inputText.value = 'WE ARE DISCOVERED. FLEE AT ONCE!';
  keyInput.value = 'ZEBRAS';
  padInput.value = 'X';
  metaInfo.textContent = 'Ví dụ mẫu đã nạp. Nhấn "Mã hóa" để xem kết quả.';
});

// keyboard: Ctrl+Enter to run encrypt
inputText.addEventListener('keydown', (e) => {
  if ((e.ctrlKey || e.metaKey) && e.key === 'Enter') {
    encryptBtn.click();
  }
});
</script>
```
#### Hình ảnh demo
##### Mã hóa:
<img width="3071" height="1817" alt="Screenshot 2025-09-27 101947" src="https://github.com/user-attachments/assets/397c6593-c196-401e-9bda-8505b7fc04a3" />

##### Giải mã:
<img width="3071" height="1817" alt="Screenshot 2025-09-27 102032" src="https://github.com/user-attachments/assets/52788a21-13ec-43fa-a65d-a8be02ad386e" />

Hiển thị matrix:
<img width="1140" height="1350" alt="Screenshot 2025-09-27 102117" src="https://github.com/user-attachments/assets/c316179e-f6f2-47e7-8ea2-c3be7535af1f" />

#### Demo code C++:
