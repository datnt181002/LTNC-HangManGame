#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <algorithm>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "util.h"
#include "draw.h"

using namespace std;

const int MAX_MISTAKES = 8;

string chooseWordFromList(const vector<string>& wordList)
{
    if (wordList.empty()) return "";

    string word = wordList[generateRandomNumber(0, wordList.size()-1)];
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

const string SCORE_FILE = "score.txt";
void printStats(const string& word, const string& secretWord,
                const string& correctChars,
                const int incorrectGuess, const string& incorrectChars)
{
    Score score = readScoreFromFile(SCORE_FILE);

    cout << "-------------------------------" << endl;
    cout << "Games played: " << score.totalGames
         << " | Wins: " << score.wins
         << " | Losses: " << score.losses << endl;
    cout << "-------------------------------" << endl << endl;
    cout << "Current word: " << secretWord;
    cout << endl << "Correct guesses: " << correctChars;
    cout << "    " << "Incorrect guesses: " << incorrectChars;

    if (secretWord == word)
    {
        cout << endl << "Well done :D   The word is: " << word << endl;
    }
    else if (incorrectGuess == MAX_MISTAKES-1)
    {
        cout << endl << "You lose :(   The word is: " << word << endl;
    }
    else
    {
        cout << endl << "Choose a character: ";
    }
}

void printScreen(const string& word, const string& secretWord,
                 const string& correctChars,
                 const int incorrectGuess, const string& incorrectChars)
{
    //for (int i = 0; i < 30; ++i) cout << endl;
    cls();

    cout << getDrawing(incorrectGuess);
    printStats(word, secretWord, correctChars, incorrectGuess, incorrectChars);

}

char getInputCharacter()
{
    char ch;
    cin >> ch;
    return tolower(ch);
}

void updateSecretWord(string& secretWord, const char ch, const string& word)
{
    int len = word.length();
    for (int i = 0; i < len; ++i)
    {
        if (word[i] == ch)
        {
            secretWord[i] = ch;
        }
    }
}

void processData(const char ch, const string& word,
                 string& secretWord,
                 string& correctChars,
                 int& incorrectGuess, string& incorrectChars)
{
    if (isCharInWord(ch, word))
    {
        updateSecretWord(secretWord, ch, word);
        correctChars +=  ch;
        correctChars += " ";
    }
    else
    {
        incorrectGuess += 1;
        incorrectChars += ch;
        incorrectChars += " ";
    }
}

void playAnimation(const string& word, const string& secretWord,
                   const string& correctChars,
                   const int incorrectGuess, const string& incorrectChars)
{
    for (int i = 0; i < 22; ++i)
    {
        //for (int i = 0; i < 30; ++i) cout << endl;
        cls();
        if (secretWord == word)
        {
            cout << getNextStandingman();
        }
        else if (incorrectGuess == MAX_MISTAKES-1)
        {
            cout << getNextHangman();
        }
        printStats(word, secretWord, correctChars, incorrectGuess, incorrectChars);
        std::this_thread::sleep_for (std::chrono::milliseconds(250/2));
    }
}

int i;
int main()
{
    setConsoleColor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); // Trắng sáng
    cls();

    cout << endl << "Error: in reading vocabulary file: " << endl;
    cin >> i;

    while(1)
    {
        srand((int)time(0));
        //string vocabularyFile = "WordList/Ogden_Picturable_200.txt";
        //string vocabularyFile = "WordList/ErrorOpenFileTest.txt";
        string vocabularyFile = "WordList/EmptyTest.txt";
        vector<string> wordList;
        try
        {
            wordList = readWordListFromFile(vocabularyFile);
        }
        catch (domain_error)
        {
            cout << endl << "Error: in reading vocabulary file: " << vocabularyFile << endl;
            return 1;
        }

        string word = chooseWordFromList(wordList);
        if (word.empty())
        {
            cout << "Error: Coud not choose a random word." << endl;
            return 1;
        }
        //cout << "Chosen word: " << word << endl;
        string secretWord(word.length(), '-');

        int incorrectGuess = 0;
        string correctChars = "";
        string incorrectChars = "";

        printScreen(word, secretWord, correctChars, incorrectGuess, incorrectChars);

        do
        {
            char ch = getInputCharacter();

            processData(ch, word, secretWord,
                        correctChars, incorrectGuess, incorrectChars);

            printScreen(word, secretWord, correctChars, incorrectGuess, incorrectChars);

        }
        while (secretWord != word && incorrectGuess != MAX_MISTAKES-1);

        playAnimation(word, secretWord, correctChars, incorrectGuess, incorrectChars);


        Score score = readScoreFromFile(SCORE_FILE);
        score.totalGames++;
        if (secretWord == word) score.wins++;
        else score.losses++;
        writeScoreToFile(SCORE_FILE, score);
    }


    return 0;
}
