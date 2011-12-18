#!/bin/sh
#A test script for maxlen
#
function top10()
{
	#print  10  largest length  strings
	#in reverse length order 
	#if two lines are the same in length then print first line of input
	#output format :
	#length:line_number:content
	awk '{print length()":"NR":"$0 }'|sort  -r  -n -u -t : -k 1,1 | head -10

}

BIN=./maxlen_hash
OF=./test/maxlen_hash.of
TF=./test/maxlen_hash.ok
IF=./test/in
RBIN=./randch

#generate a random file
# and split the line larger than 2048 bytes 
$RBIN| sed 's/^\(.\{2048\}\).*$/\1\n/g' > $IF

cat $IF|top10 > $TF
$BIN <$IF>$OF

[ -f $OF ] && diff $OF $TF >/dev/null 2>&1
[ $?  -eq 0 ] && echo test PASSED || echo test FAIL
