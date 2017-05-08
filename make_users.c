#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int
main(){
	int fd;
	fd = open("logins", O_CREATE|O_RDWR);
	write(fd, "root:0\nbob:434\n\0", 19);
	close(fd);
	return 0;
}

