#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <string.h>
#include <errno.h>

int main() {
  int fd = open("/dev/random",O_RDONLY);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  int *p[10];
  int i;
  for (i = 0; i < 10; i++) {
    p[i] = (int*)malloc(10*sizeof(int));
    read(fd,p[i],sizeof(int));
  }
  for (i = 0; i < 10; i++) {
    printf("Integer #%d: %d\n",i+1,*p[i]);
  }

  int fd2 = open("randnums",O_CREAT | O_WRONLY,0644);
  if (fd2 == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  void *vp = p;
  int numwritten = write(fd2,vp,10*sizeof(int));

  close(fd);
  close(fd2);
  //added stuff vvv
  fd2 = open("randnums",O_RDONLY);
  if (fd2 == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  
  int *p2[10];
  for (i = 0; i < 10; i++) {
    p2[i] = (int*)malloc(10*sizeof(int));
    read(fd2,p2[i],sizeof(int));
  }
  for (i = 0; i < 10; i++) {
    printf("Integer #%d (2nd round): %d\n",i+1,*p2[i]);
  }
  
}
