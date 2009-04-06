#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "getopt.h"
#include "win32util.h"

int main (int argc, char *argv[]) 
{
  static struct option options[] = 
  {
     {"quiet",   no_argument,NULL,'q'},
     {"build",   no_argument,NULL,'b'},
     {"version", no_argument,NULL,'v'},
     {"help",    no_argument,NULL,'h'},
     {"spack",   no_argument,NULL,'s'},
     {"release", no_argument,NULL,'r'},
     {"all",     no_argument,NULL,'a'},
  };
  char opt;
  char *optstring = "qbvhsra";
  char *progname;
  struct WindowsINFO wininfo;

  /* Set defaults for arguments */
  int quiet = 0;
  int build = 0;
  int spack = 0;
  int release = 0;

  progname = basename(argv[0]);
  strlwr(progname);

  while ((opt=getopt_long(argc,argv,optstring,options,NULL)) != EOF ) {
     switch (opt) {

	case 'q':
	   quiet = 1;
	   break;

	case 'b':
	   build = 1;
	   break;

	case 's':
	   spack = 1;
	   break;

	case 'r':
	   release = 1;
	   break;

	case 'a':
	   build = 1;
	   spack = 1;
	   release = 1;
	   break;

        case 'v':
           PrintVersion(progname);
           return 8;

        case 'h':
           PrintUsage(progname);
           return 8;

        default:
           fprintf(stderr,"Try '%s --help' for more information.\n",progname);
           return 9;
     }
  }

  return_info(&wininfo);
  if(!quiet) {
    fprintf(stdout,"%s ",wininfo.winos);
    if(release) fprintf(stdout,"%s",wininfo.release);
    if(release && build) fprintf(stdout,".");
    if(build) fprintf(stdout,"%s",wininfo.build);
    if(build && wininfo.platformId == VER_PLATFORM_WIN32_WINDOWS) fprintf(stdout,"%s",wininfo.spack);
    if(build && spack && wininfo.platformId == VER_PLATFORM_WIN32_NT) fprintf(stdout," ");
    if(spack && wininfo.platformId == VER_PLATFORM_WIN32_NT) fprintf(stdout,"%s",wininfo.spack);
    fprintf(stdout,"\n");
  }
  return(wininfo.returncode);

}
