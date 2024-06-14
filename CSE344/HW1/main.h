#ifndef _MAIN_H_
#define _MAIN_H_

void createFile(const char* filename);
void addStudentGrade(const char* filename, const char* studentNameSurname, const char* grade);
void searchStudent(const char* filename, const char* studentNameSurname);
void sortAll(const char* filename,const char* type, const char* order);
void showAll(const char* filename);
void listGrades(const char* filename);
void listSome(const char* filename, int numOfEntries, int pageNumber);
void logCommands(const char* logAction);
void listCommands();

#endif