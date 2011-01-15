CC=colorgcc -std=c99  -pedantic
LIBS=`pkg-config --libs --cflags gl glu quesoglc` -lglut
CFLAGS=-g

BIN=./eee
SRC=src/main.c src/nurbs.c src/msel_func*.c
SRCH=src/nurbs.h src/msel.h src/msel_func.h
.PHONY: all

all: ${BIN}
	${BIN}

${BIN}: ${SRC} ${SRCH}
	${CC} -Wall -Werror -o ${BIN} ${CFLAGS} ${SRC} ${LIBS}

