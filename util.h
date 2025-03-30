#ifndef GUARD_util
#define GUARD_util

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


int generateRandomNumber(const int min, const int max);
bool isCharInWord(const char ch, const std::string& word);
std::vector<std::string> readWordListFromFile(const std::string& filePath);
void cls(); //http://stackoverflow.com/questions/34842526/update-console-without-flickering-c/34843181
void setConsoleColor(WORD attributes);
#endif


struct Score {
    int totalGames = 0;
    int wins = 0;
    int losses = 0;
};

Score readScoreFromFile(const std::string& filePath);
void writeScoreToFile(const std::string& filePath, const Score& score);
void ResetScore(const std::string& filePath);
