#include "FileSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h> // For file permissions

using namespace std;

void dir(char * parent, char * child, DirectoryEntry directoryEntries[]);
void mkdir(char * parent, char * child, DirectoryEntry directoryEntries[]);
void rmdir(char * parent, char * child, SuperBlock superBlock, DirectoryEntry directoryEntries[]);
void dumpe2fs(SuperBlock superBlock, int free_table[], int fat_table[], DirectoryEntry directoryEntries[]);
void write(char * parent, char * child, char * filename, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[], char* password);
void read(char * parent, char * child, char * filename, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], char* password);
void del(char * parent, char * child, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[]);
void chmod(char * parent, char * child, char * permission, DirectoryEntry directoryEntries[]);
void addpw(char * parent, char * child, char * password, DirectoryEntry directoryEntries[]);

char** parsePath(char * path, int * pathCounter);
int entryType(char * parent, char * child, DirectoryEntry directoryEntries[]);
int checkParent(char * parent, char * child, DirectoryEntry directoryEntries[]);
int checkExist(char ** parsedPath, int pathLength, DirectoryEntry directoryEntries[]);

int entryChanged = 0;
int fatTableChanged = 0;
int freeTableChanged = 0;

char* fileSystemName;

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Usage: %s <fileSystemName> <operation> <parameters>\n", argv[0]);
        return 1;
    }

    fileSystemName = argv[1];

    FILE* fileSystem = fopen(fileSystemName, "rb");
    if(fileSystem == NULL){
        printf("Error opening file system\n");
        return 1;
    }

    SuperBlock superblock;
    fread(&superblock, sizeof(SuperBlock), 1, fileSystem); // Read superblock from file

    int freeTable[(superblock.totalBlocks + 7) / 8];
    fread(freeTable, sizeof(freeTable), 1, fileSystem); // Read free table from file

    int fatTable[superblock.totalBlocks];
    fread(fatTable, sizeof(int), superblock.totalBlocks, fileSystem); // Read FAT table from file

    DirectoryEntry entries[MAXFILES]; // Read directory entries from file
    for(int i = 0; i < MAXFILES; i++){
        int nameLength = 0, parentLength = 0;
        fread(&nameLength, sizeof(int), 1, fileSystem);
        fread(entries[i].name, sizeof(char), nameLength, fileSystem);
        entries[i].name[nameLength] = '\0';
        fread(&parentLength, sizeof(int), 1, fileSystem);
        fread(entries[i].parent, sizeof(char), parentLength, fileSystem);
        entries[i].parent[parentLength] = '\0';
        fread(&entries[i].size, sizeof(int), 1, fileSystem);
        fread(entries[i].permission, sizeof(char), 2, fileSystem);
        fread(&entries[i].isDirectory, sizeof(int), 1, fileSystem);
        fread(&entries[i].created, sizeof(time_t), 1, fileSystem);
        fread(&entries[i].lastModified, sizeof(time_t), 1, fileSystem);
        fread(entries[i].password, sizeof(char), 32, fileSystem);
        fread(&entries[i].exist, sizeof(int), 1, fileSystem);
        fread(&entries[i].startBlock, sizeof(int), 1, fileSystem);
    }

    fclose(fileSystem);

    char* operation = argv[2];
    char** parameters = &argv[3];

    int pathCounter = 2;

    char** parsedPath;

    if(argc > 3){
        parsedPath = parsePath(parameters[0], &pathCounter);
    }

    if(strcmp(operation, "dir") == 0){ // LIST FILES AND DIRECTORIES
        if(!checkExist(parsedPath, pathCounter - 1, entries)){
            return -1;
        }
        dir(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], entries);
    } else if(strcmp(operation, "mkdir") == 0){ // CREATE DIRECTORY
        if(pathCounter < 1){
            printf("INSUFFICENT PATH!\n");
            return -1;
        }
        if(!checkExist(parsedPath, pathCounter - 2, entries)){
            return -1;
        }
        mkdir(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], entries);
    }else if(strcmp(operation, "rmdir") == 0){ // REMOVE DIRECTORY
        if(!checkExist(parsedPath, pathCounter - 1, entries)){
            return -1;
        }
        rmdir(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], superblock, entries);
    }else if(strcmp(operation, "dumpe2fs") == 0){ // DUMP FILE SYSTEM INFORMATION
        dumpe2fs(superblock, freeTable, fatTable, entries);
    }else if(strcmp(operation, "write") == 0){ // WRITE FILE
        if(!checkExist(parsedPath, pathCounter - 3, entries)){
            return -1;
        }
        char* password = NULL;
        if(parameters[2] != NULL){
            password = parameters[2];
        }
        write(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], parameters[1], superblock, entries, fatTable, freeTable,password);
    }else if(strcmp(operation, "read") == 0){ // READ FILE
        if(!checkExist(parsedPath, pathCounter - 1, entries)){
            return -1;
        }
        char* password = NULL;
        if(parameters[2] != NULL){
            password = parameters[2];
        }
        read(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], parameters[1], superblock, entries, fatTable, password);
    }else if(strcmp(operation, "del") == 0){ // DELETE FILE
        if(!checkExist(parsedPath, pathCounter - 1, entries)){
            return -1;
        }
        del(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], superblock, entries, fatTable, freeTable);
    }else if(strcmp(operation,"chmod") == 0){ // CHANGE FILE PERMISSIONS
        if(!checkExist(parsedPath, pathCounter - 2, entries)){
            return -1;
        }
        chmod(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], parameters[1], entries);
    } else if(strcmp(operation,"addpw") == 0){ // ADD PASSWORD TO FILE
        if(!checkExist(parsedPath, pathCounter - 2, entries)){
            return -1;
        }
        addpw(parsedPath[pathCounter - 2], parsedPath[pathCounter - 1], parameters[1], entries);
    } else{
        printf("\"%s\": NOT A VALID COMMAND", operation);
    }


    FILE* fileSystemWrite = fopen(fileSystemName, "rb+"); // Open file in binary write mode
    if(fileSystemWrite == NULL){
        printf("Error opening file system\n");
        return 1;
    }

    if(entryChanged == 1){ // WRITE DIRECTORY ENTRIES TO FILE SYSTEM
        rewind(fileSystemWrite);
        long dirEntryPos = sizeof(SuperBlock) + sizeof(freeTable) + (superblock.totalBlocks * sizeof(int));
        fseek(fileSystemWrite, dirEntryPos, SEEK_SET);
        for(int i=0; i<MAXFILES; ++i){
            int nameLength = strlen(entries[i].name) + 1;
            int parentLength = strlen(entries[i].parent) + 1;
            fwrite(&nameLength, sizeof(int), 1, fileSystemWrite);
            fwrite(entries[i].name, nameLength, 1, fileSystemWrite);
            fwrite(&parentLength, sizeof(int), 1, fileSystemWrite);
            fwrite(entries[i].parent, parentLength, 1, fileSystemWrite);
            fwrite(&entries[i].size, sizeof(int), 1, fileSystemWrite);
            fwrite(entries[i].permission, sizeof(char), 2, fileSystemWrite);
            fwrite(&entries[i].isDirectory, sizeof(int), 1, fileSystemWrite);
            fwrite(&entries[i].created, sizeof(time_t), 1, fileSystemWrite);
            fwrite(&entries[i].lastModified, sizeof(time_t), 1, fileSystemWrite);
            fwrite(entries[i].password, sizeof(char), 32, fileSystemWrite);
            fwrite(&entries[i].exist, sizeof(int), 1, fileSystemWrite);
            fwrite(&entries[i].startBlock, sizeof(int), 1, fileSystemWrite);
        }
    }
    if(fatTableChanged == 1){ // WRITE FAT TABLE TO FILE SYSTEM
        rewind(fileSystemWrite);

        fseek(fileSystemWrite, sizeof(SuperBlock) + (superblock.blockSize * superblock.freeBlocks), SEEK_SET);

        fwrite(fatTable, sizeof(int), superblock.totalBlocks, fileSystemWrite);
    }
    if(freeTableChanged == 1){ // WRITE FREE TABLE TO FILE SYSTEM
        rewind(fileSystemWrite);

        fseek(fileSystemWrite, sizeof(SuperBlock), SEEK_SET);

        fwrite(freeTable, sizeof(freeTable), 1, fileSystemWrite);
    }

    fclose(fileSystemWrite);
    return 0;
}

