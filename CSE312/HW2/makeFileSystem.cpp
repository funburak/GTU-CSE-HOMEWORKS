#include "FileSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

void createFileSystem(const char* fileName, int blockSize) {
    int numberOfBlocks;
    if(blockSize == 512){
        numberOfBlocks = (MAXSIZE / 2) / blockSize;
    }
    else{
        numberOfBlocks = MAXSIZE / blockSize;
    }
    int fatBlocks = ((numberOfBlocks * sizeof(int)) + blockSize - 1) / blockSize;
    int directoryBlocks = ((MAXFILES * sizeof(DirectoryEntry)) + blockSize - 1) / blockSize;
    int freeTableBlocks = ((numberOfBlocks + 7) / 8 + blockSize - 1) / blockSize;  // 1 bit per block

    SuperBlock superblock(blockSize, numberOfBlocks, freeTableBlocks, fatBlocks, directoryBlocks);

    FILE* fileSystem = fopen(fileName, "wb"); // Open file in binary write mode
    if (fileSystem == NULL) {
        printf("Error creating file system\n");
        return;
    }

    fwrite(&superblock, sizeof(SuperBlock), 1, fileSystem); // Write superblock to file

    // Free table
    int freeTable[(numberOfBlocks + 7) / 8];
    memset(freeTable, 0, sizeof(freeTable));
    for(int i = 0; i < fatBlocks + directoryBlocks; i++){
        freeTable[i / 8] |= 1 << (i % 8);
    }
    fwrite(freeTable, sizeof(freeTable), 1, fileSystem); // Write free table to file

    // FAT table
    int fatTable[numberOfBlocks];
    memset(fatTable, -1, sizeof(fatTable));
    fwrite(fatTable, sizeof(int), numberOfBlocks, fileSystem); // Write FAT table to file

    char* rootName = (char*)malloc(strlen("/") + 1);
    strcpy(rootName, "/");

    char* rootParent = (char*)malloc(strlen("NOPARENT") + 1);
    strcpy(rootParent, "NOPARENT");

    // Root directory
    DirectoryEntry root(rootName, rootParent, 0, 0, 1);
    int nameLength = strlen(rootName) + 1;
    int parentLength = strlen(rootParent) + 1;
    fwrite(&nameLength, sizeof(int), 1, fileSystem);
    fwrite(rootName, nameLength, 1, fileSystem);
    fwrite(&parentLength, sizeof(int), 1, fileSystem);
    fwrite(rootParent, parentLength, 1, fileSystem);
    fwrite(&root.size, sizeof(int), 1, fileSystem);
    fwrite(root.permission, sizeof(char), 2, fileSystem);
    fwrite(&root.isDirectory, sizeof(int), 1, fileSystem);
    fwrite(&root.created, sizeof(time_t), 1, fileSystem);
    fwrite(&root.lastModified, sizeof(time_t), 1, fileSystem);
    fwrite(root.password, sizeof(char), 32, fileSystem);
    fwrite(&root.exist, sizeof(int), 1, fileSystem);
    fwrite(&root.startBlock, sizeof(int), 1, fileSystem);


    DirectoryEntry empty[MAXFILES];
    // Write empty directory entries
    for (int i = 1; i < MAXFILES; i++) {
        int nameLength = strlen(empty[i].name) + 1;
        int parentLength = strlen(empty[i].parent) + 1;
        fwrite(&nameLength, sizeof(int), 1, fileSystem);
        fwrite(empty[i].name, nameLength, 1, fileSystem);
        fwrite(&parentLength, sizeof(int), 1, fileSystem);
        fwrite(empty[i].parent, parentLength, 1, fileSystem);
        fwrite(&empty[i].size, sizeof(int), 1, fileSystem);
        fwrite(empty[i].permission, sizeof(char), 2, fileSystem);
        fwrite(&empty[i].isDirectory, sizeof(int), 1, fileSystem);
        fwrite(&empty[i].created, sizeof(time_t), 1, fileSystem);
        fwrite(&empty[i].lastModified, sizeof(time_t), 1, fileSystem);
        fwrite(empty[i].password, sizeof(char), 32, fileSystem);
        fwrite(&empty[i].exist, sizeof(int), 1, fileSystem);
        fwrite(&empty[i].startBlock, sizeof(int), 1, fileSystem);
    }

    // Calculate the total number of blocks written so far
    int blocksWritten = 1 + freeTableBlocks + fatBlocks + directoryBlocks;

    // Data blocks
    char emptyBlock[blockSize];
    memset(emptyBlock, 0, blockSize);
    for (int i = blocksWritten; i < numberOfBlocks; i++) {
        fwrite(emptyBlock, blockSize, 1, fileSystem);
    }

    fclose(fileSystem);

    printf("File system created successfully\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <blockSize> <fileSystemName>\n", argv[0]);
        return 1;
    }

    float blockSizeKB = atof(argv[1]);
    if (blockSizeKB != 0.5 && blockSizeKB != 1) {
        printf("Invalid block size. Must be 0.5 or 1\n");
        return 1;
    }

    int blockSize = (int)(blockSizeKB * 1024);
    createFileSystem(argv[2], blockSize);

    return 0;
}