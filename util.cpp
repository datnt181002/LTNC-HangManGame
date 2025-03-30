#include "util.h"

using std::string;
using std::vector;
using std::ifstream;
using std::domain_error;

int generateRandomNumber(const int min, const int max)
{
    //srand((int)time(0)); // It is a bug if putting this line here.
    return rand() % (max - min + 1) + min;
}

vector<string> readWordListFromFile(const string& filePath)
{
    vector<string> wordList;
    string word;
    ifstream wordFile (filePath);
    if (!wordFile.is_open()) {
        throw domain_error("Unable to open file");
    }

    //while ( getline (wordFile, word) ){  // Thong thuong doc tung line.
                                           // Chuong trinh nay cung chay.
    while (wordFile >> word) {  // Nhung voi chuong trinh nay, doc tung word cung duoc
                                // Tuc ca 2 cach doc deu chay.
        wordList.push_back(word);
        //cout << word << '\n';
    }
    wordFile.close();

    return wordList;
}

bool isCharInWord(const char ch, const string& word)
{
  return (word.find_first_of(ch) != string::npos);
    /*
    int len = word.length();
    for (int i = 0; i < len; ++i) {
        if (word[i] == ch) {
            return true;
        }
    }
    return false;
    */
}

//http://stackoverflow.com/questions/34842526/update-console-without-flickering-c/34843181
void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

void setConsoleColor(WORD attributes)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, attributes);
}


Score readScoreFromFile(const std::string& filePath) {
    Score score;
    std::ifstream file(filePath);
    if (file.is_open()) {
        file >> score.totalGames >> score.wins >> score.losses;
        file.close();
    }
    return score;
}

void writeScoreToFile(const std::string& filePath, const Score& score) {
    std::ofstream file(filePath, std::ios::trunc); // Ghi đè
    if (file.is_open()) {
        file << score.totalGames << " " << score.wins << " " << score.losses;
        file.close();
    }
}
