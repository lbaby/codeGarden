
#complier configruation

#source file section
JSRC=$(wildcard *.java)
javac=javac
java=java

%.class:%.java
	$(javac) $^
	


.PHONY:all clean
CLASS=$(JSRC:%.java=%.class)

all:$(CLASS)

clean:
	rm -f *.class
	

