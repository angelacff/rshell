[dkong008@hammer ~]$ cd rshell
[dkong008@hammer rshell]$ make
mkdir -p bin
g++  -ansi -pedantic -Wall -Werror src/cd.cpp -o bin/rshell
[dkong008@hammer rshell]$ bin/rshell
dkong008@hammer~/rshell $ cd
dkong008@hammer~ $ cd ..
dkong008@hammer/home/csmajs $ cd rshell
chdir: No such file or directory
dkong008@hammer/home/csmajs $ cd dkong008
dkong008@hammer~ $ cd rshell
dkong008@hammer~/rshell $ cd ..
dkong008@hammer~ $ cd -
dkong008@hammer~/rshell $ cd naedfada #annoted
chdir: No such file or directory
dkong008@hammer~/rshell $ cd - #annoted
dkong008@hammer~/rshell $ cd .. #fsdf
dkong008@hammer~ $ cd rsehll #dsfsf
chdir: No such file or directory
dkong008@hammer~ $ cd rsehll #dfsf
chdir: No such file or directory
dkong008@hammer~ $ cd rshell #fsdf
dkong008@hammer~/rshell $



