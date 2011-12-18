
#source file section
SRC= pep.c

DEP=$(SRC:%.c=%.d)
LIB_A = $(SRC:%.c=lib%.a)
BIN=$(SRC:%.c=%)

all:$(BIN)
#complier configruation
CC=gcc
$(AR) = ar

#
CFLAGS += 
ARFLAGS = rsv


lib%.a:%.o
	$(AR)	$(ARFLAGS) $@ $<

#dependences 
%.d:%.c
	$(CC) -MM  $(CFLAGS) $^ \
	| sed s'/:/ $@:/' > $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEP)
endif

.PHONY:clean test

clean:
	rm -f $(BIN) *.o *.a *.d
test:all
	sh test.sh


