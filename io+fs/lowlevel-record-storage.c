#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "io+fs/record-storage.h"

#define FILE_NAME "records.dat"


int usage(char *argv0, char *message) {
  printf(help_text, message, argv0, argv0);
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc >= 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[2], "-H") == 0)) {
    usage(argv[0], "");
  }
  if (argc != 3 && argc != 6) {
    usage(argv[0], "wrong number of arguments");
  }
  char *command = argv[1];
  struct rec data;
  void *raw = (void *)&data;
  size_t size = sizeof(struct rec);
  
  if (strcmp(command, "W") == 0) {
    if (argc != 6) {
      usage(argv[0], "wrong number of arguments for write");
    }
    int pos = atoi(argv[2]);
    if (pos < 0 || pos > 1000000) {
      usage(argv[0], "pos out of range (0..1000000)");
    }
    strncpy(data.name, argv[3], 255);
    data.name[255] = '\000';
    data.account_number = atoi(argv[4]);
    if (data.account_number <= 0) {
      usage(argv[0], "account number must be > 0");
    }
    data.size_in_meter = atof(argv[5]);
    if (data.size_in_meter <= 0) {
      usage(argv[0], "size in meter must be > 0");
    }
    int fd = open(FILE_NAME, O_CREAT | O_WRONLY, 0660);
    off_t retcode = lseek(fd, size * pos, SEEK_SET);
    if (retcode < 0) {
      exit(1);
    }
    ssize_t ws = write(fd, raw, size);
    printf("written rc=%d ws=%d\n", (int) retcode, (int) ws);
    close(fd);
  } else if (strcmp(command, "R") == 0) {
    if (argc != 3) {
      usage(argv[0], "wrong number of arguments for read");
    }
    int pos = atoi(argv[2]);
    if (pos < 0 || pos > 1000000) {
      usage(argv[0], "pos out of range (0..1000000)");
    }
    int fd = open(FILE_NAME, O_APPEND | O_CREAT | O_RDONLY, 0660);
    lseek(fd, size * pos, SEEK_SET);
    ssize_t rs = read(fd, raw, size);
    close(fd);
    if (rs < 0) {
      printf("error reading: %d errno=%d\n", (int) rs, (int) errno);
      exit(1);
    }
    if (rs == 0) {
      printf("no data read");
      exit(0);
    }
    printf("name=\"%s\" account=%d size=%f\n", data.name, data.account_number, data.size_in_meter);
  } else {
    usage(argv[0], "unknown command");
  }
  exit(0);
}
