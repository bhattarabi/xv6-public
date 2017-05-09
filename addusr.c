#include "types.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "buf.h"
#include "mmu.h"
#include "param.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "file.h"
#include "auth.h"
#include "proc.h"

int
main() {
	char uname[UNAME_MAX+1];
	char buf[1];
	struct stat st;
	int j, pid, fd1, fd2, nextid;

	if (getUid()!= 0)
	{
		printf(1, "Error: user does not have permission to run this command!\n");
		exit();
	}
	
	// get new username from fd1(keyboard)
	printf(1, "\nusername: ");
	for (j=0; j < UNAME_MAX && read(0, buf, 1) == 1 
			&& buf[0] != '\n'; j++)
	{
		uname[j] = buf[0];
	}

	// get next uid to be used for this user
	fd1 = open("/nextUid", O_RDWR);
	if (fd1 == -1)
		nextid = 1;
	else
	{
		nextid = getIntId(fd1);
		close(fd1);
		char *argv[] = {"rm", "/nextUid"};
		pid = fork();
		if (pid == 0)
		{
			exec("rm", argv);
			exit();
		}
		else
			wait();
	}

	// current size of logins file
	fd2 = open("/logins", O_RDWR);
	fstat(fd2, &st);
	
	// move logins to new file and add new user to its tail
	char oldfile[st.size - 1];
	
	for (j=0; j<st.size-1; j++)
	{
		read(fd2, buf, 1);
		oldfile[j] = buf[0];
	}
	close (fd2);

	char *argv[] = {"rm", "/logins"};
	pid = fork();
	if (pid == 0)
	{
		exec("rm", argv);
		exit();
	}
	else
		wait();

	
	fd2 = open("/logins", O_CREATE|O_RDWR);
	write(fd2, oldfile, st.size-1);

	printf(fd2, uname);
	printf(fd2, ":%d\n", nextid++);
	write(fd2, "\0", 1);
	close(fd2);

	// upate next available uid
	fd1 = open("/nextUid", O_CREATE|O_RDWR);
	printf(fd1, "%d\n", nextid);
	close(fd1);

	return 0;
}
