CC=cc -g -std=c99  -pedantic -Wall
LIBS=`pkg-config --libs --cflags gl glu quesoglc` -lglut
CFLAGS=

BUILD_d=./build
OBJ_d=${BUILD_d}/obj
BIN_d=${BUILD_d}/bin
SRC_d=./src

CINCLUDE=-I${SRC_d}/lib

BIN=${BIN_d}/norkkie

OBJ=${OBJ_d}/norkkie_main.o\
	${OBJ_d}/msel.o\
	${OBJ_d}/input.o\
	${OBJ_d}/msel_func.o\
	${OBJ_d}/msel_func_model.o\
	${OBJ_d}/msel_func_root.o\
	${OBJ_d}/norkkie_nurbs.o\
	${OBJ_d}/norkkie_pack_tools.o

test_nurbs_OBJ=${OBJ_d}/test_nurbs_main.o\
			   ${OBJ_d}/norkkie_nurbs.o
.PHONY: all

#all: ${BIN_d}/norkkie ${BIN_d}/test_nurbs
all: ${BIN_d}/test_nurbs

clean:
	rm -rf ${BUILD_d}

${BIN_d}/norkkie: ${OBJ_d} ${BIN_d} ${OBJ}
	@printf "  LD\t$@\n"
	@${CC} -o $@ ${LIBS} ${OBJ}

${BIN_d}/test_nurbs: ${OBJ_d} ${BIN_d} ${test_nurbs_OBJ}
	@printf "  LD\t$@\n"
	@${CC} -o $@ ${LIBS} ${test_nurbs_OBJ}

${OBJ_d}/test_nurbs_main.o: ${SRC_d}/test/nurbs/main.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} ${CINCLUDE} -c $<

${OBJ_d}/norkkie_main.o: ${SRC_d}/main/main.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} ${CINCLUDE} -c $<

${OBJ_d}/msel.o: ${SRC_d}/main/msel.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<

${OBJ_d}/input.o: ${SRC_d}/main/input.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<

${OBJ_d}/msel_func.o: ${SRC_d}/main/msel_func.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<


${OBJ_d}/msel_func_root.o: ${SRC_d}/main/msel_func_root.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<

${OBJ_d}/msel_func_model.o: ${SRC_d}/main/msel_func_model.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<

${OBJ_d}/norkkie_pack_tools.o: ${SRC_d}/lib/norkkie/src/pack_tools.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<

${OBJ_d}/norkkie_nurbs.o: ${SRC_d}/lib/norkkie/src/nurbs.c
	@printf "  CC\t$<\n"
	@${CC} -o $@ ${CFLAGS} -c ${CINCLUDE} $<

${BIN_d}:
	mkdir -p ${BIN_d}

${OBJ_d}:
	mkdir -p ${OBJ_d}

