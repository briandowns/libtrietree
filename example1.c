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

void
possibles(const node_t *node, char *prefix, const uint8_t length)
{
    if (node->is_word_end) {
        prefix[length] = '\0';
        printf("%s\n", prefix);
    }

    for (uint8_t i = 0; i < MAX_SIZE; i++) {
        if (node->children[i]) {
            prefix[length] = i + 'a';

            possibles(node->children[i], prefix, length + 1);
        }
    }
}

int
autocomplete(node_t *root, const char *prefix)
{
    node_t *node = root;

    uint16_t level = 0;

    size_t prefix_len = strlen(prefix);
    char partial[prefix_len + 1];
    strcpy(partial, prefix);

    for (level = 0; level < prefix_len; level++) {
        uint8_t index = prefix[level] - 'a';

        if (!node->children[index]) {
            return 0;
        }
        node = node->children[index];
    }

    bool is_word = node->is_word_end == true;
    bool is_last = false;

    for (uint8_t i = 0; i < MAX_SIZE; i++) {
        if (node->children[i]) {
            is_last = true;
            break;
        }
    }

    if (!is_last && is_word) {
        printf("%s\n", prefix);
        return -1;
    }

    if (node != NULL) {
        possibles(node, partial, level);
        return 1;
    }

    return 0;
}

int
main(void)
{
    FILE *f = fopen("/usr/share/dict/words", "r");
    if (f == NULL) {
        printf("error: opening dictionary file!\n");
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

    printf("\nAutocomplete suggestions for 'burn':\n");
    autocomplete(root, "burn");

    printf("\nAutocomplete suggestions for 'carn':\n");
    autocomplete(root, "carn");

    printf("\nAutocomplete suggestions for 'appl':\n");
    autocomplete(root, "appl");

    printf("\nAutocomplete suggestions for 'xyz':\n");
    if (autocomplete(root, "xyz") == 0){
        printf("no strings with prefix.\n");
    }

    trie_free(root);

    return 0;
}
