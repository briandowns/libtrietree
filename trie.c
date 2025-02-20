/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 Brian J. Downs
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define MIN_CHAR 'a'

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

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
        for (uint8_t i = 0; i < MAX_SIZE; i++) {
            if (node->children[i] != NULL) {
                trie_free(node->children[i]);
            }
        }
        free(node);
    }
}

int
trie_insert(node_t *root, const char *key) {
    if (key == NULL || key[0] == '\0') {
        return -1;
    }
    
    node_t *current = root;

    for (size_t i = 0; i < strlen(key); i++) {
        uint8_t index = key[i]-MIN_CHAR;
        if (current->children[index] == NULL) {
            current->children[index] = trie_new();
        }
        current = current->children[index];
    }
    current->is_word_end = true;

    return 0;
}

static bool
is_empty(node_t *root) {
    for (uint8_t i = 0; i < MAX_SIZE; i++) {
        if (root->children[i] != NULL) {
            return false;
        }
    }

    return true;
}

static node_t*
_delete(node_t *root, const char *key, size_t depth) {
    if (root == NULL) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->is_word_end) {
            root->is_word_end = false;
        }

        if (is_empty(root)) {
            trie_free(root);
            root = NULL;
        }

        return root;
    }

    uint8_t index = key[depth] - MIN_CHAR;
    root->children[index] = _delete(root->children[index], key, depth+1);

    if (is_empty(root) && !root->is_word_end) {
        trie_free(root);
        root = NULL;
    }

    return root;
}

void
trie_delete(node_t *root, const char *key) {
    _delete(root, key, 0);
}

bool
trie_search(node_t *root, const char *key) {
    node_t *current = root;

    for (size_t i = 0; i < strlen(key); i++) {
        uint8_t index = key[i] - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
    }

    return current != NULL && current->is_word_end;
}
