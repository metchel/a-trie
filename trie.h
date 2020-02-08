#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 128

typedef struct Trie {
    struct TrieNode* root;
} Trie;

typedef struct TrieNode {
    char data;
    struct TrieNode* children[N];
    char completes_word;
} TrieNode;

/** 
 * Build a Trie from a bag of words of size num_words.
 **/
struct Trie* createTrie();

/**
 * Search for a key in the Trie. Returns NULL if not found.
 **/
char* searchTrie(Trie* trie, char* key);

/**
 * Search the Trie for a regex pattern. Returns NULL if not found.
 **/
char* rsearchTrie(Trie* trie, char* rkey);

/**
 * Search the Trie for a prefix. Returns NULL if not found.
 **/
TrieNode* psearchTrie(Trie* trie, char* prefix);

/**
 * Add word(s) to the already built Trie.
 **/
int insertTrie(Trie* trie, char* words[], int num_words);

/**
 * Remove a word(s) from the Trie.
 **/
int removeTrie(Trie* trie, char* word);

/**
 * Remove all nodes from the Trie for some prefix. Also remove parent nodes if they do not complete words.
 **/
TrieNode* premoveTrie(Trie* trie, char* prefix);
