#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <string.h>
#include <errno.h>

int randNum(int *p) {
  int fd = open("/dev/random",O_RDONLY);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  int ret = read(fd,p,sizeof(int));
  close(fd);
  return ret;
}

int main() {
  //Part 1: reading in random numbers - works
  int *p = (int*)malloc(10*sizeof(int));
  int i;
  for (i = 0; i < 10; i++) {
    randNum(p+i);
  }
  for (i = 0; i < 10; i++) {
    printf("Integer #%d: %d\n",i+1,*(p+i));
  }

  //Part 2: writing them to a new file - maybe works?
  int fd = open("randnums",O_CREAT | O_WRONLY,0644);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  printf("%lu\n",sizeof(p));
  write(fd,p,10*sizeof(int));
  close(fd);

  //Part 3: reading them back from the file - maybe works?
  fd = open("randnums",O_RDONLY);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  int *p2[10];
  read(fd,p2,sizeof(int));
  for (i = 0; i < 10; i++) {
    p2[i] = (int*)malloc(sizeof(int));
    read(fd,p2[i],sizeof(int));
  }
  for (i = 0; i < 10; i++) {
    printf("Integer #%d (2nd round): %d\n",i+1,*p2[i]);
  }
  
}
