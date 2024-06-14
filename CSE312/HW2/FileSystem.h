#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 4 * 1024 * 1024 // 4MB
#define MAXFILES 256

struct DirectoryEntry{
    char* name;
    char* parent;
    int size;
    char permission[2]; // r, w
    time_t lastModified;
    time_t created;
    char password[32];
    int isDirectory;
    int exist;
    int startBlock;

    DirectoryEntry(){
        name = (char*)malloc(strlen("") + 1);
        parent = (char*)malloc(strlen("") + 1);
        strcpy(name, "");
        strcpy(parent, "");
        size = 0;
        permission[0] = 'R';
        permission[1] = 'W';
        lastModified = time(0);
        created = time(0);
        password[0] = '\0';
        isDirectory = 0;
        exist = 0;
        startBlock = -1;
    }

    DirectoryEntry(char* name, char* parent, int size, int startBlock, int isDirectory){
        this->name = (char*)malloc(strlen(name) + 1);
        this->parent = (char*)malloc(strlen(parent) + 1);
        strcpy(this->name, name);
        strcpy(this->parent, parent);
        this->size = size;
        permission[0] = 'R';
        permission[1] = 'W';
        lastModified = time(0);
        created = time(0);
        password[0] = '\0';
        this->isDirectory = isDirectory;
        exist = 1;
        this->startBlock = startBlock;
    }
};

struct SuperBlock{
    int blockSize;        // Block size in bytes (0.5 KB or 1 KB)
    int totalBlocks;      // Total number of blocks in the file system
    int freeBlocks;       // Number of free blocks
    int fatBlocks;        // Number of blocks used by the FAT
    int directoryBlocks;  // Number of blocks used by the directory

    SuperBlock(){
        blockSize = 0;
        totalBlocks = 0;
        freeBlocks = 0;
        fatBlocks = 0;
        directoryBlocks = 0;
    }

    SuperBlock(int blockSize, int totalBlocks, int freeBlocks, int fatBlocks, int directoryBlocks){
        this->blockSize = blockSize;
        this->totalBlocks = totalBlocks;
        this->freeBlocks = freeBlocks;
        this->fatBlocks = fatBlocks;
        this->directoryBlocks = directoryBlocks;
    }
};

#endif