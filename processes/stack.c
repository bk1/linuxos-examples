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
  
  str1[0] = 'S';
  str1[1] = 'E';
  str1[2] = 'C';
  str1[3] = 'R';
  str1[4] = 'E';
  str1[5] = 'T';
  str1[6] = 0;
  gets(str2);
  if( strncmp(str1, str2, 8) == 0 )
    valid = TRUE;
  printf("buffer1: str1(%s), str2(%s), valid(%d)", str1, str2, valid);
  exit(0);
}
