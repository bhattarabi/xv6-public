#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

int
main(int argc, char *argv[])
{
  // file descriptors in, our, # of bytes copied
  int fdi, fdo, n;

  if(argc <= 2){
    printf(1, "cp: need 2 arguments\n");
    exit();
  }

  if ((fdi = open(argv[1], O_RDONLY)) <0){
	printf(1, "cp: cannot open %s\n", argv[1]);
	exit();
  }

  if ((fdo = open(argv[2], O_CREATE|O_RDWR)) <0){
	printf(1, "cp: cannot open %s\n", argv[2]);
	exit();
  }

  while ((n=read(fdi, buf, sizeof(buf))) > 0) {
	write(fdo, buf, n);
  }

  close(fdi);
  close(fdo);

  exit();
}
