#ifndef _EXTRA_H_
#define _EXTRA_H_

//got help from: http://stackoverflow.com/questions/18402428/how-to-properly-use-scandir-in-c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdbool.h>

#define _GNU_SOURCE

#define MAX_INT 100000000001

#define max(x, y) (x > y ? x : y)

#define min(x, y) (x < y ? x : y)

#define strcmp(x, y) strncmp(x, y, min(strlen(x), strlen(y)) + 1)

#define streq(str1, str2) \
  ((strlen(str1) == strlen(str2)) && (strcmp(str1, str2) == 0))

#define DEBUG true // for debugPrint()

// printf() alternative for debug purposes
#define debugPrint(args...) {\
  if(DEBUG) {\
    printf("\x1b[33m");\
    printf("dbug: ");\
    printf(args);\
    printf("\n");\
    printf("\x1b[0m");\
  }\
}

// printf() alternative for normal use
#define autoPrint(args...) {\
  printf("auto: ");\
  printf(args);\
  printf("\n");\
}

// autoPrint() alternative used for warnings
#define autoWarn(args...) {\
  printf("\x1b[35m");\
  autoPrint(args);\
  printf("\x1b[0m");\
}

// autoPrint() alternative that kills program
#define autoError(args...) {\
  printf("\a\x1b[31m");\
  autoPrint("ERROR resulting in program crash", NULL);\
  autoPrint(args);\
  printf("\x1b[0m");\
  exit(1);\
}

#define STRLEN 509

#define sizeofarray(a) (sizeof(a) / sizeof((a)[0]))

extern int alphasort();

// ex: scandir(".", &fileList, NULL, alphasort);
extern int scandir(const char *dirname, struct dirent ***namelist, int (*select)(const struct dirent *), int (*dcomp)(const struct dirent **, const struct dirent **));

void myId(char* output);

bool fileExists(char* file);

void realName(char* output, char* id);

#endif //_EXTRA_H_
