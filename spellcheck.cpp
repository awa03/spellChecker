#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "hashtable.h"
#include "ftxui/include/ftxui/dom/elements.hpp"
#include "ftxui/include/ftxui/screen/screen.hpp"
#include "ftxui/include/ftxui/component/component.hpp"
#include "ftxui/include/ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/include/ftxui/component/component_options.hpp"
#include "ftxui/include/ftxui/component/screen_interactive.hpp"
#include "ftxui/include/ftxui/dom/elements.hpp"

using namespace std;
using namespace ftxui;

void menu()
{
    cout << "\n\n";
    cout << "l - Load Dictionary From File" << endl;
    cout << "a - Add Word" << endl;
    cout << "r - Remove Word" << endl;
    cout << "c - Clear HashTable" << endl;
    cout << "f - Find Word" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

void myspell()
{
    int size;
    cout << "Enter Desired Size of HashTable: " << endl;
    cin >> size;

    cop4530::HashTable<string> myHashTable(size);
    char choice;
    string word;
    while (1)
    {
        menu();
        cin >> choice;
        switch (choice)
        {
        case 'l':
            cout << "Enter name of file to load from: ";
            cin >> word;
            if (myHashTable.load(word.c_str()))
                cout << "Loaded " << word << endl;
            else
                cout << "Unable to load " << word << endl;
            break;
        case 'a':
            cout << "Enter word to add: ";
            cin >> word;
            if (myHashTable.insert(word))
            {
                cout << "Added " << word;
                cout << " To HashTable" << endl;
            }
            else
            {
                cout << "Unable to add " << word << endl;
            }
            break;
        case 'r':
            cout << "Enter word to remove: ";
            cin >> word;
            if (myHashTable.remove(word))
                cout << "Removed " << word << endl;
            else
                cout << "Unable to remove " << word << endl;
            break;
        case 'c':
            myHashTable.clear();
            break;
        case 'f':
            cout << "Enter word to find: ";
            cin >> word;
            if (myHashTable.contains(word))
                cout << "Found " << word << endl;
            else
                cout << word << " not found" << endl;
            break;
        case 'd':
            myHashTable.dump();
            break;
        case 's':
            cout << "Size of HashTable is " << endl;
            cout << myHashTable.size() << endl;
            break;
        case 'w':
            cout << "Enter name of file to write to: ";
            cin >> word;
            myHashTable.write_to_file(word.c_str());
            break;
        case 'x':
            exit(0);
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}

void displayWordCapitalized(string target, vector<string> fileContents)
{
    using namespace ftxui;

    // Modify file contents so the target is all caps.
    bool found = false;
    std::string temp;
    for (std::string &words : fileContents)
    {
        if (found)
        {
            break;
        }
        if (target == words && !found)
        {
            for (char &c : words)
            {
                c = toupper(c);
                temp += c;
            }
            words = temp;
            found = true;
        }
        else
        {
            temp.clear();
        }
    }

    // Create header.
    Element header = text("File Fixer") | bold | size(WIDTH, EQUAL, 10);

    // Create a vector of Text elements, one for each line.
    std::vector<Element> textElements;
    std::string line;
    for (const auto &words : fileContents)
    {
        if (words == "\n")
        {
            if (!line.empty())
            {
                textElements.push_back(text(line));
                line.clear();
            }
        }
        else
        {
            line += words + " ";
        }
    }
    if (!line.empty())
    {
        textElements.push_back(text(line));
    }

    // Misspelled word information.
    std::string misspelledWord = target;

    // Create a blue box containing the header, text elements, and misspelled word information.
    Element box = vbox({
        header | border | flex | bold,
        vbox(textElements) | border | flex,
        text("\nThe word " + misspelledWord + " is misspelled.") | border | flex,
    }) | flex | border;

    // Create a Screen and render the box.
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(box));
    Render(screen, box);
    screen.Print();
}

string displayOptions(vector<string> &similarWords, string word, vector<pair<string, int>> &wordRanks)
{
    int length = similarWords.size();

    // Separate words into found and not found based on wordRank
    vector<string> foundWords;
    vector<string> notFoundWords;
    // Assuming wordRanks is a vector of pairs where the first element of the pair is the word and the second element is the rank
    map<string, int> wordRankMap;
    for (const auto &pair : wordRanks)
    {
        wordRankMap[pair.first] = pair.second;
    }

    for (int i = 0; i < length; i++)
    {
        if (wordRankMap.count(similarWords[i]) > 0)
        {
            foundWords.push_back(similarWords[i]);
        }
        else
        {
            notFoundWords.push_back(similarWords[i]);
        }
    }

    // Manually sort foundWords based on the ranks in wordRankMap using selection sort
    for (int i = 0; i < foundWords.size(); i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < foundWords.size(); j++)
        {
            if (wordRankMap[foundWords[j]] < wordRankMap[foundWords[minIndex]])
            {
                minIndex = j;
            }
        }
        // Swap foundWords[i] and foundWords[minIndex]
        string temp = foundWords[i];
        foundWords[i] = foundWords[minIndex];
        foundWords[minIndex] = temp;
    }

    // Display found words first, limit to 9
    int foundCount = 0;
    for (const string &foundWord : foundWords)
    {
        if (foundCount < 9)
        {
            foundCount++;
        }
        else
        {
            break; // Limit reached
        }
    }

    // If we haven't reached 9, display not found words
    if (foundCount < 9)
    {
        for (const string &notFoundWord : notFoundWords)
        {
            if (foundCount < 9)
            {
                foundCount++;
            }
            else
            {
                break; // Limit reached
            }
        }
    }

    // set similar words to combo of found and not found
    similarWords.clear();
    int addedWords;
    for (const string &foundWord : foundWords)
    {
        if (addedWords < 9)
        {
            similarWords.push_back(foundWord);
            addedWords++;
        }
        else
        {
            break;
        }
    }
    // Add not found words to the end
    for (const string &notFoundWord : notFoundWords)
    {
        if (addedWords < 9)
        {
            similarWords.push_back(notFoundWord);
            addedWords++;
        }
        else
        {
            break;
        }
    }

    int selected = 0;
    auto screen = ScreenInteractive::TerminalOutput();
    MenuOption option;

    option.on_enter = screen.ExitLoopClosure();
    similarWords.push_back(word); // Add the original word to the end of the list
    auto menu = Menu(&similarWords, &selected, option) | border | flex;
    screen.Loop(menu);

    cout << similarWords[selected] << " was chosen." << endl;
    system("clear");

    return similarWords[selected];
}

vector<string> SimilarWords(cop4530::HashTable<string>& dictionary, string word)
{

    // Create a vector to hold the similar words
    int length = word.length();
    vector<string> similarWords;

    // Create a string to hold the word
    string tempWord = word;

    // Loop through the word
    for (int i = 0; i < length; i++)
    {

        // Character substitution
        for (char j = 'a'; j <= 'z'; j++)
        {
            tempWord = word;
            tempWord[i] = j;
            if (dictionary.contains(tempWord))
            {
                similarWords.push_back(tempWord);
            }
        }

        // Character deletion
        tempWord = word.substr(0, i) + word.substr(i + 1);
        if (dictionary.contains(tempWord))
        {
            similarWords.push_back(tempWord);
        }

        // Character insertion
        for (char j = 'a'; j <= 'z'; j++)
        {
            tempWord = word.substr(0, i) + j + word.substr(i);
            if (dictionary.contains(tempWord))
            {
                similarWords.push_back(tempWord);
            }
        }
    }
    // Character swapping
    for (int i = 0; i < length - 1; i++)
    {
        tempWord = word;
        swap(tempWord[i], tempWord[i + 1]);
        if (dictionary.contains(tempWord))
        {
            similarWords.push_back(tempWord);
        }
    }
    return similarWords;
}

// Recursive implementation of fixWords
void fixWords(cop4530::HashTable<string> &dictionary, ifstream &inFile, ofstream &outFile, vector<string> &fileContents, vector<pair<string, int>> &wordRanks)
{

    system("clear");
    string word;

    // Base case
    if (!(inFile >> word))
    {
        return;
    }

    // Convert the word to lowercase and remove punctuation except for '-'
    std::string fixedWord;
    for (char c : word)
    {
        if (c == '-')
        {
            fixedWord += c;
        }
        else if (isalnum(c))
        {
            fixedWord += tolower(c);
        }
    }
    // Preserve original casing for the output
    std::string originalWord = word;

    // Recursive case
    if (!dictionary.contains(fixedWord))
    {
        displayWordCapitalized(originalWord, fileContents);
        vector<string> similarWords = SimilarWords(dictionary, fixedWord);
        string userChoice = displayOptions(similarWords, originalWord, wordRanks);

        outFile << userChoice << " ";
    }
    else
    {
        outFile << originalWord << " ";
    }
    fixWords(dictionary, inFile, outFile, fileContents, wordRanks);
}

int main(int argc, char* argv[]) {
    // Create a vector to hold the words and their ranks
    vector<pair<string, int>> wordRanks;

    if (argc == 1) {
        myspell();
        return 0;
    } else if (argc < 3) {
        cout << "Error, not enough arguments" << endl;
        return 1; // Exit with an error code
    }

    // Get the arguments
    const char* arg1 = argv[1]; // dictionary file
    const char* arg2 = argv[2]; // input file
    const char* arg3 = argv[3]; // output file

    // Create the hash table
    cop4530::HashTable<string> hashTable(1000000); // Default Size only works quickly with large default size, but works non the less
    //cop4530::HashTable<string> hashTable(101);   // if you need for grading purposes, use this one (very slow)

    hashTable.load(arg1); // Load the dictionary

    // hashTable.dump(); // Dump the hash table ... for debugging

    // Open the file to check
    ifstream inFile(arg2);
    if (!inFile) { // if the file cannot be opened
        cout << arg2;
        cout << "Error," << arg2 << "file cannot be opened" << endl;
        return 1; // Exit with an error code
    }

    // Open the file to write to
    ofstream outFile(arg3);
    if (!outFile) { // if the file cannot be opened
        cout << "Error, output file cannot be opened" << endl;
        return 1; // Exit with an error code
    }

    ifstream pairFile("wordrank.txt");
    if (!pairFile) { // if the file cannot be opened
        cout << "Error, rank file cannot be opened" << endl;
        return 1; // Exit with an error code
    }

    // Load the word ranks into the vector
    string pairWord;
    int pairRank;
    while (pairFile >> pairWord >> pairRank) {
        wordRanks.push_back(make_pair(pairWord, pairRank));
    }
    pairFile.close();

    // load file contents into vector
    vector<string> fileContents;
    char ch;
    string word;
    while (inFile.get(ch)) {
        // Check if the character is an alphanumeric character or a hyphen
        if (isalnum(ch) || ch == '-') {
            word += ch;
        } else if (ch == '\n') {
            fileContents.push_back(word);
            word.clear();
            fileContents.push_back("\n");
        } else if (!word.empty()) {
            // If the word is not empty, add it to the vector and reset it
            fileContents.push_back(word);
            word.clear();
        }
    }
    inFile.close();
    inFile.open(arg2);

    // Fix the words
    fixWords(hashTable, inFile, outFile, fileContents, wordRanks);

    outFile.close();
    pairFile.close();
    cout << "File has been fixed." << endl;
}
