#ifndef _CGRAFFIC_H_
#define _CGRAFFIC_H_
#include "api.h"
#include <iostream>
#include <string>
using namespace std;

const string zero[] = { " $$$$$$ ", "$$    $$", "$$    $$", "$$    $$",
    "$$    $$", "$$    $$", " $$$$$$ " }; // ascii art of zero
const string one[] = { "   $$   ", "$$$$$   ", "   $$   ", "   $$   ",
    "   $$   ", "   $$   ", "$$$$$$$$" }; // 	ascii art of one
const string two[] = { " $$$$$$ ", "$$    $$", "      $$", " $$$$$$ ",
    "$$      ", "$$      ", "$$$$$$$$" }; // 	ascii art of two
const string three[] = { " $$$$$$ ", "$$    $$", "      $$", "   $$$$ ",
    "      $$", "$$    $$", " $$$$$$ " }; // 	ascii art of three
const string four[] = { "$$    $$", "$$    $$", "$$    $$", "$$$$$$$$",
    "      $$", "      $$", "      $$" }; // 	ascii art of four
const string five[] = { "$$$$$$$ ", "$$      ", "$$      ", "$$$$$$$ ",
    "      $$", "$$    $$", " $$$$$$ " }; // 	ascii art of five
const string six[] = { " $$$$$$ ", "$$    $$", "$$      ", "$$$$$$$ ",
    "$$    $$", "$$    $$", " $$$$$$ " }; // 	ascii art of six
const string seven[] = { "$$$$$$$$", "     $$ ", "    $$  ", "   $$   ",
    "  $$    ", " $$     ", "$$      " }; // 	ascii art of seven
const string eight[] = { " $$$$$$ ", "$$    $$", "$$    $$", " $$$$$$ ",
    "$$    $$", "$$    $$", " $$$$$$ " }; // 	ascii art of eight
const string nine[] = { " $$$$$$ ", "$$    $$", "$$    $$", " $$$$$$$",
    "      $$", "$$    $$", " $$$$$$ " }; // 	ascii art of nine

const string gameTitle = { // ascii art of game title
    R"( 
               $$$$$$\                                          $$\                            $$$$$$\                                    
              $$  __$$\                                         \__|                          $$  __$$\                                   
              $$ /  \__| $$$$$$\   $$$$$$\   $$$$$$$\  $$$$$$$\ $$\ $$$$$$$\   $$$$$$\        $$ /  \__| $$$$$$\  $$$$$$\$$$$\   $$$$$$\  
              $$ |      $$  __$$\ $$  __$$\ $$  _____|$$  _____|$$ |$$  __$$\ $$  __$$\       $$ |$$$$\  \____$$\ $$  _$$  _$$\ $$  __$$\ 
              $$ |      $$ |  \__|$$ /  $$ |\$$$$$$\  \$$$$$$\  $$ |$$ |  $$ |$$ /  $$ |      $$ |\_$$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |
              $$ |  $$\ $$ |      $$ |  $$ | \____$$\  \____$$\ $$ |$$ |  $$ |$$ |  $$ |      $$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|
              \$$$$$$  |$$ |      \$$$$$$  |$$$$$$$  |$$$$$$$  |$$ |$$ |  $$ |\$$$$$$$ |      \$$$$$$  |\$$$$$$$ |$$ | $$ | $$ |\$$$$$$$\ 
               \______/ \__|       \______/ \_______/ \_______/ \__|\__|  \__| \____$$ |       \______/  \_______|\__| \__| \__| \_______|
                                                                              $$\   $$ |                                                  
                                                                              \$$$$$$  |                                                  
                                                                               \______/      )"
};

const string keyGuide = { // ascii art of key guide
    R"(							
														 ______ ______ ______ ______
														||W   |||A   |||S   |||D   ||
														||____|||____|||____|||____||
														|/____\|/____\|/____\|/____\|
														   Up    Left   Down   Right 
														 ______ ______ ______ ______
														||Esc |||T   |||L   |||P   ||
														||____|||____|||____|||____||
														|/____\|/____\|/____\|/____\|
														  Exit   Load   Save   Pause)"
};

const string gameOver = { // ascii art of game over
    R"(
			       $$$$$$\                                           $$$$$$\                                 
			      $$  __$$\                                         $$  __$$\                                
			      $$ /  \__| $$$$$$\  $$$$$$\$$$$\   $$$$$$\        $$ /  $$ |$$\    $$\  $$$$$$\   $$$$$$\  
			      $$ |$$$$\  \____$$\ $$  _$$  _$$\ $$  __$$\       $$ |  $$ |\$$\  $$  |$$  __$$\ $$  __$$\ 
			      $$ |\_$$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |      $$ |  $$ | \$$\$$  / $$$$$$$$ |$$ |  \__|
			      $$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|      $$ |  $$ |  \$$$  /  $$   ____|$$ |  
			      \$$$$$$  |\$$$$$$$ |$$ | $$ | $$ |\$$$$$$$\        $$$$$$  |   \$  /   \$$$$$$$\ $$ |      
			       \______/  \_______|\__| \__| \__| \_______|       \______/     \_/     \_______|\__|      )"
};

void drawAsciiScore(int mScore) // draw ascii score
{
    string a = to_string(mScore); // convert int to string
    int t = 0;
    if (a.size() == 1) { // if score is less than 10
        t = 22; // set t to 22
    }
    else if (a.size() == 2) { // if score is less than 100
        t = 17;
    }
    else if (a.size() == 3) { // if score is less than 1000
        t = 12;
    }
    else if (a.size() == 4) { // if score is less than 10000
        t = 7;
    }
    for (auto i = 0; i < a.size(); ++i) { // draw ascii score
        switch (int(a[i]) - 48) { // convert char to int
        case 0: // if 0
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << zero[j]; // print zero ascii art
            }
            break;
        case 1: // if 1
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << one[j]; // print one ascii art
            }
            break;
        case 2: // if 2
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << two[j]; // print two ascii art
            }
            break;
        case 3: // if 3
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << three[j]; // print three ascii art
            }
            break;
        case 4: // if 4
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << four[j]; // print four ascii art
            }
            break;
        case 5: // if 5
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << five[j]; // print five ascii art
            }
            break;
        case 6: // if 6
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << six[j]; // print six ascii art
            }
            break;
        case 7: // if 7
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << seven[j]; // print seven ascii art
            }
            break;
        case 8:
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << eight[j]; // print eight ascii art
            }
            break;
        case 9: // if 9
            for (int j = 0; j < 7; ++j) { // for each line
                gotoxy(i * 9 + i + MAP_WIDTH + t, 6 + j); // set position
                cout << nine[j]; // print nine ascii art
            }
            break;
        default:
            break;
        }
    }
}

void drawGameTitle() // draw game title
{
    gotoxy(0, MAP_HEIGHT / 4 - 7); // set position
    cout << gameTitle; // print game title
}

void drawKeyGuide() // draw key guide
{
    gotoxy(0, MAP_HEIGHT / 2 + 1); // set position
    cout << keyGuide; // print key guide
}

void drawGameOver() // draw game over
{
    gotoxy(0, MAP_HEIGHT / 4); // set position
    cout << gameOver; // print game over
}

#endif