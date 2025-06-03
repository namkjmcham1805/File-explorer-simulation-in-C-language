#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "filetree.h"
#include "filepath.h"

// Hàm thêm file giao diện nhập liệu
void addFileInteractive(FileTree root) {
    char newName[MAX_NAME_LEN];
    char parentName[MAX_NAME_LEN];

    printf("Nhap ten file/thu muc moi: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;

    printf("Nhap ten thu muc cha de them vao: ");
    fgets(parentName, sizeof(parentName), stdin);
    parentName[strcspn(parentName, "\n")] = 0;

    FileTree parent = findNodeByName(root, parentName);
    if (!parent) {
        printf("Khong tim thay thu muc cha '%s'\n", parentName);
        return;
    }

    PFile newFile = createFile(newName);
    addFile(root, parent, newFile);
    printf("Da them file '%s' vao thu muc '%s'\n", newName, parentName);
}

// Hàm xóa file giao diện nhập liệu
FileTree deleteFileInteractive(FileTree root) {
    char delName[MAX_NAME_LEN];
    printf("Nhap ten file muon xoa: ");
    fgets(delName, sizeof(delName), stdin);
    delName[strcspn(delName, "\n")] = 0;

    FileTree toDelete = findNodeByName(root, delName);
    if (!toDelete) {
        printf("Khong tim thay file %s\n", delName);
        return root;
    }

    root = deleteFile(root, toDelete);
    printf("Da xoa file %s\n", delName);
    return root;
}

// Hàm truy vết file
void traceFileInteractive(FileTree root) {
    char target[MAX_NAME_LEN];
    printf("Nhap ten file can truy vet: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;

    char path[100][MAX_NAME_LEN];
    int pathLen = 0;
    if (findPath(root, target, path, &pathLen)) {
        printf("Duong di den file %s:\n", target);
        for (int i = 0; i < pathLen; i++) {
            printf("%s\n", path[i]);
        }
    } else {
        printf("Khong tim thay file %s\n", target);
    }
}

void menu() {
    FileTree root = loadTreeFromFile("data.txt");
    if (!root) {
        printf("Khong load duoc cay file\n");
        return;
    }

    char choice[10];

    while (1) {
        printf("\n------ MENU ------\n");
        printf("1. Them file\n");
        printf("2. Xoa file\n");
        printf("3. Truy vet file\n");
        printf("4. In cau truc thu muc\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");

        if (!fgets(choice, sizeof(choice), stdin)) break;

        switch (atoi(choice)) {
            case 1:
                addFileInteractive(root);
                saveTreeToFile("data.txt", root);
                printFileTree(root, 0);
                break;
            case 2:
                root = deleteFileInteractive(root);
                saveTreeToFile("data.txt", root);
                printFileTree(root, 0);
                break;
            case 3:
                traceFileInteractive(root);
                break;
            case 4:
    {
        char folderName[MAX_NAME_LEN];
        printf("Nhap ten thu muc ");
        fgets(folderName, sizeof(folderName), stdin);
        folderName[strcspn(folderName, "\n")] = 0;

        FileTree node = findNodeByName(root, folderName);
        if (!node) {
            printf("Khong tim thay thu muc %s\n", folderName);
        } else {
            printFileTree(node, 0);
        }
    }
    break;

            case 0:
                printf("Thoat chuong trinh.\n");
                return;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                break;
        }
    }
}
