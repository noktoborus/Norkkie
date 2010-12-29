CC=colorgcc
LIBS=`pkg-config --libs --cflags gl glu quesoglc` -lglut
CFLAGS=-g

BIN=./eee
SRC=src/main.c src/nurbs.c

.PHONY: all

all: ${BIN}
	${BIN}

${BIN}: ${SRC}
	${CC} -std=c99 -pedantic -Wall -Werror -o ${BIN} ${CFLAGS} ${SRC} ${LIBS}

