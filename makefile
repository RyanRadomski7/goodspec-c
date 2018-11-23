CC=clang
SYS=POSIX
LIBS=-ldl
DEBUG=-g
BIN=./pgs
FD=0
BS=4096

default:
	$(CC) -g -D$(SYS) -Wall -Werror --std=c89 $(LIBS) *.c -o $(BIN);
	$(BIN) $(FD) $(BS)