void dir(char* parent, char* child, DirectoryEntry directoryEntries[]) {
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == 0) { // It is a file
        printf("File: %s\n", child);
    } else if (fileType == 1) { // It is a directory
        printf("Directory: %s\n", child);
        printf("--------------------------------------------------\n");
        printf("%-10s %-5s %-5s %-10s %-25s %-25s %-15s %-15s\n", "Type", "Read", "Write", "Size", "Last Modified", "Created", "Password", "Name");
        for (int i = 1; i < MAXFILES; i++) {
            if (directoryEntries[i].exist && strcmp(directoryEntries[i].parent, child) == 0) {
                char lastModified[26];
                char created[26];
                strncpy(lastModified, ctime(&directoryEntries[i].lastModified), 25);
                strncpy(created, ctime(&directoryEntries[i].created), 25);
                lastModified[24] = '\0'; // Remove newline character
                created[24] = '\0'; // Remove newline character
                
                printf("%-10c %-5c %-5c %-10d %-25s %-25s %-15s %-15s\n",
                    (directoryEntries[i].isDirectory == 1) ? 'd' : '-',
                    directoryEntries[i].permission[0], // Read permission
                    directoryEntries[i].permission[1], // Write permission
                    directoryEntries[i].size, // Size
                    lastModified,
                    created,
                    (directoryEntries[i].password[0] != '\0') ? "Yes" : "No",
                    directoryEntries[i].name);
            }
        }
        printf("--------------------------------------------------\n");
    } else {
        printf("Path not found: %s/%s\n", parent, child);
    }
}

