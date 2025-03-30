#include "util.h"


using std::string;

string getDrawing(const int i)
{
    static int LEN = 8;
    static string FIGURES[] = {
                "   -------------    \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |           |    \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|    \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |          /     \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |          / \\  \n"
                "   |     \n"
                " -----   \n",
    };
    return FIGURES[i % LEN];
}

string getNextHangman()
{
    static int LEN = 4;
    static string FIGURES[] = {
          "   ------------+    \n"
          "   |          /     \n"
          "   |         O      \n"
          "   |        /|\\    \n"
          "   |        / \\    \n"
          "   |        \n"
          " -----      \n" ,
          "   ------------+     \n"
          "   |           |     \n"
          "   |           O     \n"
          "   |          /|\\   \n"
          "   |          / \\   \n"
          "   |        \n"
          " -----      \n",
          "   ------------+      \n"
          "   |            \\    \n"
          "   |            O     \n"
          "   |           /|\\   \n"
          "   |           / \\   \n"
          "   |      \n"
          " -----    \n",
          "   ------------+     \n"
          "   |           |     \n"
          "   |           O     \n"
          "   |          /|\\   \n"
          "   |          / \\   \n"
          "   |        \n"
          " -----      \n",
          };
    static int i = 0;
    i = (i + 1) % LEN;

    return FIGURES[i];
}

string getNextStandingman()
{
    static int LEN = 8;
    static string FIGURES[] = {
          "           \n"
          "     O     \n"
          "    /|\\   \n"
          "    | |    \n",
          "           \n"
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n",
          "           \n"
          "   __O__   \n"
          "     |     \n"
          "    / \\   \n",
          "           \n"
          "    \\O/   \n"
          "     |     \n"
          "    / \\   \n",
          "           \n"
          "   __O__   \n"
          "     |     \n"
          "    / \\   \n",
          "           \n"
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "           \n"
          "    O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "           \n"
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "           \n"
          "      O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "           \n"
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          };
    static int i = 0;
    i = (i + 1) % LEN;

    return FIGURES[i];
}
