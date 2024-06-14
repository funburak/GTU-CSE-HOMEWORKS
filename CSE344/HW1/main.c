#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "main.h"

typedef struct{
    char nameSurname[100];
    char grade[3];
} StudentEntries;

int compareByNameAsc(const void* a, const void* b) {
    const StudentEntries* entryA = (const StudentEntries*)a;
    const StudentEntries* entryB = (const StudentEntries*)b;
    return strcmp(entryA->nameSurname, entryB->nameSurname);
}

int compareByGradeDes(const void* a, const void* b) {
    const StudentEntries* entryA = (const StudentEntries*)a;
    const StudentEntries* entryB = (const StudentEntries*)b;
    return strcmp(entryA->grade,entryB->grade);
}

int compareByNameDes(const void* a, const void* b) {
    const StudentEntries* entryA = (const StudentEntries*)a;
    const StudentEntries* entryB = (const StudentEntries*)b;
    return strcmp(entryB->nameSurname, entryA->nameSurname);
}

int compareByGradeAsc(const void* a, const void* b) {
    const StudentEntries* entryA = (const StudentEntries*)a;
    const StudentEntries* entryB = (const StudentEntries*)b;
    return strcmp(entryB->grade,entryA->grade);
}


int main() {
    printf("Type exit to terminate\n");
    while(1) {
        char command[100]; 
        printf(">");
        fgets(command, sizeof(command), stdin);
        
        if(command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }
        
        char *args[4] = {0}; 
        int argCount = 0;
        char *ptr = command;
        while (*ptr != '\0' && argCount < 4) {
            while (*ptr == ' ') ptr++; // Skip leading spaces
            if (*ptr == '"') { // Start of a quoted argument
                ptr++; // Skip the opening quotation mark
                args[argCount++] = ptr; // Start of the argument
                while (*ptr && *ptr != '"') ptr++; // Move to the end of the argument
                if (*ptr) *ptr++ = '\0'; // Overwrite the closing quote with null terminator
            } else { // Unquoted argument
                args[argCount++] = ptr; // Start of the argument
                while (*ptr && *ptr != ' ') ptr++; // Move to the end of the argument
                if (*ptr) *ptr++ = '\0'; // Delimit the argument
            }
        }

        if(strcmp(args[0], "exit") == 0){
            exit(EXIT_SUCCESS);
        }

        if(strcmp(args[0], "gtuStudentGrades") == 0){
            if(argCount == 1){
                listCommands();
            }
            else if(argCount == 2){
                createFile(args[1]);
            }
        } 
        else if((strcmp(args[0], "addStudentGrade") == 0) && argCount == 4 ){
            addStudentGrade(args[3],args[1],args[2]);
        } 
        else if((strcmp(args[0], "searchStudent") == 0) && argCount == 3){
            searchStudent(args[2],args[1]);
        } 
        else if ((strcmp(args[0], "sortAll") == 0) && argCount == 2) {
            write(STDOUT_FILENO,"Sort by name or grade:",sizeof("Sort by name or grade:"));
            char type[10];
            int i = 0;
            char c;
            while (read(STDIN_FILENO, &c, 1) && c != '\n' && i < sizeof(type) - 1) {
                type[i++] = c;
            }
            type[i] = '\0'; // Null-terminate the string

            write(STDOUT_FILENO,"Ascending or descending:",sizeof("Ascending or descending:"));
            char order[100];
            i = 0;
            while (read(STDIN_FILENO, &c, 1) && c != '\n' && i < sizeof(order) - 1) {
                order[i++] = c;
            }
            order[i] = '\0'; // Null-terminate the string

            sortAll(args[1], type, order);
        }
        else if((strcmp(args[0], "showAll") == 0) && argCount == 2){
            showAll(args[1]);
        }
        else if((strcmp(args[0], "listGrades") == 0) && argCount == 2){
            listGrades(args[1]);
        }
        else if((strcmp(args[0], "listSome") == 0) && argCount == 4){
            listSome(args[3],atoi(args[1]),atoi(args[2]));
        }
        else{
            printf("Invalid command or missing arguments\n");
        }
        
    }
    return EXIT_SUCCESS;
}

void createFile(const char * filename){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        logCommands("Fork failed at creating file process");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // Child process
        fd = open(filename,O_CREAT | O_RDWR | O_APPEND,0666);
        if(fd == -1){
            perror("open");
            logCommands("File cannot be opened at creating file process");
            exit(EXIT_FAILURE);
        }
        close(fd);
        char log[256];
        sprintf(log,"%s has been created",filename);
        logCommands(log);
        exit(EXIT_SUCCESS);
    }
    else{
        waitpid(pid,NULL,0);
    }
}

