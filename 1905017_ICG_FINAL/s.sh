#!/bin/bash

yacc -d -y 1905017.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex Lexical.l
echo 'Generated the scanner C file'
g++ -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ y.o l.o -ll -o a
echo 'All ready, running'
#./a syntax_semantic_error.c
#./a no_error.c
./a test5_i.c