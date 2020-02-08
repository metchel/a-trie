#include <string.h>
#include <assert.h>

#include "trie.c"

Trie* trie;

void before() {
    trie = createTrie();
    assert(trie != NULL);

    char* words[] = { "apple", "apparatus", "appliance", "application", "banana", "banter", "bananza", "cranberry", "cranium", "crane" };
    int success = insertTrie(trie, words, 10);
    assert(success == 0);
}

void test_searchTrie() {
    char* match_ok = searchTrie(trie, "apple");
    char* match_not_found = searchTrie(trie, "cheese");

    assert(match_ok != NULL);
    assert(strcmp(match_ok, "apple") == 0);
    assert(match_not_found == NULL);
}

void test_rsearchTrie() {
}

void test_psearchTrie() {
    TrieNode* matched = psearchTrie(trie, "ban");
    assert(matched);
}

void test_premoveTrie() {
    TrieNode* removed = premoveTrie(trie, "app");
    assert(removed);
    assert(searchTrie(trie, "apple") == NULL);
    assert(searchTrie(trie, "application") == NULL);
    assert(psearchTrie(trie, "app") == NULL);
}

void test_removeTrie() {
    removeTrie(trie, "CGAGCA");
}

int main() {
    before();
    test_searchTrie();
    test_rsearchTrie();
    test_removeTrie();
}
