#ifndef FILETREE_H
#define FILETREE_H

#define MAX_CHILDREN 10
#define MAX_NAME_LEN 30

typedef struct File { // tạo một kiểu dữ liệu là kiểu File
    char name[MAX_NAME_LEN];                // gồm tên file hoặc thư mục
    struct File* children[MAX_CHILDREN];   // và một hàm con trỏ để lưu địa chỉ các file con nó
    int nchildren;                         // lưu số lượng file con hiện có
} File;

typedef File* PFile; // con trỏ trỏ tới một file 
typedef File* FileTree; //con trỏ trỏ tới cả cái cây ( ở đây là cái app File Explorer luôn)

// Các hàm tạo, thêm, xóa, in cây
PFile createFile(const char* filename);
FileTree addFile(FileTree root, PFile P, PFile Q);
FileTree deleteFile(FileTree root, PFile P);
void printFileTree(FileTree root, int level);

#endif
