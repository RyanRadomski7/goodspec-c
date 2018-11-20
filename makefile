CC=clang
SYS=POSIX
LIBS=-ldl
DEBUG=-g
BIN=./pgs

default:
	$(CC) -D$(SYS) -Wall -Werror --std=c89 $(LIBS) *.c -o $(BIN);
	$(BIN)
