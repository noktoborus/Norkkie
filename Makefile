CC=colorgcc -std=c99  -pedantic -Wall
LIBS=`pkg-config --libs --cflags gl glu quesoglc` -lglut
CFLAGS=-g

BUILD_d=./build
OBJ_d=${BUILD_d}/obj
BIN_d=${BUILD_d}/bin
SRC_d=./src

BIN=${BIN_d}/norkkie

OBJ=${OBJ_d}/main.o\
	${OBJ_d}/input.o\
	${OBJ_d}/msel_func.o\
	${OBJ_d}/msel_func_model.o\
	${OBJ_d}/msel_func_root.o\
	${OBJ_d}/nurbs.o

SRC=${SRC_d}/main.c\
	${SRC_d}/input.c\
	${SRC_d}/msel_func.c\
	${SRC_d}/msel_func_mode.c\
	${SRC_d}/msel_func_root.c\
	${SRC_d}/nurbs.c

.PHONY: all

all: ${BIN}
	${BIN}

clean:
	rm -rf ${BUILD_d}

g:
	gdb ${BIN}

c:
	gdb ${BIN} core

${BIN}: ${OBJ_d} ${BIN_d} ${OBJ}
	${CC} -o $@ ${LIBS} ${OBJ}

${OBJ_d}/%.o: ${SRC_d}/%.c
	${CC} -o $@ ${CFLAGS} -c $<

${BIN_d}:
	mkdir -p ${BIN_d}

${OBJ_d}:
	mkdir -p ${OBJ_d}

