/*****************************************************************
* NAME
* stack_overflow.c
*
* SYNOPSIS
* stack_overflow
*
* DESCRIPTION
* Prints Result of Stringcomaper to stdout
*
* AUTHOR
* Philipp Aeschlimann, HSZ-T paeschli@hsz-t.ch
*
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0 

int main( int argc, char *argv[] ){
  int valid = FALSE;
  char str1[8];
  char str2[8];
  
  str2[0] = 'S';
  str2[1] = 'E';
  str2[2] = 'C';
  str2[3] = 'R';
  str2[4] = 'E';
  str2[5] = 'T';
  str2[6] = (char) 0;

  printf("READING:\n\n");
  gets(str1);
  printf("READ:\n\n");
  if (strncmp(str1, str2, 8) == 0) {
    valid = TRUE;
  }
  printf("buffer1: str1=%s str2=%s valid=%d\n", str1, str2, valid);
  exit(0);
}
