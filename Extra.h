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
#include <sys/types.h>
#include <pwd.h>
#include <stdbool.h>

#define _GNU_SOURCE

#define MAX_INT 100000000001

#define max(x, y) (x > y ? x : y)

#define min(x, y) (x < y ? x : y)

#define strcmp(x, y) strncmp(x, y, min(strlen(x), strlen(y)))

#define streq(str1, str2) (strlen(str1) == strlen(str2)) && (strcmp(str1, str2) == 0)

#define DEBUG true // for debugPrint()

// printf() alternative for debug purposes
#define debugPrint(format, args...) {\
  if(DEBUG) {\
    printf("\x1b[33m");\
    printf("dbug: ");\
    printf(format, args);\
    printf("\n");\
    printf("\x1b[0m");\
  }\
}

// printf() alternative for normal use
#define autoPrint(format, args...) {\
  printf("auto: ");\
  printf(format, args);\
  printf("\n");\
}

// autoPrint() alternative used for warnings
#define autoWarn(format, args...) {\
  printf("\x1b[35m");\
  autoPrint(format, args);\
  printf("\x1b[0m");\
}

// autoPrint() alternative that kills program
#define autoError(format, args...) {\
  printf("\a\x1b[31m");\
  autoPrint("ERROR resulting in program crash", NULL);\
  autoPrint(format, args);\
  exit(1);\
}

// autoError() alternative that includes stack trace
#define autoErrorStack(format, args...) {\
  printf("\a\x1b[31m");\
  autoPrint("ERROR resulting in program crash", NULL);\
  autoPrint(format, args);\
  debugPrint("STACK TRACE", NULL);\
  debugPrint("GRADER <%s>", graderId);\
  debugPrint("CLASS <%s>", classId);\
  debugPrint("ASG <%s>", asgId);\
  debugPrint("PATH <%s>", currentPath());\
  exit(1);\
}

#define STRLEN 509 

extern int alphasort();

// ex: scandir(".", &fileList, NULL, alphasort);
extern int scandir(const char *dirname, struct dirent ***namelist, int (*select)(const struct dirent *), int (*dcomp)(const struct dirent **, const struct dirent **));

#endif //_EXTRA_H_
