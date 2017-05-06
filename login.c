#define UNAME_MAX	10

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = {"sh", 0};

int
lookupUser(char* uname)
{
	int fd = open("/logins", O_RDONLY);
	char uname_valid[UNAME_MAX+1];
	
	while (1)
	{
		read(fd, buf, 1);

		// uname doesn't exist
		if (buf[0] == '\0')	
			return -1;

		
		if (buf[0] == '\n')
		{
			uname_valid[j++] = '\0'; 
			
			if (strcmp(uname_valid, uname) != 0){
				j = 0;
				printf(1, "correct:\n");
				printf(1, uname_valid);
			}
			else
			{
				pid = fork();
				
				if (pid ==0)
					exec("sh", argv);
				
				else 
					break;	
			}	
		}
		else
			uname_valid[j++] = buf[0];
	
	}
	close (fd);
	
}

int
main()
{
	char uname[UNAME_MAX+1];
	char buf[1];
	int j, pid;
	
	int fd = open("/logins", O_RDONLY);
	char uname_valid[UNAME_MAX+1];
	
	printf(1, "\nusername: ");
	for (j=0; j < UNAME_MAX && read(0, buf, 1) == 1 
			&& buf[0] != '\n'; j++)
	{
		uname[j] = buf[0];
	}

	if (j >= UNAME_MAX)
	{
		printf(1, "\ninvalid username");
		exit();
	}

	uname[j+1] = '\0';
	j=0;

	while (1)
	{
		read(fd, buf, 1);
		if (buf[0] == '\0')	
		{
			printf(1, "\ninvalid username");
			exit();
		}

		if (buf[0] == '\n')
		{
			uname_valid[j++] = '\0'; 
			
			if (strcmp(uname_valid, uname) != 0){
				j = 0;
				printf(1, "correct:\n");
				printf(1, uname_valid);
			}
			else
			{
				pid = fork();
				
				if (pid ==0)
					exec("sh", argv);
				
				else 
					break;	
			}	
		}
		else
			uname_valid[j++] = buf[0];
	
	}
	close (fd);
	wait();
	return 0;
}
