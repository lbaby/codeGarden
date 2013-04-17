CFLAGS := $(CFLAGS) -g 
LDFLAGS := $(LDFLAGS) -g   -ly -ll
%.c:%.y
	yacc -d $<
	mv y.tab.c $@
	mv y.tab.h `echo $@ | sed 's/c$$/h/' `
%.l.c:%.l
	flex -t $< > $@

all: ch3-01
ch3-01:ch3-01.l.o ch3-01.o 
#ch2-03:ch2-03.l.o 

.SUFFIXES: .c .o .l.o 
.PHONY: all 
clean:
	rm -f *.c *.o ch3-01
