
# My first makefile
 
all: exe
 
exe: main.o select.o sort.o table_player.o table_rating.o table_tags.o trie.o
	gcc -o exe main.o sort.o select.o table_player.o table_rating.o table_tags.o trie.o

main.o: main.c functions.h
	gcc -o main.o main.c -c

sort.o: sort.c functions.h
	gcc -o sort.o sort.c -c

select.o: select.c functions.h
	gcc -o select.o select.c -c

table_player.o: table_player.c functions.h
	gcc -o table_player.o table_player.c -c

table_rating.o: table_rating.c functions.h
	gcc -o table_rating.o table_rating.c -c

table_tags.o: table_tags.c functions.h
	gcc -o table_tags.o table_tags.c -c

trie.o: trie.c functions.h
	gcc -o trie.o trie.c -c

clean:
	rm -rf *.o *~ exe