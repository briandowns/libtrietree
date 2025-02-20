#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_SIZE 26
#define MIN_CHAR 'a'

typedef struct node {
    struct node *children[MAX_SIZE];
    bool is_word_end;
} node_t;

node_t*
trie_new()
{
    node_t *root = (node_t*)calloc(1, sizeof(node_t));
    return root;
}

void
trie_free(node_t *node)
{
    if (node != NULL) {
        for (int i = 0; i < MAX_SIZE; i++) {
            if (node->children[i] != NULL) {
                trie_free(node->children[i]);
            }
        }
        free(node);
    }
}

int
insert(node_t *root, const char *key) {
    if (key == NULL || key[0] == '\0') {
        return -1;
    }
    
    node_t *current = root;

    for (int i = 0; i < strlen(key); i++) {
        int index = key[i]-MIN_CHAR;
        if (current->children[index] == NULL) {
            current->children[index] = trie_new();
        }
        current = current->children[index];
    }
    current->is_word_end = true;

    return 0;
}

bool
is_empty(node_t *root) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (root->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

static node_t*
_delete(node_t *root, const char *key, int depth) {
    if (root == NULL) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->is_word_end) {
            root->is_word_end = false;
        }
        if (is_empty(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = key[depth] - MIN_CHAR;
    root->children[index] = _delete(root->children[index], key, depth+1);

    if (is_empty(root) && !root->is_word_end) {
        free(root);
        root = NULL;
    }
    return root;
}

void
delete(node_t *root, const char *key) {
    _delete(root, key, 0);
}

bool
search(node_t *root, const char *key) {
    node_t *current = root;

    for (int i = 0; i < strlen(key); i++) {
        int index = key[i] - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
    }
    return current != NULL && current->is_word_end;
}

void
to_lower(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = tolower(s[i]);
    }
}

bool
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
main(int argc, char **argv)
{
    FILE *f = fopen("/usr/share/dict/words", "r");
    if (f == NULL) {
        printf("error:opening dictionary file!\n");
        return 1; 
    }

    node_t *root = trie_new();

    char word[100];
    while (fgets(word, 100, f) != NULL) {
        word[strcspn(word, "\r\n")] = 0;
        if (is_alpha_word(word) == false) {
            continue;
        }
        to_lower(word);
        printf("%s\n", word);
        insert(root, word);
    }

    fclose(f);

    printf("%s\n", search(root, "hello") ? "Found" : "Not Found");
    printf("%s\n", search(root, "world") ? "Found" : "Not Found");
    printf("%s\n", search(root, "geek") ? "Found" : "Not Found");

    trie_free(root);

    return 0;
}
