#!/bin/sh
BIN=./pep
OF=./test/pep.of
TF=./test/pep.ok
IF=./test/in

./pep >$OF
echo $PATH |sed 's/:/\n/g' > $TF
diff $OF $TF >/dev/null 2>&1
[ $? -eq 0 ]&&echo test PASSED || echo test FAIL
