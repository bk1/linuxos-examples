/* Nach: An Introductory 4.3BSD IPC Tutorial, S. Sechrest */
/* 03.12.04 / gle */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    printf("Child executing \"/bin/date\"\n");
    execl("/bin/date", "date", (char *) 0);

    printf ("This should not happen!\n");
  }
  printf ("Parent waiting for child to finish: child pid=%d\n", pid);
  pid = wait(&status);
  printf("Parent: Child just terminated: pid=%d.\n", pid);
  exit(0);
}
