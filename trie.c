#include "trie.h"

void _printTrieNode(TrieNode* node, int depth) {
    if (node == NULL) return;

    for (int i = 0; i < depth - 1; i++) printf("\t");

    if (depth > 0) {
        printf("%c", node->data);
        if (node->completes_word) printf("($)");
        printf("\n");
    }

    for (int j = 0; j < 128; j++) {
        _printTrieNode(node->children[j], depth + 1);
    }
} 

void _rfree(TrieNode* node) {
    if (!node) return;
    
    for (int i = 0; i < 128; i++) {
        TrieNode* child = node->children[i];
        if (child) _rfree(child);
    }

    free(node);
}

void printTrie(Trie* trie) {
    _printTrieNode(trie->root, 0);
}

TrieNode* createTrieNode(char data, char completes_word) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->data = data;
    node->completes_word = completes_word;

    for (int i = 0; i < 128; i++) node->children[i] = NULL;

    return node;
}

Trie* createTrie() {
    TrieNode* root = createTrieNode('^', 0);
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = root;
    return trie;
}

int _insertChars(TrieNode* node, char* word, int i) {
    
    if (word[i] == '\0') {
        node->completes_word = 1;
        return 0;
    }

    TrieNode* next = node->children[word[i] - '0'];
    if (next == NULL) {    
        next = createTrieNode(word[i], 0); 
        node->children[word[i] - '0'] = next;
    }

    return _insertChars(next, word, i + 1);
}

int _searchChars(TrieNode* node, char* word, int i) {
    if (word[i] == '\0') 
        return node->completes_word;
    
    if ((node->children)[word[i] - '0'] == NULL) 
        return 0;
    else 
        return _searchChars((node->children)[word[i] - '0'], word, i + 1);
}

int _has_child(TrieNode* node) {
    for (int i = 0; i < 128; i++) {
        if (node->children[i] != NULL) return 1;
    }
    return 0;
}

TrieNode* _psearchChars(TrieNode* node, char* word, int i, TrieNode* stack[]) {
    if (stack)
        stack[i] = node;
    
    if (word[i] == '\0') 
        return node;

    if (node->children[word[i] - '0'] == NULL) 
        return NULL;
    else 
        return _psearchChars(node->children[word[i] - '0'], word, i + 1, stack);
}

int insertTrie(Trie* trie, char* words[], int num_words) {
    int error = 0;
    for (int i = 0; i < num_words; i++) {
        error = _insertChars(trie->root, words[i], 0);
        if (error > 0) {
            printf("Failed to insert word: %s\n", words[i]);
        }
    }

    return error;
}

int removeTrie(Trie* trie, char* key) {
    TrieNode* stack[128];

    for (int k = 0; k < 128; k++) stack[k] = NULL;

    TrieNode* node = _psearchChars(trie->root, key, 0, stack);
    int n = strlen(key);
    int i = n;

    while (i > 0) {
        node = stack[i];
        if (!_has_child(node)) {
            free(node);
            TrieNode* parent = stack[i - 1];
            parent->children[key[i - 1] - '0'] = NULL;
        } else {
            break;
        }
        i--;
    }

    if (i == n) {
        node->completes_word = 0;
    }

    return 0;
}

TrieNode* premoveTrie(Trie* trie, char* prefix) {
    TrieNode* stack[128];
    for (int i = 0; i < 128; i++) stack[i] = NULL;

    TrieNode* node = _psearchChars(trie->root, prefix, 0, stack);

    if (!node) {
        return NULL;
    } else {
        for (int j = 0; j < 128; j++) {
            _rfree(node->children[j]);
        }
    }

    int keylen = strlen(prefix);
    int k = keylen;

    while (k > 0) {
        node = stack[k];
        if (!_has_child(node) && node->completes_word == 0) {
            free(node);
            TrieNode* parent = stack[k - 1];
            parent->children[prefix[k - 1] - '0'] = NULL;
        } else {
            break;
        }
        k--;
    }

    return node;
}

char* searchTrie(Trie* trie, char* key) {
    if (_searchChars(trie->root, key, 0)) 
        return key;
    else 
        return NULL;
}

TrieNode* psearchTrie(Trie* trie, char* prefix) {
    TrieNode* matchedNode = _psearchChars(trie->root, prefix, 0, NULL);

    if (!matchedNode) 
        return NULL;
    else 
        return matchedNode;
}

char* rsearchTrie(Trie* trie, char* key) {
    return NULL;
}