void mkdir(char * parent, char * child, DirectoryEntry directoryEntries[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == -1){
        for(int i = 1; i < MAXFILES; i++){
            if(directoryEntries[i].exist != 1){
                strcpy(directoryEntries[i].name, child);
                directoryEntries[i].name[strlen(child)] = '\0';
                strcpy(directoryEntries[i].parent, parent);
                directoryEntries[i].parent[strlen(parent)] = '\0';
                time(&directoryEntries[i].created);
                time(&directoryEntries[i].lastModified);
                directoryEntries[i].isDirectory = 1;
                directoryEntries[i].size = 0;
                entryChanged = 1;
                directoryEntries[i].exist = 1;
                return;
            }
        }
    }else if(fileType == 0){ // THERE IS A FILE ALREADY WITH GIVEN NAME //
        printf("CANNOT CREATE DIRECTORY \"%s\": FILE WITH THE SAME NAME EXISTS!\n", child);
    }else if(fileType == 1){
        printf("CANNOT CREATE DIRECTORY \"%s\": IT EXISTS!\n", child);
    }
}

void rmdir(char * parent, char * child, SuperBlock superBlock, DirectoryEntry directoryEntries[]){
    if(strcmp(child, "/") == 0){
        printf("FAILED TO REMOVE \"/\": CANNOT REMOVE ROOT DIRECTORY!\n");
        return;
    }
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 0){ // IT IS A FILE
        printf("FAILED TO REMOVE \"%s\": NOT A DIRECTORY!\n", child);
    }else if(fileType == -1){
        printf("FAILED TO REMOVE \"%s\": NO SUCH FILE OR DIRECTORY!\n", child);
    }else{
        // Check if the directory is empty
        for(int i = 0; i < MAXFILES; i++){
            if(strcmp(directoryEntries[i].parent, child) == 0){
                printf("FAILED TO REMOVE \"%s\": DIRECTORY NOT EMPTY!\n", child);
                return;
            }
        }

        // Remove the directory
        for(int i = 0; i < MAXFILES; i++){
            if(strcmp(directoryEntries[i].name, child) == 0){
                strcpy(directoryEntries[i].name, "");
                directoryEntries[i].name[strlen(directoryEntries[i].name)] = '\0';
                strcpy(directoryEntries[i].parent, "");
                directoryEntries[i].parent[strlen(directoryEntries[i].parent)] = '\0';
                directoryEntries[i].lastModified = 0;
                directoryEntries[i].created = 0;
                directoryEntries[i].isDirectory = 0;
                directoryEntries[i].size = 0;
                entryChanged = 1;
                directoryEntries[i].exist = 0;
                break;
            }
        }
        freeTableChanged = 1;
        fatTableChanged = 1;
    }
}

