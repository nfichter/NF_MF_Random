#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <string.h>
#include <errno.h>

/*
Michael and I worked on this over the phone both looking at the code together, but we decided that
only one of us should actually be committing and pushing the file so we don't have a bunch of conflicts.
(In other words, yes, he did work.)

Also, something I found was quite interesting: since /dev/random generates random integers by using the computer's
"entropy", it starts off SUPER fast and gets SUPER slow after a few runs because it no longer has enough entropy to
generate these integers, so you have to do a bunch of random stuff on your computer to have it generate more integers.
*/

//Takes a pointer, reads a random integer from /dev/random to it, and returns the number of bytes read
int randNum(int *p) {
  //open with read flag & error check
  int fd = open("/dev/random",O_RDONLY);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  //read, close, return
  int ret = read(fd,p,sizeof(int));
  close(fd);
  return ret;
}

int main() {
  //PART 1: READING IN RANDOM NUMBERS - works
  //allocate 10*sizeof(int) bytes of memory to a new pointer - effectively our array
  int *p = (int*)malloc(10*sizeof(int));
  int i;
  printf("\n===Reading in===\n");
  //apply the randNum function to every sizeof(int) bytes in the pointer by incrementing it by 1 every time 
  for (i = 0; i < 10; i++) {
    printf("Reading in %d bytes\n",randNum(p+i));
  }
  //print them out
  printf("\n===Printing===\n");
  for (i = 0; i < 10; i++) {
    printf("Integer #%d: %d\n",i+1,*(p+i));
  }

  //PART 2: WRITING THEM TO A NEW FILE - works
  //open with create and write flags & error check
  int fd = open("randnums",O_CREAT | O_WRONLY,0644);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  //write the pointer's contents (all 10*sizeof(int) bytes of it) to the file, close
  printf("\n===Writing out bytes===\n");
  printf("Writing %zu bytes\n",write(fd,p,10*sizeof(int)));
  close(fd);

  //PART 3: READING THEM BACK FROM THE NEW FILE - works
  //reopen with read flag & error check
  fd = open("randnums",O_RDONLY);
  if (fd == -1) {
    printf("%d - %s",errno,strerror(errno));
    return 0;
  }
  printf("\n===Reading in===\n");
  //new pointer, same initialization as p
  int *p2 = (int*)malloc(10*sizeof(int));
  //read all 10*sizeof(int) bytes from the file into p2
  printf("Reading in %zu bytes\n",read(fd,p2,10*sizeof(int)));
  //print them out
  printf("\n===Printing===\n");
  for (i = 0; i < 10; i++) {
    printf("Integer #%d (2nd round): %d\n",i+1,*(p2+i));
  }
  
}
