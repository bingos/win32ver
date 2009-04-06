#define RET_WINDOWS 0
#define RET_WINDOWSNT 1
#define RET_WINDOWS2K 2
#define RET_WINDOWSXP 3
#define RET_WINDOWS2K3 4
#define RET_UNKNOWN 8

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define tolow(c)  (isupper(c) ? (c)-'A'+'a' : (c))    /* force to lower case */

struct WindowsINFO
{
	char winos[12];
	char release[10];
	char build[10];
	char spack[128];
	int returncode;
	DWORD platformId;
};

extern char *basename(char *fname);
extern char *strlwr(char *s);
extern void PrintUsage(const char *prog_name);
extern void PrintVersion(const char *prog_name);
extern void return_info(struct WindowsINFO *wininfo);