void addStudentGrade(const char* filename, const char* studentNameSurname, const char* grade){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        logCommands("Fork failed at adding student grade process");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // Child process
        fd = open(filename, O_WRONLY | O_APPEND);
        if(fd == -1){
            perror("open");
            logCommands("File cannot be opened at adding student grade process");
            exit(EXIT_FAILURE);
        }
        char buffer[256];
        int byte_written = sprintf(buffer,"%s, %s\n",studentNameSurname,grade);
        if(write(fd,buffer,byte_written) == -1){
            perror("write");
            logCommands("Write failed at adding student grade process");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        char log[256];
        sprintf(log,"Student %s has been added to the file",studentNameSurname);
        logCommands(log);
        exit(EXIT_SUCCESS);
    }
    else{
        waitpid(pid,NULL,0);
    }
}

void searchStudent(const char* filename, const char* studentNameSurname) {
    int fd;
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        logCommands("Fork failed at search student process");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) { // Child process
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            logCommands("File open failed at search student process");
            exit(EXIT_FAILURE);
        }
        char buffer[256];
        char lineBuffer[512]; // Assuming a line won't be longer than 512 characters
        ssize_t bytesRead;
        int linePos = 0;
        int found = 0;

        while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0 && !found) {
            for (int i = 0; i < bytesRead; ++i) {
                if (buffer[i] == '\n' || linePos == sizeof(lineBuffer) - 1) {
                    lineBuffer[linePos] = '\0'; // Null-terminate the line
                    
                    char* commaPos = strchr(lineBuffer, ',');
                    if (commaPos) {
                        *commaPos = '\0';
                        if (strcmp(lineBuffer, studentNameSurname) == 0) {
                            printf("Student found: %s, %s\n", studentNameSurname, commaPos + 2); // Assuming a space follows the comma, hence +2
                            found = 1;
                            break; 
                        }
                        *commaPos = ','; // Restore the comma in case we need to print or log the line
                    }
                    linePos = 0;
                } else {
                    lineBuffer[linePos++] = buffer[i];
                }
            }
        }
        char log[256];
        sprintf(log, "You have searched for %s in the file %s", studentNameSurname, filename);
        logCommands(log);
        close(fd);
        if (!found) {
            printf("Student %s not found\n", studentNameSurname);
        }
        exit(EXIT_SUCCESS);
    } 
    else {
        waitpid(pid, NULL, 0);
    }
}

void sortAll(const char* filename,const char* type, const char* order){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        logCommands("Fork failed at sortAll process");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            perror("open");
            logCommands("File open failed at sortAll process");
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        ssize_t bytesRead;
        StudentEntries entries[100];
        int numOfEntries = 0;

        while((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0){
            buffer[bytesRead] = '\0'; // Null-terminate the buffer

            char* line = strtok(buffer, "\n");
            while (line != NULL && numOfEntries < 100) {
                char* commaPos = strchr(line, ',');
                if (commaPos && *(commaPos + 1) == ' ') { // Check for a space after the comma
                    *commaPos = '\0'; // Split the string at the comma
                    strncpy(entries[numOfEntries].nameSurname, line, sizeof(entries[numOfEntries].nameSurname) - 1);
                    entries[numOfEntries].nameSurname[sizeof(entries[numOfEntries].nameSurname) - 1] = '\0';
                    strncpy(entries[numOfEntries].grade, commaPos + 2, sizeof(entries[numOfEntries].grade) - 1); // Skip comma and space
                    entries[numOfEntries].grade[sizeof(entries[numOfEntries].grade) - 1] = '\0';
                    numOfEntries++;
                }
                line = strtok(NULL, "\n");
            }
        }
        if(bytesRead == -1){
            perror("read");
            logCommands("File read failed at sortAll process");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);

        int (*compareFunc)(const void*, const void*) = NULL;
        if (strcmp(type, "name") == 0 && strcmp(order, "ascending") == 0) {
            compareFunc = compareByNameAsc;
        } 
        else if (strcmp(type, "grade") == 0 && strcmp(order, "ascending") == 0) {
            compareFunc = compareByGradeAsc;
        }
        else if(strcmp(type, "name") == 0 && strcmp(order, "descending") == 0){
            compareFunc = compareByNameDes;
        }
        else if(strcmp(type, "grade") == 0 && strcmp(order, "descending") == 0){
            compareFunc = compareByGradeDes;
        }

        if (compareFunc) {
            qsort(entries, numOfEntries, sizeof(StudentEntries), compareFunc);
        }

        // Print sorted records
        for (int i = 0; i < numOfEntries; ++i) {
            printf("%s, %s\n", entries[i].nameSurname, entries[i].grade);
        }

        char log[256];
        sprintf(log,"You have printed the entries in sorted way");
        logCommands(log);
        exit(EXIT_SUCCESS);
    }
    else{
        waitpid(pid,NULL,0);
    }

}

