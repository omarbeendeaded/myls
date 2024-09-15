#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "util.h"

Entry makeEntry (char* path, DIR* dp)
{
	Entry entry;
	struct dirent* ent = readdir(dp);

	// Get full path to file
	int fullLength = strlen(path) + strlen(ent->d_name) + 2;
	char* fullPath = malloc(fullLength * sizeof(char));
	strcpy(fullPath, path);
	if (fullPath[strlen(path) - 1] != '/') strcat(fullPath, "/");

	strcat(fullPath, ent->d_name);
	
	entry.name = strdup(ent->d_name);
	entry.path = fullPath;
	
	entry.inode = ent->d_ino; // Get inode number


	struct stat st;
	if (lstat(fullPath, &st) < 0)
	{
		printf("failed to open stat\n");
		exit(0);
	}

	entry.nlink = st.st_nlink; // Get number of hard links
	entry.size  = st.st_size;  // Get size of file in bytes

	getPermissions(st.st_mode, entry.perms); // Create permissions string
	
	// Times
	entry.atime = st.st_atim;
	entry.mtime = st.st_mtim;
	entry.ctime = st.st_ctim;

	// Group name
	struct group* grp = getgrgid(st.st_gid);
	entry.group = strdup(grp->gr_name);

	// User name
	struct passwd* pwd = getpwuid(st.st_uid);
	entry.user = strdup(pwd->pw_name);

	return entry;
}

void getPermissions (mode_t mode, char str[11])
{	 
	strcpy(str, "----------");

	// File type
	if ((mode & 0170000) == 0140000) str[0] = 's';
	if ((mode & 0170000) == 0120000) str[0] = 'l';
	if ((mode & 0170000) == 0060000) str[0] = 'b';
	if ((mode & 0170000) == 0040000) str[0] = 'd';
	if ((mode & 0170000) == 0020000) str[0] = 'c';
	if ((mode & 0170000) == 0010000) str[0] = 'p';

	// Owner  permissions
	if((mode & 0000400) == 0000400) str[1] = 'r';
	if((mode & 0000200) == 0000200) str[2] = 'w';
	if((mode & 0000100) == 0000100) str[3] = 'x';
	
	// Group permissions
	if((mode & 0000040) == 0000040) str[4] = 'r';
	if((mode & 0000020) == 0000020) str[5] = 'w';
	if((mode & 0000010) == 0000010) str[6] = 'x';
	
	// Others  permissions
	if((mode & 0000004) == 0000004) str[7] = 'r';
	if((mode & 0000002) == 0000002) str[8] = 'w';
	if((mode & 0000001) == 0000001) str[9] = 'x';
	
	// Special  permissions
	if((mode & 0004000) == 0004000)
	{
	      	if (str[3] == 'x') str[3] = 's';
		else               str[3] = 'S';
	}
	
	if((mode & 0002000) == 0002000)
	{
	      	if (str[6] == 'x') str[6] = 's';
		else               str[6] = 'S';
	}
	
	if((mode & 0001000) == 0001000)
	{
	      	if (str[9] == 'x') str[9] = 't';
		else               str[9] = 'T';
	}
}


int cmpName (const void* p1, const void* p2)
{
	const Entry* ent1 = (Entry*) p1;
	const Entry* ent2 = (Entry*) p2;

	return strcoll(ent1->name, ent2->name);
}

int cmpaTime (const void* p1, const void* p2)
{
	const Entry* ent1 = (Entry*) p1;
	const Entry* ent2 = (Entry*) p2;

	if      (ent1->atime.tv_sec < ent2->atime.tv_sec) return 1;
	else if (ent1->atime.tv_sec > ent2->atime.tv_sec) return -1;
	else                                              return 0;
}

int cmpmTime (const void* p1, const void* p2)
{
	const Entry* ent1 = (Entry*) p1;
	const Entry* ent2 = (Entry*) p2;

	if      (ent1->mtime.tv_sec < ent2->mtime.tv_sec) return 1;
	else if (ent1->mtime.tv_sec > ent2->mtime.tv_sec) return -1;
	else                                              return 0;
}

int cmpcTime (const void* p1, const void* p2)
{
	const Entry* ent1 = (Entry*) p1;
	const Entry* ent2 = (Entry*) p2;

	if      (ent1->ctime.tv_sec < ent2->ctime.tv_sec) return 1;
	else if (ent1->ctime.tv_sec > ent2->ctime.tv_sec) return -1;
	else                                              return 0;
}


void printLongList (Entry entry, int dispTime)
{
	printf("%s %lu %s %s %-5lu ", entry.perms, entry.nlink, entry.user, entry.group, entry.size);

	// Get last modified time
	struct tm* timeinfo;
	
	switch (dispTime)
	{
		case ATIM: timeinfo = localtime(&entry.atime.tv_sec); break;
		case CTIM: timeinfo = localtime(&entry.ctime.tv_sec); break;
		default:    timeinfo = localtime(&entry.mtime.tv_sec); break;
	}
	
	
	
	char buf[80];
	strftime(buf, sizeof(buf), "%H:%M %d %b", timeinfo);
	printf("%s ", buf);

}



