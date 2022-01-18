#include <iostream>
#include <vector>
#include "Trie.h"

using namespace std;

const int A_REGULAR = 'a';
const int Z_REGULAR = 'z';
const int A_CAPITAL = 'A';
const int Z_CAPITAL = 'Z';
const vector<char> SENTANCE_ENDING_SYMBOLS = { '.','!','?' };

int CharToTrieChildIndex(char c) {
    //Returns a value from 0 to 25, that determines the code of the given letter
    int index = c;
    if (A_REGULAR <= index && index <= Z_REGULAR) {
        return index - A_REGULAR;
    }
    if (A_CAPITAL <= index && index <= Z_CAPITAL) {
        return index - A_CAPITAL;
    }
    return -1;
}

char TrieChildIndexToChar(int x) {
    //Return the letter, by it's code
    char c = x + 97;
    return c;
}

struct TrieNode* MakeNode() {
    //Constructs an empty Trie Node
    struct TrieNode* newNode = new TrieNode;
    newNode->isWord = 0;
    newNode->amountOfEntries = 0;
    for (int i = 0;i < NUMBER_OF_LETTERS;i++) {
        newNode->children[i] = nullptr;
    }
    return newNode;
}

Trie::Trie() {
    //Basic constructor of Trie
    root = MakeNode();
    sentences = 0;
}

Trie::Trie(vector<string> wordList) {
    //Constructs a Trie from a given vector of words
    root = MakeNode();
    sentences = 0;
    for (int i = 0;i < wordList.size();i++) {
        AddWord(wordList[i]);
    }
}

void Trie::AddWord(string s) {
    //Adds a word into a trie
    for (int i = 0;i < SENTANCE_ENDING_SYMBOLS.size();i++) {
        if (s.size() == 0) { return; }
        if (s[s.size() - 1] == SENTANCE_ENDING_SYMBOLS[i]) {
            sentences++;
            s = s.substr(0, s.size() - 1);
        }
    }
    if (s.size() == 0) { return; }
    if (s[s.size() - 1] == ',') {
        s = s.substr(0, s.size() - 1);
    }
    if (s.size() == 0) { return; }
    struct TrieNode* current = root;
    for (int i = 0;i < s.size();i++) {
        int trieChildIndex = CharToTrieChildIndex(s[i]);
        if (trieChildIndex == -1) { return; }
        if (!current->children[trieChildIndex]) {
            current->children[trieChildIndex] = MakeNode();
        }
        current->amountOfEntries++;
        current = current->children[trieChildIndex];
    }
    current->isWord++;
}

int Trie::SearchWord(string s) {
    //Returns the amount the given word appers in the text
    struct TrieNode* current = root;
    for (int i = 0;i < s.size();i++) {
        int trieChildIndex = CharToTrieChildIndex(s[i]);
        if (!current->children[trieChildIndex]) {
            return 0;
        }
        current = current->children[trieChildIndex];
    }
    return current->isWord;
}

int Trie::SearchPrefix(string s) {
    //Returns the amount the prefix appears in the text
    struct TrieNode* current = root;
    for (int i = 0;i < s.size();i++) {
        int trieChildIndex = CharToTrieChildIndex(s[i]);
        if (!current->children[trieChildIndex]) {
            return 0;
        }
        current = current->children[trieChildIndex];
    }
    return current->amountOfEntries;
}

int Trie::CountLetters(TrieNode* node) {
    //Recursive function, used for counting the number of letters in the Trie
    if (node == NULL) { return 0; }
    int amountOfLetters = node->amountOfEntries;
    for (int i = 0;i < NUMBER_OF_LETTERS;i++) {
        amountOfLetters += CountLetters(node->children[i]);
    }
    return amountOfLetters;
}

int Trie::NumberOfLetters() {
    //Returns the number of letters in the Trie
    return CountLetters(root);
}

char Trie::MostProbableLetter(string s) {
    //Based on the data in the Trie returns the letter that is most probable to appear after the given letter combination
    struct TrieNode* current = root;
    for (int i = 0;i < s.size();i++) {
        int trieChildIndex = CharToTrieChildIndex(s[i]);
        if (!current->children[trieChildIndex]) {
            cout << "No word in the text has the following letter combination: " << s << endl;
            return ' ';
        }
        current = current->children[trieChildIndex];
    }
    char mostProbableLetter = '0';
    int timesUsed = 0;
    for (int i = 0;i < NUMBER_OF_LETTERS;i++) {
        if (current->children[i] != NULL) {
            if (current->children[i]->amountOfEntries > timesUsed) {
                timesUsed = current->children[i]->amountOfEntries;
                mostProbableLetter = TrieChildIndexToChar(i);
            }
        }
    }
    return mostProbableLetter;
}

string Trie::MostProbableWord(string s) {
    //Returns the most used word with the given prefix
    struct TrieNode* current = root;
    for (int i = 0;i < s.size();i++) {
        int trieChildIndex = CharToTrieChildIndex(s[i]);
        if (!current->children[trieChildIndex]) {
            cout << "No word in the text has the following letter combination: " << s << endl;
            return "";
        }
        current = current->children[trieChildIndex];
    }
    string mostProbableWord = s + MostProbableWordEnding(current).first;
    return mostProbableWord;
}

pair<string, int> Trie::MostProbableWordEnding(TrieNode* node) {
    //Recursive method, used for obtaining the most probable ending after a given prefix
    int wordCount = node->isWord;
    string mostProbableWordEnding = "";
    for (int i = 0;i < NUMBER_OF_LETTERS;i++) {
        if (node->children[i] != NULL) {
            if (MostProbableWordEnding(node->children[i]).second > wordCount) {
                wordCount = MostProbableWordEnding(node->children[i]).second;
                mostProbableWordEnding = TrieChildIndexToChar(i) + MostProbableWordEnding(node->children[i]).first;
            }
        }
    }
    return { mostProbableWordEnding, wordCount };
}