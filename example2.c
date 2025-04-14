#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

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
    node_t *root = trie_new();

    char word[64] = {0};
    uint8_t idx = 0;

    while (1) {
        int c;
        int i = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            word[i++] = c; // Store the character
            word[i+2] = '\0';
            // word = (char *)realloc(word, (i + 1) * sizeof(char)); // Reallocate memory
            // if (str == NULL) {
            //     perror("Failed to reallocate memory");
            //     return 1; // Exit if memory reallocation fails
            // }
            printf("Options for %s\n", word);
            autocomplete(root, word);
        }
    }

    return 0;
}