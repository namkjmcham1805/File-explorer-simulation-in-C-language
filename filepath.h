#ifndef FILEPATH_H
#define FILEPATH_H

#include "filetree.h"

FileTree loadTreeFromFile(const char* filename);
void saveTreeToFile(const char* filename, FileTree root);
FileTree findNodeByName(FileTree root, const char* name);
bool findPath(FileTree root, const char* target, char path[][MAX_NAME_LEN], int* pathLen);

#endif