void dumpe2fs(SuperBlock superBlock, int free_table[], int fat_table[], DirectoryEntry directoryEntries[]){
    printf("BLOCK SIZE: %d\nNUMBER OF BLOCKS: %d\n", superBlock.blockSize, superBlock.totalBlocks);
    int freeBlocks = 0;
    int fileNumber = 0;
    int directoryNumber = 0;
    for(int i = 0; i < superBlock.totalBlocks; i++){
        if ((free_table[i / 8] & (1 << (i % 8))) != 0) { // Check if the block is free
            freeBlocks++;
        }
    }
    printf("FREE BLOCKS NUMBER: %d\n", freeBlocks);

    for(int i = 0; i < MAXFILES; i++){
        if(directoryEntries[i].exist == 1){
            if(directoryEntries[i].isDirectory == 1){ // IT IS A DIRECTORY
                directoryNumber++;
            }else{ // IT IS A FILE
                fileNumber++;
            }
        }
    }

    printf("NUMBER OF FILES: %d\n", fileNumber);
    printf("NUMBER OF DIRECTORIES: %d\n", directoryNumber);

    for(int i = 0; i < MAXFILES; i++){ // PRINT OCCUPIED BLOCKS FOR FILES
        if(directoryEntries[i].exist == 1 && directoryEntries[i].isDirectory == 0){
            printf("OCCUPIED BLOCKS FOR %s: ", directoryEntries[i].name); 
            int start = directoryEntries[i].startBlock;
            while(start != -1){
                printf("%d ", start);
                start = fat_table[start];
            }
            printf("\n");
        }
    }
}

