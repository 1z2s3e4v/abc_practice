TARGET	= main
CC	= g++
CG	= gcc
ABC	= ../abc

SRCS	= main.cpp
OBJS	= ${SRCS:.cpp=.o}
LIB = -lm -ldl -lreadline -lpthread ${ABC}/libabc.a
INCLUDE = -I. -I${ABC}/src
CFLAGW  = -Wall
CFLAGS  = -O3 -std=c++11
${TARGET}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIB} ${LIBS} -o ${TARGET}

.SUFFIXES: .c .o

.c.o:
	${CG} ${CFLAGW} ${INCLUDE} -o $@ -c $<
.cpp.o:
	${CC} ${CFLAGW} ${INCLUDE} -o $@ -c $<

clean:
	rm -f core *~ $(TARGET); \
	rm *.o
