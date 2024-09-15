#ifndef _UTIL_H_
#define _UTIL_H_

#define MTIM   0
#define CTIM   1
#define ATIM   2
#define NAME   3
#define NOSORT 4

typedef struct 
{
	ino_t inode;
	nlink_t nlink;

	off_t size;

	char* name;
	char* path;

	char perms[11];

	char* user;
	char* group;
	
	struct timespec atime;
	struct timespec mtime;
	struct timespec ctime;
} Entry;


Entry makeEntry      (char* path, DIR* dp); 
void  getPermissions (mode_t mode, char str[11]);
void  printLongList  (Entry entry, int dispTime);
int   cmpName        (const void* p1, const void* p2);
int   cmpaTime       (const void* p1, const void* p2);
int   cmpmTime       (const void* p1, const void* p2);
int   cmpcTime       (const void* p1, const void* p2);


#endif
