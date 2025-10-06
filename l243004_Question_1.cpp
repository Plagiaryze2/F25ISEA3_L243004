#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

bool isPalindrome(const string &str) {
    int length = str.length();
    for (int i = 0; i < length / 2; i++) {
        if (str[i] != str[length - i - 1])
            return false;
    }
    return true;
}

int main() {
    string input;

    while (true) {
        cout << "Enter a string: ";
        getline(cin,input);

        cout << "Enter Any Key to Proceed (ESC to EXIT): " << endl;
        if (_getch() == 27) {
            cout << "Quitting Program" << endl;
            break;
        } 
        else {
            if (isPalindrome(input))
                cout << input << " is a palindrome" << endl;
            else
                cout << input << " is not a palindrome" << endl;
        }
    }
    return 0;
}
