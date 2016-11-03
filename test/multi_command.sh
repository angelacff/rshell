#tests commands with ;, && , or ||
angelacai@angelacai-Lenovo-Y50-70$ echo a;echo b
a
b
angelacai@angelacai-Lenovo-Y50-70$ echo a&&echo b
a
b
angelacai@angelacai-Lenovo-Y50-70$ echo a || echo b
a
angelacai@angelacai-Lenovo-Y50-70$ echo a ; echo b&& echo c
a
b
c
angelacai@angelacai-Lenovo-Y50-70$ echo a || echo b&& echo c
a
angelacai@angelacai-Lenovo-Y50-70$ echo a && echo b ||echo c
a
b
c
