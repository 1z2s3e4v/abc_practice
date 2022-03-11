TARGET	= ace
CC	= gcc
ABC	= ../abc

SRCS	= main.c ntk2cnf.c
OBJS	= ${SRCS:.c=.o}
LIB = -lm -ldl -lrt -rdynamic -lreadline -ltermcap -lpthread ${ABC}/libabc.a
INCLUDE = -I. -I${ABC}/src
CFLAGW  = -Wall -O3
CFLAGS  = -O3
${TARGET}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIB} ${LIBS} -o ${TARGET}

.SUFFIXES: .c .o

.c.o:
	${CC} ${CFLAGW} ${INCLUDE} -o $@ -c $<

clean:
	rm -f core *~ $(TARGET); \
	rm *.o
