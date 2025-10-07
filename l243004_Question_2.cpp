#include <iostream>
#include <string>
#include <fstream>
using namespace std;


string* readFile(string filename, int &actualWordCount){
    ifstream file(filename);
    if(!file){
        cout << "Erorr while Openining File or File does not exist" << endl;
        return nullptr;
    }

    int maxElements = 15;             // initial size of array;
    string *words = new string[maxElements];
    actualWordCount = 0;

    string line;                        
    while(getline(file, line)){                          // all words -> store in array
        if(actualWordCount >= maxElements){
            maxElements *= 2;
            string *newWords = new string[maxElements];
            for(int i = 0; i < actualWordCount; i++){
                newWords[i] = words[i];
            }
            delete[]words;
            words = newWords;   
        }
        words[actualWordCount] = line;
        actualWordCount++;
    }
    file.close();
    return words;
}

int userInput(string* words, int actualWordCount){
    int choice;
    bool valid = false;

    while (!valid) {
        cout << "Enter any number within range (1 to " << actualWordCount << "): ";
        
        if (!(cin >> choice)) {               // used help from internet (program was crashing when retaking inputs)
            cout << "Invalid input! Please enter a number only." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        if (choice < 1 || choice > actualWordCount) {
            cout << "Number out of range! Please enter between 1 and " << actualWordCount << "." << endl;
            continue;
        }
        valid = true;
    }
    return choice - 1;
}

void Display(string str){
    cout << "Current Word Status: " ;
    int len = str.length();
    for(int c = 0; c < len; c++){
        cout << str[c] << " ";
    }
    cout << endl << endl;
}

char letterInput(){
     char letter;
        bool validInput = false;

        while (!validInput) {
            cout << "Enter a letter guess (a to z): ";
            cin >> letter;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid input! Please enter a lowercase letter." << endl;
                continue;
            }

            if (letter < 'a' || letter > 'z') {
                cout << "Please enter only lowercase letters (a-z)." << endl;
                continue;
            }
            validInput = true;
        }
        return letter;
    }

bool hangman(string word){
    bool wordFound,letterFound;
    wordFound = letterFound = false;
    int tries = 0;
    int len= word.length();

    string wordGuesser = "";
    for(int c = 0; c < len; c++){
        wordGuesser += "_";
    }

    Display(wordGuesser);
    while(tries < 7 && !wordFound){
        char guess = letterInput();

        for(int c = 0; c < len; c++){
            if(word[c] == guess){
                wordGuesser[c] = guess;
                letterFound = true;
            }
        }
        if(!letterFound)
            tries++;
        letterFound = false;

        cout << "Wrong Guess, " << (7 - tries) << " tries remaining." << endl;

        Display(wordGuesser);
        if(wordGuesser == word)
            return true;
    }
    return false;
}


int main(){
    string filename = "hangman.txt";
    int arraySize, wordIndex;
    string* words;
    words = readFile(filename, arraySize);
   if(!words){
        return -1;
   }

   wordIndex = userInput(words, arraySize);

   bool wordFound = hangman(words[wordIndex]);
   if(wordFound)
        cout << "Word found" << endl;
    else
        cout << "You failed" << endl;
    return 0;
}