#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <algorithm>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <conio.h>        // Lib cho lệnh getch()

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
bool PrintScore(bool AlwayDisplay) //Nếu AlwayDisplay = false thì k hiện khi tổng game = 0 (ván đầu)
{
    Score score = readScoreFromFile(SCORE_FILE);
    if(score.totalGames == 0 && AlwayDisplay == false)
    {
        return false;
    }
    cout << "-------------------------------" << endl;
    cout << "Games played: " << score.totalGames
         << " | Wins: " << score.wins
         << " | Losses: " << score.losses << endl;
    cout << "-------------------------------" << endl << endl;
    return true;
}

void printStats(const string& word, const string& secretWord,
                const string& correctChars,
                const int incorrectGuess, const string& incorrectChars)
{
    PrintScore(true);
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


#define NumberOfList 4
int main()
{
    setConsoleColor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); // Trắng sáng
    cls();

    while(1)
    {
        int WordListChoosen = 0; //Reset bien wordlist
        while (WordListChoosen > NumberOfList || WordListChoosen < 1)
        {
            if(PrintScore(false) == true)
            {
                cout << "Press letter C or N or E to (C)ontinue or (N)ewgame or (E)xit?";
                char ch;
                while (1)
                {
                    ch = _getch();  // Đọc phím không cần Enter
                    if (ch == 'c' || ch == 'C')
                    {

                        break;
                    }
                    else if (ch == 'n' || ch == 'N')
                    {
                        ResetScore(SCORE_FILE);
                        break;
                    }
                    else if (ch == 'e' || ch == 'E')
                    {
                        return 1;
                    }
                }
            }
            cls();
            cout << "Choose Word Topic: " << endl << "1: Colors || 2: Foods || 3: Animals || 4: General" << endl << "Your Choose: ";
            cin >> WordListChoosen;
            cin.clear();
            cls();
            if(WordListChoosen > NumberOfList || WordListChoosen < 1)
            {
                WordListChoosen;
                cout << "Wroong Choosen! Press ENTER to choose again! " << endl;
                cin.get();
            }
        }

        string vocabularyFile;
        switch (WordListChoosen)
        {
        case 1:
            vocabularyFile = "WordList/Colors.txt";
            break;
        case 2:
            vocabularyFile = "WordList/Foods.txt";
            break;
        case 3:
            vocabularyFile = "WordList/Animals.txt";
            break;
        case 4:
            vocabularyFile = "WordList/general.txt";
            break;
        }

        srand((int)time(0));
        //string vocabularyFile = "WordList/Ogden_Picturable_200.txt";
        //string vocabularyFile = "WordList/ErrorOpenFileTest.txt";

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
