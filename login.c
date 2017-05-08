#define UNAME_MAX	10
#define UID_MAXLEN	10	//10 digit number 9999999999 is the max userID possible

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argv[] = {"sh", 0};

int 
power(int base, int exp)
{
	int res = 1;
	int i=0;
	for (; i<exp; i++)
		res *= base;

	return res;
}

int 
getIntId(int fd)
{
	char buf[1];
	char uid_char[UID_MAXLEN];
	int res, id_len, i;
	
	id_len = 0;
	read(fd, buf, 1);
	while (buf[0] != '\n')
	{
		uid_char[id_len++] = buf[0];	
		read(fd, buf, 1);
	}

	uid_char[id_len] = '\0';
	printf(1, uid_char);
	printf(1, "len:%d", id_len);

	res = 0;
	for (i=0; i<id_len; i++)
	{
		res += (uid_char[i]-'0')*power(10, id_len-i-1);
	}
	return res;
}

int
lookupUser(char* uname)
{
	int fd = open("/logins", O_RDONLY);
	char uname_valid[UNAME_MAX+1];
	char buf[1];
	int j=0;
	int ret=-1;

	while (1)
	{
		read(fd, buf, 1);

		// uname doesn't exist
		if (buf[0] == '\0')	
			break;
		
		if (buf[0] == ':')
		{
			uname_valid[j++] = '\0'; 
			
			if (strcmp(uname_valid, uname) != 0){
				j = 0;
			}
			else{
				ret = getIntId(fd);
				break;
			}
		}
		else{
			uname_valid[j++] = buf[0];
		}
	}
	close (fd);
	return ret;
}

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
	j=0;

	uid = lookupUser(uname);	
	if (uid == -1)
	{
		printf(1, "\ninvalid username");
		exit();
	}
	
	printf(1, "\nuid:%d", uid);

	pid = fork();
	if (pid ==0)
		exec("sh", argv);
	else
		wait();

	return 0;
}
