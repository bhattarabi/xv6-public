#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int
main(){
	int fd;
	fd = open("logins", O_CREATE|O_RDWR);
	write(fd, "jim\ncleopatra\nthomas\n", 21);
	close(fd);
	return 0;
}

