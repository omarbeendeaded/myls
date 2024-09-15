#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <sys/ioctl.h>

#include "util.h"


char longList = 0; // -l -- use a long listing format
char all      = 0; // -a -- do not ignore entries starting with .
char sortTime = 0; // -t -- sort by time, newest first
char uOpt     = 0; // -u -- with -lt: sort by, and show, access time; with -l: show access time and sort by name; otherwise: sort by access time, newest first
char cOpt     = 0; // -c -- with  -lt:  sort  by, and show, ctime; with -l: show ctime and sort by name; otherwise: sort by ctime, newest first
char noSort   = 0; // -f -- do not sort
char inode    = 0; // -i -- print the inode number of each file
char pDir     = 0; // -d -- list directories themselves, not their contents
char oneOpt   = 0; // -1 -- list one file per line.


extern int errno, optind;
void do_ls(char*);

int main(int argc, char* argv[])
{
	// sleep(30);
	setlocale (LC_ALL, "");
	int opt;

	while ((opt = getopt(argc, argv, "latucifd1")) != -1)
	{
		switch (opt)
		{
			case 'l': longList = 1; break;
			case 'a': all      = 1; break;
			case 't': sortTime = 1; break;
			case 'u': uOpt     = 1; break;
			case 'c': cOpt     = 1; break;
			case 'f': noSort   = 1; break;
			case 'i': inode    = 1; break;
			case 'd': pDir     = 1; break;
			case '1': oneOpt   = 1; break;
			default :               break;
		}
	}

	if (optind < argc) while (optind < argc)
	{	
		if (!pDir && argc != 2) printf("%s:\n", argv[optind]);
		do_ls(argv[optind++]);
	}
	else do_ls(".");

	return 0;
}


void do_ls(char* dir)
{
	int count    = 0;
	int maxLen   = 0;
	int dispTime = MTIM;
	int sortType = NAME;

	// Open directory
	DIR * dp = opendir(dir);
	if (dp == NULL)
	{
		fprintf(stderr, "Cannot open directory:%s\n",dir);
		return;
	}

	// Create an array of entries
	while(readdir(dp) != NULL) count++;
	Entry* entries = malloc (count * sizeof(Entry));

	// Populate array
	rewinddir(dp);
	for (int i = 0; i < count; i++) 
	{
		entries[i] = makeEntry(dir, dp);

		if (entries[i].name[0] == '.' && !all) continue;
		maxLen = maxLen < strlen(entries[i].name) ? strlen(entries[i].name) : maxLen;
	}
	
	// Sort
	if (cOpt) // -c
	{
		if (longList && sortTime) 
		{
			dispTime = CTIM;
			sortType = CTIM;
		}
		else if (longList) 
		{
			dispTime = CTIM;
		}
		else
		{
			sortType = CTIM;
		}
	}
	
	if (uOpt) // -u
	{
		if (longList && sortTime) 
		{
			dispTime = ATIM;
			sortType = ATIM;
		}
		else if (longList) 
		{
			dispTime = ATIM;
		}
		else
		{
			sortType = ATIM;
		}
	}
	
	if (sortTime && !uOpt && !cOpt) // -t
	{
		sortType = MTIM;
	}
	
	if (noSort) // -f
	{
		sortType = NOSORT;
	}

	switch (sortType)
	{
		case NAME: qsort(entries, count, sizeof(Entry), cmpName);  break;
		case MTIM: qsort(entries, count, sizeof(Entry), cmpmTime); break;
		case ATIM: qsort(entries, count, sizeof(Entry), cmpaTime); break;
		case CTIM: qsort(entries, count, sizeof(Entry), cmpcTime); break;
	}

	// Terminal width
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); 

	for (int i = 0; i < count; i++) 
	{
		// -d
		if (pDir && strcmp(entries[i].name, ".") != 0) continue;
		
		// -a
		else if (!all && entries[i].name[0] == '.' && !pDir) continue;

		// -i
		if (inode) printf("%-7lu ", entries[i].inode);
		
		// -l
		if (longList) printLongList(entries[i], dispTime);

		if (!pDir) printf("%-*s  ", maxLen, entries[i].name);
		else       printf("%-*s  ", maxLen, dir);

		if (oneOpt || longList || i % (w.ws_col / (maxLen + (7 * inode) + 2)) == 0) printf("\n");
	}
	
	
	// Close directory
	printf("\n");
	closedir(dp);
	free(entries);
}
