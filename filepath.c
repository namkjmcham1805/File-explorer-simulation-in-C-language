#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "filetree.h"

// Hàm tìm đường đi tới file có tên target, lưu đường đi vào mảng path, pathLen là độ dài đường đi
bool findPath(FileTree root, const char* target, char path[][MAX_NAME_LEN], int* pathLen) {
    if (root == NULL) return false;

    strncpy(path[(*pathLen)++], root->name, MAX_NAME_LEN);

    if (strcmp(root->name, target) == 0) return true;

    for (int i = 0; i < root->nchildren; i++) {
        if (findPath(root->children[i], target, path, pathLen)) {
            return true;
        }
    }

    (*pathLen)--;
    return false;
}

// Duyệt cây theo DFS in tên từng node
void DFS(FileTree root) {
    if (root == NULL) return;

    printf("%s ", root->name);
    for (int i = 0; i < root->nchildren; i++) {
        DFS(root->children[i]);
    }
}

//them vao
FileTree findNodeByName(FileTree root, const char* name) {
    if (!root) return NULL;
    printf("Dang so sanh: %s voi %s\n", root->name, name);  // Debug thêm
    if (strcmp(root->name, name) == 0) return root;
    for (int i = 0; i < root->nchildren; i++) {
        FileTree res = findNodeByName(root->children[i], name);
        if (res != NULL) return res;
    }
    return NULL;
}


void saveTreeToFileHelper(FILE* f, FileTree node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) fputc('\t', f);
    fprintf(f, "%s\n", node->name);
    for (int i = 0; i < node->nchildren; i++) {
        saveTreeToFileHelper(f, node->children[i], level + 1);
    }
}

void saveTreeToFile(const char* filename, FileTree root) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Khong the mo file de ghi: %s\n", filename);
        return;
    }
    saveTreeToFileHelper(f, root, 0);
    fclose(f);
}
