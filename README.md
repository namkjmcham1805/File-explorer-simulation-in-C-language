# Thành viên nhóm

Đoàn Thị Thanh Thủy - 20233940

Đỗ Đức Thiện - 20233938

Nguyễn Danh Thiện Thành - 20233937

# Hệ mô phỏng quản lý tệp tin ( File Explorer )

## Mục đích

Chương trình mô phỏng cấu trúc thư mục theo dạng cây trong ngôn ngữ C.

Bạn có thể: 

- Đọc cây thư mục từ file văn bản `data.txt`có cấu trúc thụt lề bằng tab.
- Hiển thị cấu trúc cây thư mục dạng cây rõ ràng
- Thêm thư mục/file mới vào cây
- Xóa thư mục/file khỏi cây
- Truy vết đường đi đến thư mục/file trong cây
- In cấu trúc của một thư mục bất kì
- Tương tác dễ dàng qua menu

## Cấu Trúc Thư Mục và Tệp Tin Chính

- `main.c`: Chương trình chính, load cây thư mục từ file `data.txt` và gọi menu thao tác.
- `filetree.h`, `filetree.c`: Định nghĩa struct cây thư mục và các hàm thao tác như tạo, thêm, xóa, in cây.
- `filepath.h`, `filepath.c`: Các hàm tìm kiếm, truy vết đường dẫn, lưu cây thư mục vào file.
- `menu.c`: Menu tương tác người dùng, xử lý các lựa chọn thêm/xóa/truy vết/in cây.

## Các hàm sử dụng trong tập tin

### 1. `filetree.c` và `filetree.h` — Quản lý cây thư mục và file

### `PFile createFile(const char* filename)`

- Tạo một node mới đại diện cho file hoặc thư mục có tên `filename`.
- Cấp phát bộ nhớ cho node, khởi tạo số con bằng 0, đặt tên node.
- Trả về con trỏ đến node mới tạo.

---

### `FileTree addFile(FileTree root, PFile parent, PFile child)`

- Thêm node `child` vào làm con của node `parent`.
- Kiểm tra nếu `parent` đã có số con tối đa (`MAX_CHILDREN`) thì báo lỗi.
- Cập nhật mảng con và số lượng con của `parent`.
- Trả về `root` (cây gốc, có thể dùng để chaining).

---

### `FileTree deleteFile(FileTree root, PFile nodeToDelete)`

- Xóa node `nodeToDelete` khỏi cây bắt đầu từ `root`.
- Xóa đệ quy toàn bộ cây con của node đó (dọn sạch bộ nhớ).
- Nếu node cần xóa là root thì trả về NULL.
- Nếu node cần xóa là con của node khác thì xóa khỏi mảng con, dồn lại mảng cho liền mạch.
- Trả về cây sau khi xóa.

---

### `void printFileTree(FileTree root, int level)`

- In cấu trúc cây thư mục bắt đầu từ `root`.
- In thụt lề theo `level` (cấp độ node trong cây).
- In tên node, rồi đệ quy in các con.
- Mục đích để hiển thị cấu trúc cây rõ ràng trên console.

---

### 2. `filepath.c` và `filepath.h` — Các hàm tìm kiếm, truy vết, lưu cây

### `FileTree loadTreeFromFile(const char* filename)`

- Đọc file dữ liệu (ví dụ `data.txt`) chứa cấu trúc cây theo định dạng thụt lề bằng tab.
- Mỗi dòng tương ứng 1 file hoặc thư mục.
- Dựa vào số tab để xác định cấp độ (level) của node.
- Tạo node mới và thêm vào cây đúng vị trí dựa trên level.
- Trả về cây root vừa load.

---

### `void saveTreeToFile(const char* filename, FileTree root)`

- Ghi cấu trúc cây `root` ra file văn bản.
- Sử dụng định dạng thụt lề bằng tab tương tự file input.
- Đệ quy ghi từng node và các con theo đúng cấp độ.

---

### `FileTree findNodeByName(FileTree root, const char* name)`

- Duyệt cây từ `root` tìm node có tên trùng với `name`.
- Dùng thuật toán DFS (đệ quy) để tìm.
- Trả về con trỏ node tìm được hoặc NULL nếu không tìm thấy.

---

### `bool findPath(FileTree root, const char* target, char path[][MAX_NAME_LEN], int* pathLen)`

- Tìm đường dẫn từ `root` tới node tên `target`.
- Lưu đường dẫn từng node vào mảng `path`.
- `pathLen` lưu số node trong đường đi.
- Dùng đệ quy để đi tìm, nếu tìm thấy trả về `true` cùng đường đi.
- Nếu không tìm thấy trả về `false`.

---

### 3. `menu.c` — Giao diện tương tác với người dùng

### `void addFileInteractive(FileTree root)`

- Hỏi người dùng nhập tên file/thư mục mới và tên thư mục cha.
- Tìm thư mục cha trong cây.
- Tạo node mới và thêm vào cây.
- Thông báo thêm thành công.

---

### `FileTree deleteFileInteractive(FileTree root)`

- Hỏi người dùng nhập tên file/thư mục cần xóa.
- Tìm node cần xóa.
- Gọi hàm xóa node trong cây.
- Trả về cây sau khi xóa.

---

### `void traceFileInteractive(FileTree root)`

- Hỏi người dùng nhập tên file/thư mục cần truy vết.
- Tìm đường dẫn đến node đó.
- In ra đường dẫn theo thứ tự từ root đến node.

---

### `void menu()`

- Vòng lặp hiển thị menu chức năng: thêm, xóa, truy vết, in cây, thoát.
- Đọc lựa chọn người dùng.
- Gọi các hàm tương ứng.
- Cập nhật và lưu cây vào file `data.txt`.
- In cây sau mỗi thay đổi để dễ quan sát.

---

### 4. `main.c`

### `int main()`

- Gọi `loadTreeFromFile` để đọc cây từ file dữ liệu.
- In cây vừa load ra màn hình.
- Hỏi người dùng có muốn mở menu thao tác không.
- Nếu đồng ý, gọi hàm `menu()` để chạy giao diện tương tác.

## Hướng Dẫn Sử Dụng

1. **Biên dịch chương trình**:
    
    Dùng lệnh sau trong terminal/CMD:
    
    ```
    gcc main.c filetree.c filepath.c menu.c -o main.exe -Wall -Wextra
    ```
    
2. **Chạy chương trình**:
    
    Chạy file thực thi `main.exe`: 
    ```
    .\main.exe
    ```

## Kết luận
- Đã thực hiện được các chức năng cơ bản: thêm, xóa, truy vết
- Tuy nhiên vẫn còn hạn chế: Chưa phân biệt rõ ràng file và folder.
