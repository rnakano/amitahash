OBJS = table.o bucket.o alloc.o
TESTS = test.o
MAIN = main.o

CFLAGS = -Wall -std=c99 -g
CPPFLAGS = -g
CC = gcc

main : $(OBJS) $(MAIN)
	gcc -o $@ -g -Wall $^ $(CFLAGS)

test : $(OBJS) $(TESTS)
	g++ -o $@ -lgtest -Wall $^

clean :
	rm -f *.o
