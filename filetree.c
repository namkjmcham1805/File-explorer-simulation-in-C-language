#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filetree.h"

PFile createFile(const char* filename) { 
    //truyền vào mảng char filename; char* nghĩa là con trỏ trỏ tới ptu đầu của mảng char đó
    
    PFile newFile = (PFile)malloc(sizeof(File));
    if (!newFile) {
        printf("Khong du bo nho de tao file!\n");
        exit(1);
    }

    strncpy(newFile->name, filename, MAX_NAME_LEN); //đặt tên file là filename
    newFile->name[MAX_NAME_LEN - 1] = '\0';

    newFile->nchildren = 0; // set số con bằng 0 

    for (int i = 0; i < MAX_CHILDREN; i++) //chưa có con nào
        newFile->children[i] = NULL;
    
    return newFile;
}

FileTree addFile(FileTree root, PFile P, PFile Q) { //thêm file  Q là con của file P
    if (root == NULL) return Q; //chưa có node nào thì add Q là root

    if (P->nchildren >= MAX_CHILDREN) {
        printf("Thu muc %s da dat gioi han %d file con.\n", P->name, MAX_CHILDREN);
        return root;
    }
    
    P->children[P->nchildren] = Q;
    P->nchildren++;
    return root;
}


FileTree deleteFile(FileTree root, PFile P) {
//xoa  1 node va xoa subtree cua node do

    //base case
    if (root == NULL || P == NULL) return root;

    //truong hop xoa ca cay
    if (root == P) {
        for (int i = 0; i < P->nchildren; i++) {
            deleteFile(root, P->children[i]);
        }
        free(P);
        return NULL;
    }

    //truong hop binh thuong
    for (int i = 0; i < root->nchildren; i++) {
        if (root->children[i] == P) {
            for (int j = 0; j < P->nchildren; j++) {
                deleteFile(root, P->children[j]);
            }
            free(P);
            //dồn lại con của cây 
            for (int k = i; k < root->nchildren - 1; k++) {
                root->children[k] = root->children[k + 1];
            }
            root->children[--root->nchildren] = NULL;
            return root;
        } else {
            root->children[i] = deleteFile(root->children[i], P);
        }
    }
    return root;
}

//in ra cấu trúc của cây
void printFileTree(FileTree root, int level) {
    if (root == NULL) return;

    if (level == 0)
        printf("Cau truc thu muc %s duoi dang cay:\n", root->name);

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s\n", root->name);

    for (int i = 0; i < root->nchildren; i++) {
        printFileTree(root->children[i], level + 1);
    }
}
