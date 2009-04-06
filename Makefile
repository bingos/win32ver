# Mingw32 - Minimalist GNU C Compiler (using DMAKE)
CC = gcc
DEFS = -DWIN32
CFLAGS = -O3 -Wall
#LINKOPTS = -lwsock32

# Cygwin32 - Cygnus GNU C Compiler for Win32
# CC = gcc
# DEFS = -DWIN32
# CFLAGS = -O3 -Wall -ansi -pedantic
# This is optional but you can specify this flag to compile native Win32 code
# EXTRAS = -mno-cygwin

# NCR SVR4 MP-RAS using the NCR High Performance C Compiler
# CC = cc
# CFLAGS = -O3

# Data General DG/UX on Intel and M88K
# CC = gcc
# DEFS = -DDGUX
# CFLAGS = -O3 -Wall -ansi -pedantic

# The following should work for UNIX-like operating systems
# with GNU C Compiler
#CC = gcc
#CFLAGS = -O3 -Wall

# And for the rest give this a good
# CC = cc


# For those with a suitable UNIX rm
RM = rm
RMFLAGS = -f
# Else on Windows NT4
# RM = cmd /c del
# RMFLAGS = /F /Q
################################################################################################
################################################################################################

OBJS = win32ver.o win32util.o getopt.o getopt1.o
WASTE = *.exe *.o

all: win32ver

%.o: %.c
	${CC} ${DEFS} ${CFLAGS} -c $< -o $@ ${EXTRAS}

win32ver:	${OBJS}
	${CC} ${DEFS} ${CFLAGS} -o win32ver ${OBJS} ${EXTRAS} ${LINKOPTS}

clean:
	${RM} ${RMFLAGS} ${WASTE}

