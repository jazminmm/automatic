/*

  Auto.c

*/

#include "Auto.h"

void autoGrade(char *dir) {
  //printf("This method is not yet ready\n");
  //return;
  if (1 || strncmp(dir, "pa2", 4)) {
    printf("Auto grade function is not yet available for this directory\n");
    return;
  }
  char execfile[10];
  //sprintf(dir, "pa4");
  //printf("%s\n", dir);
  sprintf(execfile, "m%s", dir);
  //printf("%s\n", dir);
  char path[500];
  FILE *fp;
  FILE *fp2;
  FILE *fp3;
  FILE *fp4 = NULL;
  struct dirent **fileList;
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s", dir);
  //printf("%s\n", path);
  int filecount;
  chdir("..");
  if (chdir(dir) != 0) {
    printf("Trouble switching to %s\n", dir);
    return;
  }
  filecount = scandir(".", &fileList, NULL, alphasort);
  char temp[501] = "";
  char temp1[501] = "";
  int diff = 0;
  for (int i = 2; i < filecount; i++) { //start at i = 2 because we are ignoring the "." and ".." directories
    //printf("test\n");
    diff = 0;
    if (chdir(fileList[i]->d_name) != 0) {
      printf("Error changing directories\n");
      return;
    }
    sprintf(temp, "cp /afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/%s /afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s", dir, execfile, dir, fileList[i]->d_name);
    system(temp);
    fp = fopen("tests.txt", "w");
    fp4 = fopen("design.temp", "w");
    system("make");
    fp3 = fopen("Search", "r");
    fprintf(fp, "Makefile Test %s\n", fp3 ? "Passed" : "Failed");
    if (fp3) {
      fclose(fp3);
    } else {
      fprintf(fp4, "-5 points - Makefile doesn't make.");
      sprintf(temp, "cp /afs/cats.ucsc.edu/users/d/icherdak/cs12b_pt.s15/%s/mfile .", dir);
      system(temp);
      system("mfile");
      system("rm mfile");
    }
    sprintf(temp, "timeout 25 %s", execfile);
    system(temp);
    fp2 = fopen("diff1", "r");
    fprintf(fp, "User Input Tests %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2) fclose(fp2);
    int scount = 0; // this is how we know that both untit tests passed special tests
    fp2 = fopen("diff21", "r");
    fp3 = fopen("diff22", "r");
    fprintf(fp, "Unit Tests 1 %s\n", (fp2 && fgetc(fp2) == EOF || fp3 && fgetc(fp3) == EOF) ? (fp2 && fgetc(fp2) == EOF ? "Normal Tests Passed" : "Special Tests Passed") : "Failed Tests");
    if (fp3 && feof(fp3)) scount = 1;
    if (fp2) fclose(fp2);
    if (fp3) fclose(fp3);
    fp2 = fopen("diff31", "r");
    fp3 = fopen("diff32", "r");
    fprintf(fp, "Unit Tests 2 %s\n", (fp2 && fgetc(fp2) == EOF || fp3 && fgetc(fp3) == EOF) ? (fp2 && fgetc(fp2) == EOF ? "Normal Tests Passed" : "Special Tests Passed") : "Failed Tests");
    if (fp3 && feof(fp3)) scount = 1;
    if (fp2) fclose(fp2);
    if (fp3) fclose(fp3);
    fp2 = fopen("diff41", "r");
    fp3 = fopen("diff42", "r");
    fprintf(fp, "Multi Target %s\n", (fp2 && fgetc(fp2) == EOF || fp3 && fgetc(fp3) == EOF) ? (fp2 && fgetc(fp2) == EOF ? "Normal Tests Passed" : "Special Tests Passed") : "Tests Failed");
    if (fp3 && feof(fp3)) scount = 1;
    if (scount) {
    //  if (!fp4) fp4 = fopen("design.temp", "w");
      fprintf(fp4, "-10 points - Program doesn't support line numbers\n\n");
    }
    if (!(fp2 && feof(fp2) || fp3 && feof(fp3))) {
    //  if (!fp4) fp4 = fopen("design.temp", "w");
      //fprintf(fp4, "-5 points - Program doesn't support variable arguments\n\n");
    }
    if (fp2) fclose(fp2);
    if (fp3) fclose(fp3);
    if (fp) fclose(fp);
    fp = fopen("README", "r");
    fp2 = fopen("Makefile", "r");
    fp3 = fopen("Search.java", "r");
    if (!fp || !fp2 || !fp3) {
    //  if (!fp4) fp4 = fopen("design.temp", "w");
    if (!fp) fprintf(fp4, "-3 points - Missing/incorrectly named file: README\n\n");
    if (!fp2) fprintf(fp4, "-3 points - Missing/incorrectly named file: Makefile\n\n");
    if (!fp3) fprintf(fp4, "-3 points - Missing/incorrectly named file: Search.java\n\n");
    }
    if (fp) fclose(fp);
    if (fp2) fclose(fp2);
    if (fp3) fclose(fp3);
    if (fp4) fclose(fp4);
    /*fp2 = fopen("diff3", "r");
    fprintf(fp, "Advanced Unit Tests %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2 && fgetc(fp2) == EOF) diff++;
    if (fp2) fclose(fp2);
    fp2 = fopen("diff4", "r");
    fprintf(fp, "Credibility Test %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2 && fgetc(fp2) == EOF) diff++; 
    if (fp2) fclose(fp2);*/

    /*
    fp2 = fopen("diff5", "r");
    fprintf(fp, "Test 5 %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2 && fgetc(fp2) == EOF) diff++;
    if (fp2) fclose(fp2);
    fp2 = fopen("diff6", "r");
    fprintf(fp, "\"make\" Test %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2 && fgetc(fp2) == EOF) diff++;
    if (fp2) fclose(fp2);
    fp2 = fopen("diff7", "r");
    fprintf(fp, "\"make submit\" Test %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2 && fgetc(fp2) == EOF) diff++;
    if (fp2) fclose(fp2);
    fp2 = fopen("diff8", "r");
    fprintf(fp, "\"make clean\" Test %s\n", (!fp2 || fp2 && fgetc(fp2) != EOF) ? "Failed" : "Passed");
    if (fp2 && fgetc(fp2) == EOF) diff++; 
    if (fp2) fclose(fp2);
    */

    /*if (0 && diff == 8) {
      fp = fopen("grade.txt", "r");
      if (!fp) {
        fp = fopen("grade.txt", "w");
        fprintf(fp, "\n\nAll Test Passed");
      }
      fclose(fp);
    }*/
    sprintf(temp, "rm %s", execfile);
    system(temp);
    system("rm -f *.class Search");
    printf("Finished grading %s for %s\n", fileList[i]->d_name, dir);
    chdir("..");
  }
  for (int i = 0; i < filecount; i++)
    free(fileList[i]);
  free(fileList);
  printf("Grading routine finished\n");
}

void sendMail(char *dir) {
  //	printf("Mail method not yet available\n");
  //	return;
  char path[500];
  //	sprintf(path, "/afs/cats.ucsc.edu/class/cmps011-pt.w15/bin/%s/mail_all", dir);
  //	FILE *fp = fopen(path, "w");
  FILE *fp;
  struct dirent **fileList;
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s", dir);
  int filecount;
  chdir("..");
  if (chdir(dir) != 0) {
    printf("Trouble switching to the specified directory\n");
    return;
  }
  filecount = scandir(".", &fileList, NULL, alphasort);
  FILE *fp2 = fopen("/afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/mailscript", "w");
  fprintf(fp2, "#!/bin/csh\ncd /afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s\n", dir);
  int mailcount = 0;
  //	char temp[501];
  //	char commands[filecount - 2][501];
  for (int i = 2; i < filecount; i++) { //start at i = 2 because we are ignoring the "." and ".." directories
    chdir(fileList[i]->d_name);
    fp = fopen("grade.txt", "r");
    if (!fp) printf("grade.txt does not exist for %s\n", fileList[i]->d_name);
    else {
      fprintf (fp2, "cd %s\necho \"Mailing %s@ucsc.edu\"\nmailx -s \"grade for %s\" %s@ucsc.edu < grade.txt\ncd ..\nsleep 3\n", fileList[i]->d_name, fileList[i]->d_name, dir, fileList[i]->d_name);
      //			strncpy(commands[i - 2], temp, 500);
      //			printf("%s\n", commands[i - 2]);
      fclose(fp);
      mailcount++;
    }
    chdir("..");
  }
  //	fclose(fp);
  for (int i = 0; i < filecount; i++)
    free(fileList[i]);
  free(fileList);
  fclose(fp2);
  chdir("/afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin");
  while(1) {
    printf("Approximate runtime: %d minute%s %d second%s, Would you like to email all students that have been graded? [y/n]\n", (mailcount * 3) / 60, ((mailcount * 3) / 60) == 1 ? "" : "s", (mailcount * 3) % 60, ((mailcount * 3) % 60) == 1 ? "" : "s");
    char ask = getchar();
    if (ask == 'y') {
      system("chmod 700 mailscript");
      system("mailscript");
      system("rm mailscript");
      printf("Mail Routine Complete\n");
      return;
    } else if (ask =='n') {
      system("rm mailscript");
      printf("Exiting Program\n");
      return;
    } else {
      printf("Invalid Command!\nPlease Enter An Appropriate Character [y/n]\n");
    }
  }
}

void getGrades(char *dir) {
  if (strncmp(dir, "pa2", 4)) {
    printf("This method is currently unavailable\n");
    return;
  }
  char path[500];
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/gradelist.txt", dir);
  FILE *fp = fopen(path, "w");
  FILE *fp2;
  FILE *fp10;
  FILE *fp20;
  FILE *fp30;
  struct dirent **fileList;
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s", dir);
  int filecount;
  if (chdir(path) != 0) {
    printf("Trouble switching to the specified directory\n");
    return;
  }
  filecount = scandir(".", &fileList, NULL, alphasort);
  char temp[501];
  char temp1[501];
  int grade1, grade2, grade3, grade4;
  for (int i = 2; i < filecount; i++) { //start at i = 2 because we are ignoring the "." and ".." directories
    chdir(fileList[i]->d_name);
    fp2 = fopen("grade.txt", "r");
    //system("rm -f grade.txt");
    if (1 || !fp2) {
      if (fp2) fclose(fp2);
      fp10 = fopen("performance.txt", "r");
      fp20 = fopen("design.txt", "r");
      fp30 = fopen("bugs.txt", "r");
      if (fp10) {
        sprintf(temp1, "cp performance.txt /afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/performance/%s_performance.txt", dir, fileList[i]->d_name);
        system(temp1);
      }
      if (fp20) {
        sprintf(temp1, "cp design.txt /afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/design/%s_design.txt", dir, fileList[i]->d_name);
        system(temp1);
      }
      if (fp30) {
        sprintf(temp1, "cp bugs.txt /afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/bugs/%s_bugs.txt", dir, fileList[i]->d_name);
        system(temp1);
        fclose(fp30);
      }
      if (fp10 && fp20) {
        fp2 = fopen("grade.txt", "w");
        fscanf(fp10, "%d", &grade3);
        fscanf(fp20, "%d", &grade4);
        grade1 = grade3;
        grade2 = grade4;
        while(fgets(temp1, 500, fp10)) {
          if (temp1[0] == '-') {
            int index = 1;
            while (isdigit(temp1[index])) {
              temp[index - 1] = temp1[index];
              index++;
            }
            temp[index - 1] = '\0';
            index = strlen(temp) - 1;
            while (index >= 0) {
              //printf("Subtracting %d from %d in %s as a result of array: {%s}\n", pow(10, ((int) strlen(temp) - index - 1)) * ((int) temp[index] - 48), grade1, fileList[i]->d_name, temp);
              grade1 -= pow (10, strlen(temp) - index - 1) * ((int) temp[index] - 48);
              index--;
            }
          }
        }
        while(fgets(temp1, 500, fp20)) {
          if (temp1[0] == '-') {
            int index = 1;
            while (isdigit(temp1[index])) {
              temp[index - 1] = temp1[index];
              index++;
            }
            temp[index - 1] = '\0';
            index = strlen(temp) - 1;
            while (index >= 0) {
              //printf("Subtracting %d from %d in %s as a result of array: {%s}\n", pow(10, ((int) strlen(temp) - index - 1)) * ((int) temp[index] - 48), grade2, fileList[i]->d_name, temp);
              grade2 -= pow(10, strlen(temp) - index - 1) * ((int) temp[index] - 48);
              index--;
            }
          }
        }
        fclose(fp10);
        fp10 = fopen("performance.txt", "r");
        fgets(temp1, 500, fp10);
        fclose(fp20);
        fp20 = fopen("design.txt", "r");
        fgets(temp1, 500, fp20);
        //fscanf(fp10, "%d", &grade3);
        //fscanf(fp20, "%d", &grade4);
        fprintf(fp2, "%d/%d points\n", grade1 + grade2, grade3 + grade4);
        //printf("test1");
        fprintf(fp2, "====================\nPerformance\n====================\n\n%d/%d points\n", grade1, grade3);
        while(fgets(temp, 500, fp10)) {
          fprintf(fp2, "%s", temp);
          //printf("test2");
        }
        fprintf(fp2, "\n====================\nDesign\n====================\n\n%d/%d points\n", grade2, grade4);
        while(fgets(temp, 500, fp20)) {
          fprintf(fp2, "%s", temp);
          //printf("test3");
        }
        fprintf(fp2, "\n====================");
        if (fp2) fclose(fp2);
        fp2 = fopen("grade.txt", "r");
      } else {
        if (fp10) fclose(fp10);
        if (fp20) fclose(fp20);
      }
    }
    if (!fp2) printf("grade.txt does not exist for %s\n", fileList[i]->d_name);
    else {
      printf("Finished Compiling %s\n", fileList[i]->d_name);
      if (fgets(temp, 500, fp2)) {
        strncpy (temp1, temp, 501);
        temp1[strlen(temp1) - 1] = '\0';
        sprintf (temp, "%s: %s (Performance: %d points, Design: %d points)\n", fileList[i]->d_name, temp1, grade1, grade2);
        fputs(temp, fp);
      }
      fclose(fp2);
      fclose(fp10);
      fclose(fp20);
    }
    chdir("..");
  }
  fclose(fp);
  for (int i = 0; i < filecount; i++)
    free(fileList[i]);
  free(fileList);
}

void restoreGrades(char *dir) { //buggy
  if (strncmp(dir, "pa", 2)) {
    printf("This method is unavailable for this directory");
    return;
  }
  char path[501];
  //	sprintf(path, "/afs/cats.ucsc.edu/class/cmps011-pt.w15/bin/%s/mail_all", dir);
  //	FILE *fp = fopen(path, "w");
  //FILE *fp;
  struct dirent **fileList;
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/performance", dir);
  int filecount;
  if (chdir(path) != 0) {
    printf("Trouble switching to performance backup directory\n");
    return;
  }
  filecount = scandir(".", &fileList, NULL, alphasort);
  char temp[501];
  //char temp1[501];
  int j;
  for (int i = 2; i < filecount; i++) { //start at i = 2 because we are ignoring the "." and ".." directories
    for (j = 0; fileList[i]->d_name[j] != '_'; j++) {
      path[j] = fileList[i]->d_name[j];
    }
    path[j] = '\0';
    sprintf(temp, "cp %s_performance.txt /afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s/performance.txt", path, dir, path);
    system(temp);
    printf("Restoring performance.txt for %s\n", path);
  }
  for (int i = 0; i < filecount; i++)
    free(fileList[i]);
  free(fileList);
  printf("Restored %d performance.txt files\n", filecount - 2);
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/design", dir);
  if (chdir(path) != 0) {
    printf("Trouble switching to design backup directory\n");
    return;
  }
  filecount = scandir(".", &fileList, NULL, alphasort);
  for (int i = 2; i < filecount; i++) { //start at i = 2 because we are ignoring the "." and ".." directories
    for (j = 0; fileList[i]->d_name[j] != '_'; j++) {
      path[j] = fileList[i]->d_name[j];
    }
    path[j] = '\0';
    sprintf(temp, "cp %s_design.txt /afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s/design.txt", path, dir, path);
    system(temp);
    printf("Restoring design.txt for %s\n", path);
  }
  for (int i = 0; i < filecount; i++)
    free(fileList[i]);
  free(fileList);
  printf("Restored %d design.txt files\n", filecount - 2);
  getGrades(dir);
}

void testGrade(char *dir) {
  if (strncmp(dir, "pa2", 4)) {
    printf("This method is not yet ready\n");
    return;
  }
  char path[500];
  FILE *fp;
  FILE *fp2;
  struct dirent **fileList;
  sprintf(path, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s", dir);
  int filecount;
  if (chdir(path) != 0) {
    printf("Trouble switching to the specified directory\n");
    return;
  }
  filecount = scandir(".", &fileList, NULL, alphasort);
  char *fl[filecount];
  for (int l = 0; l < filecount; l++) {
    fl[l] = fileList[l]->d_name;
  }
  char temps[501];
  char temps1[501];
  char mode = '2';
  List *l = listCreate(fl, filecount, dir, 2);
  List *ltemp = NULL;
  if (!l) {
    printf("Error compiling list");
    return;
  }
  sprintf(temps, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s", dir, l->first->sdir);
  chdir(temps);
  printf("Type '-h' for help\n");
  Node *temp = l->first;
  while (1) {
    printf("auto> ");
    gets(temps1);
    if (strncmp(temps1, "-h", 2) == 0) {
      printf("List of commands:\n-f - go to first directory\n-l - go to last directory\n-n - go to next directory\n-p - go to previous directory\n-ce - check Extrema.java\n-ct - check tests.txt\n-cd - check diff*\n-co - check out*\n-cg - check peformance.txt and design.txt\n-cm - check Makefile\n-c - check major files\n-m - change modes\n-ftr - filter the list to only have directories that contain (or don't by adding '!') a file\n-ft - fast filter that accepts direct argument and otherwise works like -ftr\n-vdt - open design.txt in vim\n-vpt - open performance.txt in vim\n-vbt - open bugs.txt\n-vgt - open grade.txt in vim\n-e - exit the program securely\n-h - bring up help\ntype anything else and it will be run as a unix command\n");
    } else if (strncmp(temps1, "-f", 3) == 0) {
      temp = l->first;
      chdir("..");
      chdir(temp->sdir);
    } else if (strncmp(temps1, "-n", 3) == 0) {
      if (temp->next) {
        temp = temp->next;
        chdir("..");
        chdir(temp->sdir);
      } else printf("No next directory\n");
    } else if (strncmp(temps1, "-p", 3) == 0) {
      if (temp->prev) {
        temp = temp->prev;
        chdir("..");
        chdir(temp->sdir);
      } else printf("No previous directory\n");
    } else if (strncmp(temps1, "-l", 3) == 0) {
      temp = l->last;
      chdir("..");
      chdir(temp->sdir);
    } else if (strncmp(temps1, "-m", 3) == 0) {
      do {
        printf("Enter a mode: 0 for ungraded, 1 for graded, 2 for mixed: ");
        mode = getchar();
      } while(mode < 48 || mode > 50);
      ltemp = listCreate(fl, filecount, dir, (int) mode - 48);
      if (!ltemp) {
        printf("%s mode has has no directories, try %s mode or mixed mode\n", mode == 48 ? "ungraded" : "graded", mode == 49 ? "ungraded" : "graded");
      } else {
        listDestroy(l);
        l = ltemp;
        ltemp = NULL;
        temp = l->first;
        chdir("..");
        chdir(temp->sdir);
        printf("Changing to mode %d\n", (int) mode - 48);
      }
    } else if (strncmp(temps1, "-e", 3) == 0) {
      getGrades(dir);
      printf("Exiting program\n");
      break;
    } else if (strncmp(temps1, "-vpt", 5) == 0) {
      fp = fopen("performance.txt", "r");
      if (!fp) {
        sprintf(temps1, "cp /afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/performance.txt .", dir);
        system(temps1);
      } else fclose(fp);
      system("vi performance.txt");
    } else if (strncmp(temps1, "-vdt", 5) == 0) {
      fp = fopen("design.txt", "r");
      if (!fp) {
        sprintf(temps1, "cp /afs/cats.ucsc.edu/class/cmps012b-pt.s15/bin/%s/design.txt .", dir);
        system(temps1);
        fp = fopen("design.txt", "a");
        fprintf(fp, "\n\n");
        fp2 = fopen("design.temp", "r");
        if (fp2) while (fgets(temps1, 500, fp2)) {
          fprintf(fp, "%s", temps1);
        }
        if (fp2) fclose(fp2);
      }
      fclose(fp);
      system("vi design.txt");
    } else if (strncmp(temps1, "-vgt", 5) == 0) {
      system("vi grade.txt");
    //} else if (strncmp(temps1, "-pvgt", 6) == 0) {
    //  fp = fopen("grade.txt", "w");
    //  fprintf(fp, "%s points\n", (strncmp(dir, "pa3", 4) == 0 || strncmp(dir, "pa2", 4) == 0 || strncmp(dir, "pa1", 4)) ? "80/80" : "100/100");
    //  fclose(fp);i
    } else if (strncmp(temps1, "-vbt", 5) == 0) {
      system("vi bugs.txt");
    } else if (strncmp(temps1, "-c", 3) == 0) {
      system("more tests.txt");
      system("more *");
      fp = fopen("bugs.txt", "r");
      printf("%s", fp ? "::::::::::::::\nBUGS.TXT EXISTS!\n" : "");
      if (fp) fclose(fp);
    } else if (strncmp(temps1, "-cc", 4) == 0) {
      system("more tests.txt bugs.txt performance.txt design.txt design.temp diff1 diff21 diff31 diff41 Search.java Makefile README tests.txt");
    } else if (strncmp(temps1, "-ct", 4) == 0) {
      system("more tests.txt");
    } else if (strncmp(temps1, "-cm", 4) == 0) {
      system("more Makefile");
    } else if (strncmp(temps1, "-cd", 4) == 0) {
      system("more diff*");
    } else if (strncmp(temps1, "-cg", 4) == 0) {
      system("more performance.txt design.txt");
    } else if (strncmp(temps1, "-ce", 4) == 0) {
      system("more Search.java");
    } else if (strncmp(temps1, "-co", 4) == 0) {
      system("more out*");
    } else if (strncmp(temps1, "-pos", 5) == 0) {
      printf("Your current position is %d out of %d\n", listGetPos(l, temp), listGetSize(l));
    } else if (strncmp(temps1, "-ftr", 5) == 0) {
      printf("Please enter the name of the text file you would like to filter for (add '!' to front of name to make it filter to directories without the file): ");
      fgets(temps1, 500, stdin);
      //printf("The thing being filtered is: %s which is size %d\n", temps1, strlen(temps1));
      int tempint = listGetSize(l);
      listFilter(l, dir, temps1);
      if (tempint != listGetSize(l)) {
        temp = l->first;
        chdir("..");
        chdir(temp->sdir);
      }
    } else if (strncmp(temps1, "-ft ", 4) == 0) {
      //printf("Please enter the name of the text file you would like to filter for (add '!' to front of name to make it filter to directories without the file): ");
      strncpy(temps, temps1 + 4, 500);
      temps[strlen(temps)] = '\n';
      temps[strlen(temps) + 1] = '\0';
      //printf("The thing being filtered is: %s which is size %d\n", temps, strlen(temps));
      int tempint = listGetSize(l);
      listFilter(l, dir, temps);
      if (tempint != listGetSize(l)) {
        temp = l->first;
        chdir("..");
        chdir(temp->sdir);
      }
    } else {
      //printList(l);
      //printf("The size of the list is %d\n", listGetSize(l));
      system(temps1);
    }
  }
  for (int i = 0; i < filecount; i++)
    free(fileList[i]);
  free(fileList);
  listDestroy(l);
}

int main(int argc, char **argv) {
  if (argc == 3) {
    char *asg = argv[2];
    char *method = argv[1];
    if (strncmp(method, "-m", 3) == 0) sendMail(asg);
    else if (strncmp(method, "-g", 3) == 0) getGrades(asg);
    else if (strncmp(method, "-r", 3) == 0) testGrade(asg);
    else if (strncmp(method, "-a", 3) == 0) autoGrade(asg);
    else if (strncmp(method, "-b", 3) == 0) restoreGrades(asg);
    else {
      printf("Invalid method, Usage: [Method] [directory name for assignment]\n");
      return 1;
    }
  } else {
    printf("Usage: [Method] [directory name for assignment]\n");
    return 1;
  }
  return 0;
}
