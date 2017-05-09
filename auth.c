#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "auth.h"


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
			uname_valid[j] = '\0'; 
			if (strcmp(uname, uname_valid) != 0){
				while (buf[0]!='\n')
					read(fd, buf, 1);
					
				printf(1, "j=%d\n", j);
				printf(1, uname);
				printf(1, "yyy\n");
				printf(1, uname_valid);
				printf(1, "xxx\n");
				j =0;
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
