all: clean
	cc -g -Wall -O3 -o trie main.c 

.PHONY: clean
clean:
	rm -f trie
