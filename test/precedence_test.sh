[dkong008@hammer rshell]$ bin/rshell
dkong008@hammer.cs.ucr.edu$ (echo a && echo b) || ( echo c && echo d)
a
b
dkong008@hammer.cs.ucr.edu$ (echo a )|| echo b
a
dkong008@hammer.cs.ucr.edu$ (echo c) || echo d
c
dkong008@hammer.cs.ucr.edu$
