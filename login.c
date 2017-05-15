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

char *argv[] = {"sh", 0};

int
main()
{
	char uname[UNAME_MAX+1];
	char buf[1];
	int j, pid, uid;
	
	printf(1, "\nusername: ");
	for (j=0; j < UNAME_MAX && read(0, buf, 1) == 1 
			&& buf[0] != '\n'; j++)
	{
		uname[j] = buf[0];
	}

	uname[j] = '\0';

	uid = lookupUser(uname);	
	if (uid == -1)
	{
		printf(1, "\ninvalid username");
		exit();
	}

	setUid(uid);
	printf(1, "username accepted.\nuid:%d\n", getUid());
	pid = fork();
	if (pid ==0)
		exec("sh", argv);
	else
		wait();

	return 0;
}
