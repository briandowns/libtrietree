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

 #ifdef __cplusplus
extern "C" {
#endif

#ifndef __TRIE_H
#define __TRIE_H

#include <stdbool.h>

#define MAX_SIZE 26

/**
 * node represents the Trie tree.
 */
typedef struct node {
    struct node *children[MAX_SIZE];
    bool is_word_end;
} node_t;

/**
 * creates a new tree initialized to 0.
 */
node_t*
trie_new();

/**
 * frees the memory used by the tree.
 */
void
trie_free(node_t *node);

/**
 * insert inserts a new key into the tree. Returns 0 on success and -1
 * on failure.
 */
int
trie_insert(node_t *root, const char *key);

/**
 * delete deletes a key from the tree.
 */
void
trie_delete(node_t *root, const char *key);

/**
 * search searches the tree for the given key and returns true if found 
 * or false if it's not.
 */
bool
trie_search(node_t *root, const char *key);

#endif /** end __TRIE_H */
#ifdef __cplusplus
}
#endif
