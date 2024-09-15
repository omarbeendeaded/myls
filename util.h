#ifndef _UTIL_H_
#define _UTIL_H_

#define MTIM   0
#define CTIM   1
#define ATIM   2
#define NAME   3
#define NOSORT 4

// Define ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

typedef struct 
{
	ino_t   inode;
	nlink_t nlink;
	mode_t  mode;

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
void  printColor     (Entry entry, int maxLen, char* str);
int   cmpName        (const void* p1, const void* p2);
int   cmpaTime       (const void* p1, const void* p2);
int   cmpmTime       (const void* p1, const void* p2);
int   cmpcTime       (const void* p1, const void* p2);


#endif
