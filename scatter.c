#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int fd;
  int i;
  char fname[3];

  //create 100 files
  for (i=0; i<100; i++){
	fname[0] = (i/10) + '0';
	fname[1] = (i%10) + '0';
	fname[2]='\0';

	fd = open(fname, O_CREATE|O_RDWR);
	write(fd, "file\n", 5);
	close(fd);
  }

  //delete one in every three files
  for (i=0; i<100; i+=3){
	fname[0] = (i/10) + '0';
	fname[1] = (i%10) + '0';
	fname[2] = '\0';

	unlink(fname);
  }
  return 0;
}
