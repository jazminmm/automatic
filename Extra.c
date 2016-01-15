#include "Extra.h"

void myId(char* output) {
  struct passwd *pw = getpwuid(getuid());
  strcpy(output, getpwuid(getuid())->pw_name);
}

bool fileExists(char* file) {
  struct stat buffer;
  return stat(file, &buffer) == 0;
}

void realName(char* output, char* id) {
  struct passwd* pwd = getpwnam(id);
  if (pwd) {
    strcpy(output, pwd->pw_gecos);
  } else {
    autoWarn("USER <%s> could not be indentified by real name", id);
    strcpy(output, "???");
  }
}