void write(char * parent, char * child, char * filename, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[], char* password) {
    int fileType = entryType(parent, child, directoryEntries);
    int dirIndex = -1;

    // Check if the child is a directory
    if (fileType == 1) {
        printf("\"%s\": IS A DIRECTORY!\n", child);
        return;
    }

    // Check if the file already exists in the directory and get its index
    for (int i = 0; i < MAXFILES; i++) {
        if ((directoryEntries[i].exist == 1) && strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0) {
            dirIndex = i;
            break;
        }
    }

    // Check for write permissions and password protection if the file exists
    if (dirIndex != -1) {
        char writePermission = directoryEntries[dirIndex].permission[1];
        if (writePermission != 'W') {
            printf("No write permission for \"%s\"\n", child);
            return;
        }
        if (directoryEntries[dirIndex].password[0] != '\0') {
            if (password == NULL) {
                printf("Password required for \"%s\"\n", child);
                return;
            }
            if (strcmp(password, directoryEntries[dirIndex].password) != 0) {
                printf("Incorrect password for \"%s\"\n", child);
                return;
            }
        }
        del(parent, child, superBlock, directoryEntries, fat_table, free_table); // Delete the file
    }

    // Open the file to read
    FILE * file = fopen(filename, "rb");
    if (file == NULL) {
        perror("fopen");
        exit(-1);
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    // Calculate the number of blocks needed for the file
    int file_blocks = (size + superBlock.blockSize - 1) / superBlock.blockSize;

    // Allocate memory to read the file into blocks
    char ** fileArray = (char**) malloc(file_blocks * sizeof(char*));
    for (int i = 0; i < file_blocks; i++) {
        fileArray[i] = (char*) malloc(superBlock.blockSize * sizeof(char));
        int bytesRead = fread(fileArray[i], sizeof(char), superBlock.blockSize, file);
        if (bytesRead < superBlock.blockSize) {
            memset(fileArray[i] + bytesRead, 0, superBlock.blockSize - bytesRead);
        }
    }

    // Prepare to write: find free blocks and update FAT
    int remainingSize = size;
    int firstBlock = -1, lastBlock = -1;

    for (int i = 0; i < superBlock.totalBlocks && remainingSize > 0; i++) {
        if ((free_table[i / 8] & (1 << (i % 8))) == 0) { // FREE BLOCK IS FOUND
            free_table[i / 8] |= (1 << (i % 8)); // Mark block as used
            if (firstBlock == -1) {
                firstBlock = i;
            }
            if (lastBlock != -1) {
                fat_table[lastBlock] = i;
            }
            lastBlock = i;
            remainingSize -= superBlock.blockSize;
        }
    }

    // If not enough space
    if (remainingSize > 0) {
        printf("SOME PARTS OF THE FILE IS NOT WRITTEN TO \"%s\": MEMORY IS FULL!\n", child);
        fclose(file);
        return;
    }

    // Write the file blocks to the filesystem
    FILE * fs = fopen(fileSystemName, "rb+");
    if (fs == NULL) {
        perror("fopen");
        exit(-1);
    }

    // Write the file blocks to the filesystem  
    int currentBlock = firstBlock;
    for (int i = 0; i < file_blocks; i++) {
        int position = sizeof(SuperBlock) + currentBlock * superBlock.blockSize;
        fseek(fs, position, SEEK_SET);
        fwrite(fileArray[i], sizeof(char), superBlock.blockSize, fs);
        currentBlock = fat_table[currentBlock];
    }

    // Set -1 to the last block
    if (lastBlock != -1) {
        fat_table[lastBlock] = -1;
    }

    // Get the file's permissions
    struct stat st;
    stat(filename, &st);

    // Update the directory entry for the new file
    if (dirIndex == -1) {
        for (int i = 0; i < MAXFILES; i++) {
            if (directoryEntries[i].exist != 1) {
                directoryEntries[i].name = new char[strlen(child) + 1];
                directoryEntries[i].parent = new char[strlen(parent) + 1];
                strcpy(directoryEntries[i].name, child);
                strcpy(directoryEntries[i].parent, parent);
                time(&directoryEntries[i].lastModified);
                time(&directoryEntries[i].created);
                directoryEntries[i].isDirectory = 0;
                directoryEntries[i].size = size;
                directoryEntries[i].startBlock = firstBlock;
                directoryEntries[i].exist = 1;
                directoryEntries[i].permission[0] = (st.st_mode & S_IRUSR) ? 'R' : '-'; // Read permission
                directoryEntries[i].permission[1] = (st.st_mode & S_IWUSR) ? 'W' : '-'; // Write permission
                break;
            }
        }
    }

    // Clean up and close files
    fclose(file);
    fclose(fs);
    for (int i = 0; i < file_blocks; i++) {
        free(fileArray[i]);
    }

    free(fileArray);
    
    freeTableChanged = 1;
    fatTableChanged = 1;
    entryChanged = 1;
}

void read(char * parent, char * child, char * filename, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], char* password){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }else if(fileType == -1){
        printf("\"%s\": NO SUCH FILE OR DIR!\n", child);   
    }else{
        int dirIndex = -1;

        for (int i = 0; i < MAXFILES; i++) {
            if ((directoryEntries[i].exist == 1) && strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0) {
                dirIndex = i;
                break;
            }
        }

        // Check for read permissions and password protection if the file exists
        if (dirIndex != -1) {
            char readPermission = directoryEntries[dirIndex].permission[0];
            if(readPermission != 'R'){
                printf("No read permission for \"%s\"\n", child);
                return;
            }
            if(directoryEntries[dirIndex].password[0] != '\0'){
                if(password == NULL){
                    printf("Password required for \"%s\"\n", child);
                    return;
                }
                if(strcmp(password, directoryEntries[dirIndex].password) != 0){
                    printf("Incorrect password for \"%s\"\n", child);
                    return;
                }
            }
        }

        FILE * file = fopen(filename, "wb");  // Open the file in binary write mode
        if(file == NULL){
            perror("fopen");
            return;
        }
        FILE * fs = fopen(fileSystemName, "rb+"); // Open the file system in read binary mode
        if(fs == NULL){
            perror("fopen");
            return;
        }


        for(int i = 0; i < MAXFILES; i++){
            if(strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
                int start = directoryEntries[i].startBlock;

                mode_t mode = 0; // Set the file permissions
                if(directoryEntries[i].permission[0] == 'R'){ // Read permission
                    mode |= S_IRUSR;
                }
                if(directoryEntries[i].permission[1] == 'W'){ // Write permission
                    mode |= S_IWUSR;
                }

                if(chmod(filename, mode) == -1){ // Change the file permissions
                    perror("chmod");
                    return;
                }

                int fileSize = directoryEntries[i].size;
                int remainingSize = fileSize;

                while(start != -1 && remainingSize > 0){
                    char buffer[superBlock.blockSize];
                    fseek(fs, sizeof(SuperBlock) + start * superBlock.blockSize, SEEK_SET); // Seek to the start block
                    size_t bytesToRead = (remainingSize > superBlock.blockSize) ? superBlock.blockSize : remainingSize; // Read the block
                    int bytesRead = fread(buffer, sizeof(char), bytesToRead, fs); // Write the block to the file
                    fwrite(buffer, sizeof(char), bytesRead, file); // Update the remaining size
                    remainingSize -= bytesRead; 
                    start = fat_table[start]; // Move to the next block
                }
                break;
            }
        }
        fclose(file);
        fclose(fs);
    }
}

