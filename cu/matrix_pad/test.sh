#!/bin/sh
BIN=./matrix_pad
OF=./test/matrix_pad.of
TF=./test/matrix_pad.ok
IF=./test/in

$BIN<$IF>$OF

diff $OF $TF >/dev/null 2>&1
[ $? -eq 0 ]&&echo test PASSED || echo test FAIL
