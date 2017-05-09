#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int
main(){
	int fd, pid;
	fd = open("logins", O_RDWR);
	
	if (fd != -1)
	{
		close(fd);
		char *argv[] = {"rm", "/logins"};
		pid = fork();
		if (pid == 0)
		{
			exec("rm", argv);
			exit();
		}
		else
			wait();
	}
		
	fd = open("logins", O_CREATE|O_RDWR);
	write(fd, "root:0\n\0", 8);
	close(fd);
	return 0;
}

