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

extern int alphasort();

// ex: scandir(".", &fileList, NULL, alphasort);
extern int scandir(const char *dirname, struct dirent ***namelist, int (*select)(const struct dirent *), int (*dcomp)(const struct dirent **, const struct dirent **));

#endif //_EXTRA_H_
