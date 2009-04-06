/*
 * win32ver
 * Copyright (C) 1999 BingosNET Produktions Ltd
 * Written by Kidney Bingos aka Chris Williams
 * <chris@kidney-bingos.demon.co.uk> 
 * With some components borrowed from the Free Software Foundation
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <windows.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include "win32util.h"
#include "version.h"
#include "tailor.h"

/* ========================================================================
 * Return the base name of a file (remove any directory prefix and
 * any version suffix). For systems with file names that are not
 * case sensitive, force the base name to lower case.
 */
char *basename(fname)
    char *fname;
{
    char *p;

    if ((p = strrchr(fname, PATH_SEP))  != NULL) fname = p+1;
#ifdef PATH_SEP2
    if ((p = strrchr(fname, PATH_SEP2)) != NULL) fname = p+1;
#endif
#ifdef PATH_SEP3
    if ((p = strrchr(fname, PATH_SEP3)) != NULL) fname = p+1;
#endif
#ifdef SUFFIX_SEP
    if ((p = strrchr(fname, SUFFIX_SEP)) != NULL) *p = '\0';
#endif
    if (casemap('A') == 'a') strlwr(fname);
    return fname;
}

/* ========================================================================
 * Put string s in lower case, return s.
 */
char *strlwr(s)
    char *s;
{
    char *t;
    for (t = s; *t; t++) *t = tolow(*t);
    return s;
}

void PrintUsage(const char *prog_name)
{
	printf("Usage: %s [OPTIONS]\n",prog_name);
	printf("\n");
	printf("-q, --quiet	only return errorlevel\n");
	printf("-b, --build	return the build number of the OS\n");
	printf("-v, --version	show version information for %s\n",prog_name);
	printf("-h, --help	show this help message\n");
	printf("-s, --spack	return the Service Pack information\n");
	printf("-r, --release	return the Major and Minor release numbers\n");
	printf("-a, --all	display all available information\n");
	printf("\nBug reports to %s-bugs@kidney-bingos.demon.co.uk\n",prog_name); 
}

void PrintVersion(const char *prog_name)
{
	printf("%s\n\n", prog_name);
	printf("version:                    %s\n",VERSION);
	printf("compile date:               %s %s\n",__DATE__,__TIME__);
#if defined __GNUC__
	printf("compiler:                   %s %s\n",COMPILER,__VERSION__);
#else
	printf("compiler:                   %s\n",COMPILER);
#endif
	printf("environment:                %s\n",BUILD_ENV);
	printf("author:                     Kidney Bingos (chris@bingosnet.co.uk)\n");
}

void return_info(struct WindowsINFO *wininfo)
{
  OSVERSIONINFO osvi;
  char *sp;

  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if (GetVersionEx(&osvi)) {
    wininfo->platformId = osvi.dwPlatformId;
    switch(osvi.dwPlatformId) {
      case VER_PLATFORM_WIN32_WINDOWS:
	wininfo->returncode = RET_WINDOWS;
        switch (osvi.dwMinorVersion) {
          case 10:
            sprintf(wininfo->winos,"Windows98"); break;
          case 90:
            sprintf(wininfo->winos,"WindowsME"); break;
          default:
            sprintf(wininfo->winos,"Windows95"); break;
        }
        break;
      case VER_PLATFORM_WIN32_NT:
        if (osvi.dwMajorVersion < 5) {
	  wininfo->returncode = RET_WINDOWSNT;
          sprintf(wininfo->winos,"WindowsNT");
        } else {
	  switch (osvi.dwMinorVersion) {
  	    case 1:
	      wininfo->returncode = RET_WINDOWSXP;
	      sprintf(wininfo->winos,"WindowsXP");
	      break;
	    case 2:
	      wininfo->returncode = RET_WINDOWS2K3;
              sprintf(wininfo->winos,"Windows2003");
	      break;
	    default:
	      wininfo->returncode = RET_WINDOWS2K;
              sprintf(wininfo->winos,"Windows2000");
          }
        }
        break;
      default:
	wininfo->returncode = RET_UNKNOWN;
        sprintf(wininfo->winos,"Unknown"); break;
    }
    sprintf(wininfo->release,"%li.%02li",osvi.dwMajorVersion,osvi.dwMinorVersion);
    sprintf(wininfo->build,"%ld",osvi.dwPlatformId == VER_PLATFORM_WIN32_NT ? osvi.dwBuildNumber : (osvi.dwBuildNumber & 0xffff));
    sp = strtok(osvi.szCSDVersion, " ");
    sprintf(wininfo->spack,"%s",sp);
    do {
      sp = strtok('\0', " ");
      if(sp) strcat(wininfo->spack, sp);
    } while(sp);
  } else {
    exit(9);
  }
}
