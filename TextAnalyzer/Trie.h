#include<string>
#include <vector>

using namespace std;

const int NUMBER_OF_LETTERS = 26;

struct TrieNode {
//A Node used to construct a Trie
    struct TrieNode* children[NUMBER_OF_LETTERS];
    int isWord;
    int amountOfEntries;
};

class Trie {
//Trie is a type of search tree, a tree data structure used for locating specific keys from within a set
public:
    Trie();
    Trie(vector<string> wordList);
    void AddWord(string s);
    int SearchWord(string s);
    int SearchPrefix(string s);
    int NumberOfLetters();
    int sentences;
    char MostProbableLetter(string s);
    string MostProbableWord(string s);
protected:
    int CountLetters(TrieNode* node);
    pair<string, int> MostProbableWordEnding(TrieNode* node);
private:
    TrieNode* root;
};