void del(char * parent, char * child, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }else if(fileType == -1){
        printf("\"%s\": NO SUCH FILE OR DIR!\n", child);   
    }else{
        for(int i = 0; i < MAXFILES; i++){
            if(strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
                int current = directoryEntries[i].startBlock; 
                int next;
                do{
                    next = fat_table[current]; 
                    free_table[current / 8] &= ~(1 << (current % 8));
                    fat_table[current] = -1;
                    current = next; 

                }while(current != -1);
                    strcpy(directoryEntries[i].name, "");
                    strcpy(directoryEntries[i].parent, "");
                    directoryEntries[i].lastModified = 0;
                    directoryEntries[i].created = 0;
                    directoryEntries[i].isDirectory = 0;
                    directoryEntries[i].size = 0;
                    directoryEntries[i].exist = 0;
                break;
            }
        }
        freeTableChanged = 1;
        fatTableChanged = 1;
        entryChanged = 1;
    }
}

void chmod(char * parent, char * child, char * permission, DirectoryEntry directoryEntries[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }
    else if(fileType == -1){
        printf("\"%s\": NO SUCH FILE OR DIR!\n", child);
    }
    else{ // IT IS A FILE
        for(int i = 0; i < MAXFILES; i++){
            if(strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
                if(permission[0] == '+' || permission[0] == '-'){
                    if(permission[1] == 'r' || permission[2] == 'r'){
                        if(permission[0] == '+'){
                            directoryEntries[i].permission[0] = 'R';
                        }
                        else if(permission[0] == '-'){
                            directoryEntries[i].permission[0] = '-';
                        }
                    }
                    if(permission[1] == 'w' || permission[2] == 'w'){
                        if(permission[0] == '+'){
                            directoryEntries[i].permission[1] = 'W';
                        }
                        else if(permission[0] == '-'){
                            directoryEntries[i].permission[1] = '-';
                        }
                    }
                }
                directoryEntries[i].lastModified = time(0);
                entryChanged = 1;
                break;
            }
        }
    }
}

void addpw(char * parent, char * child, char * password, DirectoryEntry directoryEntries[]){
    int fileType = entryType(parent, child, directoryEntries);
    if(fileType == 1){
        printf("\"%s\": IS A DIRECTORY!\n", child);
    }
    else if(fileType == -1){
        printf("\"%s\": NO SUCH FILE OR DIR!\n", child);
    }
    else{ // IT IS A FILE
        for(int i = 0; i < MAXFILES; i++){
            if(strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
                strcpy(directoryEntries[i].password, password);
                directoryEntries[i].lastModified = time(0);
                entryChanged = 1;
                break;
            }
        }
    }
}

char** parsePath(char * path, int * pathCounter){
    char ** parsedPath = (char**) malloc(100 * sizeof(char*));

    parsedPath[0] = strdup("NOPARENT");

    parsedPath[1] = strdup("/");

    char * token = strtok(path, "/");

    for(int i = 2; i < 100 && token != NULL; i++){
        parsedPath[i] = token;
        token = strtok(NULL, "/");
        (*pathCounter)++;
    }
    return parsedPath;
}

int entryType(char * parent, char * child, DirectoryEntry directoryEntries[]){
    for(int i = 0; i < MAXFILES; i++){
        if(strcmp(directoryEntries[i].name, child) == 0 && strcmp(directoryEntries[i].parent, parent) == 0){
            return directoryEntries[i].isDirectory;
        }
    }
    return -1;
}

int checkParent(char * parent, char * child, DirectoryEntry directoryEntries[]){
    for(int i = 0; i < MAXFILES; i++){
        if(strcmp(directoryEntries[i].name, child) == 0){
            if(strcmp(directoryEntries[i].parent, parent) == 0){
                return 1;
            }
        }
    }
    return 0;
}

int checkExist(char ** parsedPath, int pathLength, DirectoryEntry directoryEntries[]){
    for(int i = 0; i < pathLength; i++){
        if(!checkParent(parsedPath[i], parsedPath[i + 1], directoryEntries)){
            printf("NO SUCH FILE OR DIR!\n");
            return 0;
        }
    }
    return 1;
}