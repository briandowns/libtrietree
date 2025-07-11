#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>

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

    // printf("dog: %s\n", trie_search(root, "dog") ? "Found" : "Not Found");
    // printf("cat: %s\n", trie_search(root, "cat") ? "Found" : "Not Found");
    // printf("blahblahblah: %s\n", trie_search(root, "blahblahblah") ? "Found" : "Not Found");

    // trie_delete(root, "cat");
    // printf("cat: %s\n", trie_search(root, "cat") ? "Found" : "Not Found");

    char prefix[MAX_WORD_LEN] = {0};
    int length = 0;
    int ch;
    while (1) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') {
            printf("\n");
            length = 0;
            prefix[0] = '\0';
            continue;
        }

        if (isalpha(ch) && length < MAX_WORD_LEN - 1) {
            prefix[length++] = tolower(ch);
            prefix[length] = '\0';

            printf("\nSuggestions for \"%s\":\n", prefix); 
            node_t *node = trie_get_node(root, prefix);
            if (node) {
                trie_search(node, prefix, length);
            } else {
                printf("No matches found.\n");
            }
            printf("\n");
        }
    }

    trie_free(root);

    return 0;
}
