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

IoC ≈ 0.066 (thực tế ~0.065–0.073 tùy tập dữ liệu).

Chuỗi chữ cái ngẫu nhiên:

IoC ≈ 1/26 ≈ 0.03846

Có công thức ước lượng m (Friedman formula — dạng xấp xỉ):
<img width="1592" height="159" alt="image" src="https://github.com/user-attachments/assets/e9eb92f2-e549-4df6-895d-c15ebd7991ed" />
### B. Cài đặt
Em sẽ thực hiện cài đặt chương trình demo phương pháp mã hóa Vigenere Cipher bằng js và html với tính năng:

Mã hóa / giải mã bằng Vigenère.

Hai chế độ: Letters only (A–Z) và Full printable ASCII (32–126) (hỗ trợ số và ký tự đặc biệt).

Tuỳ chọn xử lý chữ hoa/chữ thường, nút sao chép, và hoán đổi input/output., dưới đây là một số đoạn code chính:

```html
  <script>
    // Utils
    function isLetter(ch){return /[A-Za-z]/.test(ch)}
    function mod(n,m){return ((n % m) + m) % m}

    function prepareKey(key, length, mode){
      if(!key) return null;
      if(mode === 'letters'){
        // remove non-letters from key
        const clean = key.replace(/[^A-Za-z]/g,'');
        if(clean.length === 0) return null;
        // map to 0..25
        const arr = [];
        for(let i=0;i<length;i++){
          const ch = clean[i % clean.length];
          arr.push(ch.toUpperCase().charCodeAt(0) - 65);
        }
        return arr;
      } else {
        // ascii mode: use full printable ASCII codes 32..126 => modulus 95
        const clean = key.split('');
        if(clean.length === 0) return null;
        const arr = [];
        for(let i=0;i<length;i++){
          const code = clean[i % clean.length].charCodeAt(0);
          // map into 0..94 by shifting 32..126 -> 0..94
          arr.push(mod(code - 32, 95));
        }
        return arr;
      }
    }

    function encryptVigenere(plaintext, key, mode, caseHandling){
      if(!key) return {err:'Key is empty'};
      if(mode === 'letters'){
        // Build key array only counting letters of plaintext (so that non-letters don't consume key)
        const lettersOnly = plaintext.split('').filter(c=>isLetter(c));
        const keyArr = prepareKey(key, lettersOnly.length, 'letters');
        if(!keyArr) return {err:'Key must contain letters for Letters-only mode.'};
        let keyIndex = 0;
        let out = '';
        for(let ch of plaintext){
          if(isLetter(ch)){
            const base = (ch === ch.toUpperCase()) ? 65 : 97;
            const p = ch.toUpperCase().charCodeAt(0) - 65; // use uppercase for shift
            const k = keyArr[keyIndex++];
            const c = mod(p + k, 26);
            let enc = String.fromCharCode(c + base);
            // case handling: preserve by default; if upper/lower forced, adjust
            if(caseHandling === 'upper') enc = enc.toUpperCase();
            if(caseHandling === 'lower') enc = enc.toLowerCase();
            out += enc;
          } else {
            out += ch;
          }
        }
        return {text: out};
      } else {
        // ASCII mode; every printable char is encoded; other chars unchanged
        const printable = [];
        for(let ch of plaintext){
          const code = ch.charCodeAt(0);
          printable.push((code >= 32 && code <= 126) ? true : false);
        }
        const printableCount = printable.filter(Boolean).length;
        const keyArr = prepareKey(key, printableCount, 'ascii');
        if(!keyArr) return {err:'Key is empty for ASCII mode.'};
        let keyIndex = 0;
        let out = '';
        for(let i=0;i<plaintext.length;i++){
          const ch = plaintext[i];
          const code = ch.charCodeAt(0);
          if(code >= 32 && code <= 126){
            const p = code - 32;
            const k = keyArr[keyIndex++];
            const c = mod(p + k, 95);
            out += String.fromCharCode(c + 32);
          } else {
            out += ch;
          }
        }
        // case handling for ascii mode: apply if requested
        if(caseHandling === 'upper') return {text: out.toUpperCase()};
        if(caseHandling === 'lower') return {text: out.toLowerCase()};
        return {text: out};
      }
    }

    function decryptVigenere(ciphertext, key, mode, caseHandling){
      if(!key) return {err:'Key is empty'};
      if(mode === 'letters'){
        const lettersOnly = ciphertext.split('').filter(c=>isLetter(c));
        const keyArr = prepareKey(key, lettersOnly.length, 'letters');
        if(!keyArr) return {err:'Key must contain letters for Letters-only mode.'};
        let keyIndex = 0;
        let out = '';
        for(let ch of ciphertext){
          if(isLetter(ch)){
            const base = (ch === ch.toUpperCase()) ? 65 : 97;
            const c = ch.toUpperCase().charCodeAt(0) - 65;
            const k = keyArr[keyIndex++];
            const p = mod(c - k, 26);
            let dec = String.fromCharCode(p + base);
            if(caseHandling === 'upper') dec = dec.toUpperCase();
            if(caseHandling === 'lower') dec = dec.toLowerCase();
            out += dec;
          } else {
            out += ch;
          }
        }
        return {text: out};
      } else {
        const printable = [];
        for(let ch of ciphertext){
          const code = ch.charCodeAt(0);
          printable.push((code >= 32 && code <= 126) ? true : false);
        }
        const printableCount = printable.filter(Boolean).length;
        const keyArr = prepareKey(key, printableCount, 'ascii');
        if(!keyArr) return {err:'Key is empty for ASCII mode.'};
        let keyIndex = 0;
        let out = '';
        for(let i=0;i<ciphertext.length;i++){
          const ch = ciphertext[i];
          const code = ch.charCodeAt(0);
          if(code >= 32 && code <= 126){
            const c = code - 32;
            const k = keyArr[keyIndex++];
            const p = mod(c - k, 95);
            out += String.fromCharCode(p + 32);
          } else {
            out += ch;
          }
        }
        if(caseHandling === 'upper') return {text: out.toUpperCase()};
        if(caseHandling === 'lower') return {text: out.toLowerCase()};
        return {text: out};
      }
    }

    // DOM
    const inputText = document.getElementById('inputText');
    const keyInput = document.getElementById('key');
    const output = document.getElementById('output');
    const encBtn = document.getElementById('enc');
    const decBtn = document.getElementById('dec');
    const copyBtn = document.getElementById('copy');
    const swapBtn = document.getElementById('swap');
    const modeSel = document.getElementById('mode');
    const caseSel = document.getElementById('case');

    encBtn.addEventListener('click', ()=>{
      const mode = modeSel.value;
      const caseHandling = caseSel.value;
      const res = encryptVigenere(inputText.value, keyInput.value, mode, caseHandling);
      if(res.err) output.textContent = 'Error: ' + res.err;
      else output.textContent = res.text;
    });

    decBtn.addEventListener('click', ()=>{
      const mode = modeSel.value;
      const caseHandling = caseSel.value;
      const res = decryptVigenere(inputText.value, keyInput.value, mode, caseHandling);
      if(res.err) output.textContent = 'Error: ' + res.err;
      else output.textContent = res.text;
    });

    copyBtn.addEventListener('click', async ()=>{
      try{
        await navigator.clipboard.writeText(output.textContent);
        copyBtn.textContent = 'Copied!';
        setTimeout(()=>copyBtn.textContent = 'Sao chép kết quả',1200);
      }catch(e){
        alert('Không thể sao chép. Hãy copy thủ công.');
      }
    });

    swapBtn.addEventListener('click', ()=>{
      const tmp = inputText.value;
      inputText.value = output.textContent || '';
      output.textContent = tmp || '';
    });
  </script>
```
#### Hình ảnh demo
##### Mã hóa chuỗi bao gồm cả chữ cái, số và kí tự:
<img width="3068" height="1817" alt="Screenshot 2025-09-27 092831" src="https://github.com/user-attachments/assets/26b6d8ba-b23a-4e49-93bb-7d4a64e0b373" />

##### Giải mã chuỗi vừa rồi:
<img width="3071" height="1818" alt="Screenshot 2025-09-27 092943" src="https://github.com/user-attachments/assets/446fa6df-6d70-4018-abf7-fff124595ea2" />

##### Ở chế độ Letter only (chỉ từ A-Z) cách hoạt động tương tự nhưng chỉ mã hóa các kí tự từ A -> Z:
<img width="3071" height="1819" alt="Screenshot 2025-09-27 093151" src="https://github.com/user-attachments/assets/a9abb817-8f33-4975-98f8-2dfa28277b5d" />
<img width="3070" height="1812" alt="Screenshot 2025-09-27 093226" src="https://github.com/user-attachments/assets/4e8ac8c9-8a92-4fca-8d3e-ab5c32fbaa41" />

#### Trên đây là phần demo của em về phương pháp Vigenere Cipher trong bảo mật thông tin. Như vậy bằng việc sử dụng khóa gồm nhiều ký tự, Vigenere Cipher giúp tăng tính bảo mật hơn so với các phương pháp đơn bảng.
