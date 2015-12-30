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

extern int alphasort();

extern int scandir(const char *dirname, struct dirent ***namelist, int (*select)(const struct dirent *), int (*dcomp)(const struct dirent **, const struct dirent **));

#endif //_EXTRA_H_
