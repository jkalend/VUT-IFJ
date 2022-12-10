CFLAGS:= -O0

default: parser

parser: parser.o stack.o  symtable.o scanner.o generator.o
	$(CC) $(CFLAGS) -o parser stack.o scanner.o parser.o symtable.o  generator.o -lm
clean:
	rm -f *.o parser
pack: clean
	zip xkalen07.zip parser.* scanner.* stack.* symtable.* generator.* error.h dokumentace.pdf  Makefile rozdeleni rozsireni

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
