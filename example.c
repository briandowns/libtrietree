#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "trie.h"

#define MAX_WORD_LEN 100

static void
to_lower(char *s) {
    for (uint8_t i = 0; s[i] != '\0'; i++) {
        s[i] = tolower(s[i]);
    }
}

static bool
is_alpha_word(const char *word)
{
    for (uint8_t i = 0; i < strlen(word); i++) {
        if (!isalpha(word[i])) {
            return false;
        }
    }

    return true;
}

int
main(void)
{
    FILE *f = fopen("/usr/share/dict/words", "r");
    if (f == NULL) {
        printf("error:opening dictionary file!\n");
        return 1; 
    }

    node_t *root = trie_new();

    char word[100];
    while (fgets(word, MAX_WORD_LEN, f) != NULL) {
        word[strcspn(word, "\r\n")] = 0;
        if (is_alpha_word(word) == false) {
            continue;
        }
        to_lower(word);
        trie_insert(root, word);
    }

    fclose(f);

    printf("dog: %s\n", trie_search(root, "dog") ? "Found" : "Not Found");
    printf("cat: %s\n", trie_search(root, "cat") ? "Found" : "Not Found");
    printf("blahblahblah: %s\n", trie_search(root, "blahblahblah") ? "Found" : "Not Found");

    trie_delete(root, "cat");
    printf("cat: %s\n", trie_search(root, "cat") ? "Found" : "Not Found");

    trie_free(root);

    return 0;
}
