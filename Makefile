# name of executable
EXEC = program

# compiler to use
CC = clang

# command-line options to give to the compiler
# -std forces compiler to confirm you are only using features in that C standard
# -g generate source level debug information
# -Wall Warn all
# -I add directory to include in search path for headers
CFLAGS = -std=c99 -g -Wall -MMD


SRC = $(wildcard *.c)

OBJECTS = $(SRC:.c=.o)

DEPENDS = $(OBJECTS:.o=.d)

${EXEC}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${EXEC}

# copy the generated .d files which provides dependencies for each .c file
-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d ${EXEC}
