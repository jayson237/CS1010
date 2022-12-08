.SILENT: test tidy
.PHONY: all clean compile test tidy

SHELL := /bin/bash
FILES=digits
CC=clang
LDLIBS=-lm -lcs1010
CFLAGS=@compile_flags.txt

all: compile test tidy

compile: $(FILES) 

test: $(FILES)
	./test.sh digits
	./test.sh digits 6 1
	./test.sh digits 100 30
	./test.sh digits 60000 30
	./test.sh digits 100 10000

tidy:
	clang-tidy -quiet *.c 2> /dev/null

clean:
	rm $(FILES)
# vim:noexpandtab
