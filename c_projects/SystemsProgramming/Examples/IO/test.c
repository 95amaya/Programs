#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void helper(DIR *, struct dirent *, struct stat, char *, int, char **);
void dircheck(DIR *, struct dirent *, struct stat, char *, int, char **);

int main(int argc, char *argv[]){

  DIR *dip;
  struct dirent *dit;
  struct stat statbuf;
  char currentPath[FILENAME_MAX];
  int depth = 0; /*Used to correctly space output*/

  /*Open Current Directory*/
  if((dip = opendir(".")) == NULL)
    return errno;

  /*Store Current Working Directory in currentPath*/
  if((getcwd(currentPath, FILENAME_MAX)) == NULL)
    return errno;

  /*Read all items in directory*/
  while((dit = readdir(dip)) != NULL){

    /*Skips . and ..*/
    if(strcmp(dit->d_name, ".") == 0 || strcmp(dit->d_name, "..") == 0)
      continue;

    /*Correctly forms the path for stat and then resets it for rest of algorithm*/
    getcwd(currentPath, FILENAME_MAX);
    strcat(currentPath, "/");
    strcat(currentPath, dit->d_name);
    if(stat(currentPath, &statbuf) == -1){
      perror("stat");
      return errno;
    }
    getcwd(currentPath, FILENAME_MAX);


    /*Checks if current item is of the type file (type 8) and no command line arguments*/
    if(S_ISREG(statbuf.st_mode) && argv[1] == NULL)
      printf("%s (%d bytes)\n", dit->d_name, (int)statbuf.st_size);

    /*If a command line argument is given, checks for filename match*/
    if(S_ISREG(statbuf.st_mode) && argv[1] != NULL)
      if(strcmp(dit->d_name, argv[1]) == 0)
         printf("%s (%d bytes)\n", dit->d_name, (int)statbuf.st_size);

    /*Checks if current item is of the type directory (type 4)*/
    if(S_ISDIR(statbuf.st_mode))
      dircheck(dip, dit, statbuf, currentPath, depth, argv);

  }
  closedir(dip);
  return 0;
}

/*Recursively called helper function*/
void helper(DIR *dip, struct dirent *dit, struct stat statbuf, 
        char currentPath[FILENAME_MAX], int depth, char *argv[]){
  int i = 0;

  if((dip = opendir(currentPath)) == NULL)
    printf("Error: Failed to open Directory ==> %s\n", currentPath);

  while((dit = readdir(dip)) != NULL){

    if(strcmp(dit->d_name, ".") == 0 || strcmp(dit->d_name, "..") == 0)
      continue;

    strcat(currentPath, "/");
    strcat(currentPath, dit->d_name);
    stat(currentPath, &statbuf);
    getcwd(currentPath, FILENAME_MAX);

    if(S_ISREG(statbuf.st_mode) && argv[1] == NULL){
      for(i = 0; i < depth; i++)
    printf("    ");
      printf("%s (%d bytes)\n", dit->d_name, (int)statbuf.st_size);
    }

    if(S_ISREG(statbuf.st_mode) && argv[1] != NULL){
      if(strcmp(dit->d_name, argv[1]) == 0){
    for(i = 0; i < depth; i++)
      printf("    ");
    printf("%s (%d bytes)\n", dit->d_name, (int)statbuf.st_size);
      }
    }

    if(S_ISDIR(statbuf.st_mode))
      dircheck(dip, dit, statbuf, currentPath, depth, argv);
  }
  /*Changing back here is necessary because of how stat is done*/
    chdir("..");
    closedir(dip);
}

void dircheck(DIR *dip, struct dirent *dit, struct stat statbuf, 
          char currentPath[FILENAME_MAX], int depth, char *argv[]){
  int i = 0;

  strcat(currentPath, "/");
  strcat(currentPath, dit->d_name);

  /*If two directories exist at the same level the path
    is built wrong and needs to be corrected*/
  if((chdir(currentPath)) == -1){
    chdir("..");
    getcwd(currentPath, FILENAME_MAX);
    strcat(currentPath, "/");
    strcat(currentPath, dit->d_name);

    for(i = 0; i < depth; i++)
      printf ("    ");
    printf("%s (subdirectory)\n", dit->d_name);
    depth++;
    helper(dip, dit, statbuf, currentPath, depth, argv);
  }

  else{
    for(i =0; i < depth; i++)
      printf("    ");
    printf("%s (subdirectory)\n", dit->d_name);
    chdir(currentPath);
    depth++;
    helper(dip, dit, statbuf, currentPath, depth, argv);
  }
}