CC=clang
CPP=clang++
CFLAGS=-g -Wall

BIN=main

all: ${BIN}

# build:
# 	${CC} ${CFLAGS} main.c -o main -std=c17


%: %.c
	${CC} ${CFLAGS} $< -o $@

%: %.cpp
	${CPP} ${CFLAGS} $< -0 $@

# linked_list.o: linked_list.c
# 	${CC} ${CFLAGS} -c linked_list.c

run:
	${CC} ${CFLAGS} main.c -o main && ./main

clean:
	rm -f *.o ${BIN}
