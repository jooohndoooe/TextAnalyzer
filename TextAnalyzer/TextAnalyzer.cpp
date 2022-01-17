#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

Trie T;

void ReadInput() {
    //Reads data from "input.txt" and puts it in a Trie
    fstream input;
    input.open("input.txt", ios::in);
    string s;
    while (input >> s) {
        T.AddWord(s);
    }
    input.close();
}

void WriteReport() {
    //Output data about sentences, words and letters in the given text
    cout << "Text contains " << T.sentences << " sentences, " << T.SearchPrefix("") << " words, " << T.NumberOfLetters() << " letters." << endl;
}

bool AnalysisLoop() {
    //Console dialog to determine what data to output
    cout << endl;
    cout << "Do you want to continue? (y/n)" << endl;
    string s;
    cin >> s;
    if (s[0] == 'n' || s[0] == 'N') {
        return false;
    }    
    cout << "For the most probable word with a given prefix print 'w'" << endl;
    cout << "For the most probable letter after a given prefix print 'l'" << endl;
    cout << "For the amount of words with the given prefix print 'a'" << endl;
    cout << "For the exact amount the word appears in the text print 'e'" << endl;
    cin >> s;
    if (s[0] == 'w' || s[0] == 'W') {
        cout << "Enter prefix of a word" << endl;
        cin >> s;
        s = T.MostProbableWord(s);
        if (s != "") {
            cout << "Most probable word with the given prefix: " << s << endl;
        }
    } else if (s[0] == 'l' || s[0] == 'L') {
        cout << "Enter prefix of a word" << endl;
        cin >> s;
        char c = T.MostProbableLetter(s);
        if (c != ' ') {
            cout << "Most probable letter after the given prefix: " << c << endl;
        }
    } else if (s[0] == 'a' || s[0] == 'A') {
        cout << "Enter prefix of a word" << endl;
        cin >> s;
        int amountOfWordsWithTheGivenPrefix = T.SearchPrefix(s);
        cout << "Amount of words with the given prefix: " << amountOfWordsWithTheGivenPrefix << endl;
    } else if (s[0] == 'e' || s[0] == 'E') {
        cout << "Enter the word" << endl;
        cin >> s;
        int amountOfGivenWords = T.SearchWord(s);
        cout << "Amount of the given words: " << amountOfGivenWords << endl;
    } else {
        cout << "Invalid input" << endl;
    }
}

int main()
{
    ReadInput();
    WriteReport();
    while (AnalysisLoop());
}