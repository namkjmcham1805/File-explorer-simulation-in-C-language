#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filetree.h"

#define MAX_LEVEL 10

FileTree loadTreeFromFile(const char* filename) { //đọc vào các filename
    FILE* f = fopen(filename, "r"); //mở file ở chế độ đọc r

    if (!f) {
        printf("Khong the mo file %s\n", filename); //nếu không có thì in ra không thể mở
        return NULL;
    }

    FileTree parents[MAX_LEVEL] = {NULL}; //tạo mảng parents để lưu địa chỉ file
    FileTree root = NULL;

    char line[256];
    while (fgets(line, sizeof(line), f)) { // quét từng dòng trong file
        line[strcspn(line, "\r\n")] = 0;  // xóa newline \n đi, vì bữa sau so sánh tên file có thể bị lỗi 

        int level = 0;
        while (line[level] == '\t') level++; //đếm số lượng ký tự, nếu phát hiện phím tab thì tăng level

        char* name = line + level; /*tên file giờ trỏ vào địa chỉ sau khi bỏ qua các dấu tab. bởi line thực tế là con trỏ
trỏ trỏ vào kí tự bắt đầu của chuỗi, giờ nó + thêm level nghĩa là địa chỉ nó vượt qua dấu tab */
        FileTree node = createFile(name); //tạo file với cái tên như z
// tạo file xong rùi thì thêm file 

        if (level == 0) { //nếu level = 0 thì là root
            root = node;

        } else { //nếu level khác 0
            if (parents[level - 1]) { //lưu cha ở cấp độ từ 1 trở đi
                addFile(root, parents[level - 1], node); 
            } else {
                printf("Loi cau truc file o dong: %s\n", line); //nếu k có cha thì k có con
                free(node);
                continue;
            }
        }

        parents[level] = node; // khởi tạo lại node cha bây giờ là node con vừa rồi để xử lí tiếp các con tiếp theo
        for (int i = level + 1; i < MAX_LEVEL; i++) { //level của con thì bằng level của cha +1
            parents[i] = NULL;
        }
    }

    fclose(f); // đọc xong thì đóng file data nè 
    return root;
}

void menu(void);

int main() {
    FileTree root = loadTreeFromFile("data.txt");

    if (!root) {
        printf("Khong load duoc cay file\n");
        return 1;
    }

    printFileTree(root, 0);

    char ans;
    int c;
    printf("\nBan co muon mo menu thao tac (y/n)? ");
    ans = getchar();

// Xóa ký tự newline còn trong bộ đệm
   while ((c = getchar()) != '\n' && c != EOF) {} //xả ký tự thừa, tránh lần sau bị dư kí tự -> đọc sai dữ liệu

    if (ans == 'y' || ans == 'Y') 
    menu();
}
