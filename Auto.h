/*

  Auto.h

*/

#include "List.h"
#include "Table.h"

void autoGrade(char *dir);

void sendMail(char *dir);

void getGrades(char *dir);

void restoreGrades(char *dir); //buggy

void testGrade(char *dir);

char* realName(char *id);

bool changeDir(char *dir);

void assertChangeDir(char *dir);

void requireChangeDir(char *dir);

char* currentPath();

char* currentDir();

void autoPrompt(char* result);

bool autoAsk();

bool fileExists(char* file);

void autoShell();