void showAll(const char* filename){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        logCommands("Fork failed at showAll process");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // Child process
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            perror("open");
            logCommands("File open failed at showAll process");
            exit(EXIT_FAILURE);
        }
        char buffer[1024];
        ssize_t bytes_read;
        while((bytes_read = read(fd,buffer,sizeof(buffer))) > 0){
            if(write(STDOUT_FILENO,buffer,bytes_read) != bytes_read){
                perror("write");
                logCommands("File write failed at showAll process");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
        if(bytes_read == -1){
            perror("read");
            logCommands("File read failed at showAll process");
            close(fd);
            exit(EXIT_FAILURE);
        }
        char log[256];
        sprintf(log,"You printed every entry in the file");
        logCommands(log);
        close(fd);
    }
    else{
        waitpid(pid,NULL,0);
    }
}

void listGrades(const char* filename){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        logCommands("Fork failed at listGrades process");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // Child process
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            perror("open");
            logCommands("File open failed at listGrades process");
            exit(EXIT_FAILURE);
        }
        char buffer[1024];
        ssize_t bytes_read;
        int lineCount = 0;
        while((bytes_read = read(fd,buffer,sizeof(buffer) -1)) > 0 && lineCount < 5){
            buffer[bytes_read] = '\0';
            for(ssize_t i=0; i<bytes_read && lineCount < 5; ++i){
                if(write(STDOUT_FILENO,&buffer[i],1) != 1){
                    perror("write");
                    logCommands("File write failed at listGrades process");
                    close(fd);
                    exit(EXIT_FAILURE);
                }
                if(buffer[i] == '\n') lineCount++;
            }
        }
        if(bytes_read == -1){
            perror("read");
            logCommands("File read failed at listGrades process");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        char log[256];
        sprintf(log,"You printed the first 5 entries in the file");
        logCommands(log);
        exit(EXIT_SUCCESS);
    }
    else{
        waitpid(pid,NULL,0);
    }
}

void listSome(const char* filename, int numOfEntries, int pageNumber){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        logCommands("Fork failed at listSome process");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // Child process
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            perror("open");
            logCommands("File open failed at listSome process");
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        ssize_t bytesRead;
        int startLine = numOfEntries * (pageNumber - 1) + 1;
        int endLine = startLine + numOfEntries - 1;
        int currentLine = 0;
        int lineStart = 0;

        while((bytesRead = read(fd, buffer, sizeof(buffer)-1)) > 0){
            buffer[bytesRead] = '\0'; // Null-terminate the buffer to make it a valid string
            for(int i = 0; i < bytesRead; i++){
                if(buffer[i] == '\n'){ // Line end found
                    currentLine++;
                    if(currentLine >= startLine && currentLine <= endLine){
                        // Print the line segment
                        write(STDOUT_FILENO, &buffer[lineStart], i - lineStart + 1);
                    }
                    lineStart = i + 1; // Update the start of the next line
                    if(currentLine >= endLine) break; // Stop if the end of the range is reached
                }
            }
            if(currentLine >= endLine) break; // Exit the loop if the range end is reached
            if(lineStart < bytesRead && currentLine + 1 >= startLine && currentLine + 1 <= endLine){
                write(STDOUT_FILENO, &buffer[lineStart], bytesRead - lineStart);
            }
        }
        char log[256];
        sprintf(log,"You have printed the entries between %d and %d",startLine,endLine+1);
        logCommands(log);
        close(fd);
        exit(EXIT_SUCCESS); 
    }
    else{
        waitpid(pid,NULL,0);
    }
}

void logCommands(const char* logAction){
    int fd;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ // Child process
        fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND,0644);
        if(fd == -1){
            perror("open");
            exit(EXIT_FAILURE);
        }
        char buffer[256];
        int byte_written = sprintf(buffer,"%s\n",logAction);
        if(write(fd,buffer,byte_written) == -1){
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else{
        waitpid(pid,NULL,0);
    }
}

void listCommands(){
    printf("Listing all commands...\n");
    printf("gtuStudentsGrades \"filename\" ---> Creates a file\n");
    printf("addStudentGrade \"Name Surname\" \"AA\" \"filename\" ---> Appends student and grade at the end of the file\n");
    printf("searchStudent \"Name Surname\" \"filename\" ---> Prints student name, surname and grade if found in the file\n");
    printf("sortAll \"filename\" ---> Prints all entries sorted by their names\n");
    printf("showAll \"filename\" ---> Prints all of the entries in the file \n");
    printf("listGrades \"filename\" ---> Prints first 5 entries\n");
    printf("listSome \"numOfEntries\" \"pageNumber\" \"filename\" ---> Lists some of the entries\n");
    printf("gtuStudentGrades ---> Lists all of the instructions\n");

    logCommands("You printed the details of the commands");
}