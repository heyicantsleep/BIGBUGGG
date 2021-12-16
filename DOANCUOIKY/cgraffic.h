#ifndef _CGRAFFIC_H_
#define _CGRAFFIC_H_
#include <string>
#include "api.h"
#include <iostream>
using namespace std;

const string zero[] = { " $$$$$$ ", "$$    $$", "$$    $$", "$$    $$",
					   "$$    $$", "$$    $$", " $$$$$$ " };
const string one[] = { "   $$   ", "$$$$$   ", "   $$   ", "   $$   ",
					  "   $$   ", "   $$   ", "$$$$$$$$" };
const string two[] = { " $$$$$$ ", "$$    $$", "      $$", " $$$$$$ ",
					  "$$      ", "$$      ", "$$$$$$$$" };
const string three[] = { " $$$$$$ ", "$$    $$", "      $$", "   $$$$ ",
						"      $$", "$$    $$", " $$$$$$ " };
const string four[] = { "$$    $$", "$$    $$", "$$    $$", "$$$$$$$$",
					   "      $$", "      $$", "      $$" };
const string five[] = { "$$$$$$$ ", "$$      ", "$$      ", "$$$$$$$ ",
					   "      $$", "$$    $$", " $$$$$$ " };
const string six[] = { " $$$$$$ ", "$$    $$", "$$      ", "$$$$$$$ ",
					  "$$    $$", "$$    $$", " $$$$$$ " };
const string seven[] = { "$$$$$$$$", "     $$ ", "    $$  ", "   $$   ",
						"  $$    ", " $$     ", "$$      " };
const string eight[] = { " $$$$$$ ", "$$    $$", "$$    $$", " $$$$$$ ",
						"$$    $$", "$$    $$", " $$$$$$ " };
const string nine[] = { " $$$$$$ ", "$$    $$", "$$    $$", " $$$$$$$",
					   "      $$", "$$    $$", " $$$$$$ " };

const string gameTitle = { 
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
                                                                               \______/      )" };

const string keyGuide = { 
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
														  Exit   Load   Save   Pause)" };

const string gameOver = {
R"(
			       $$$$$$\                                           $$$$$$\                                 
			      $$  __$$\                                         $$  __$$\                                
			      $$ /  \__| $$$$$$\  $$$$$$\$$$$\   $$$$$$\        $$ /  $$ |$$\    $$\  $$$$$$\   $$$$$$\  
			      $$ |$$$$\  \____$$\ $$  _$$  _$$\ $$  __$$\       $$ |  $$ |\$$\  $$  |$$  __$$\ $$  __$$\ 
			      $$ |\_$$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |      $$ |  $$ | \$$\$$  / $$$$$$$$ |$$ |  \__|
			      $$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|      $$ |  $$ |  \$$$  /  $$   ____|$$ |      
			      \$$$$$$  |\$$$$$$$ |$$ | $$ | $$ |\$$$$$$$\        $$$$$$  |   \$  /   \$$$$$$$\ $$ |      
			       \______/  \_______|\__| \__| \__| \_______|       \______/     \_/     \_______|\__|      )" };

void asci(int mScore) {
	string a = to_string(mScore);
	int t = 0;
	if (a.size() == 1) {
		t = 22;
	}
	else if (a.size() == 2) {
		t = 17;
	}
	else if (a.size() == 3) {
		t = 12;
	}
	else if (a.size() == 4) {
		t = 7;
	}
	for (auto i = 0; i < a.size(); i++) {
		switch (int(a[i]) - 48) {
		case 0:
			for (int j = 0; j < 7; ++j) {
				gotoxy( i * 9 + i + MAP_WIDTH + t, 6 + j); cout << zero[j];
			}
			break;
		case 1:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << one[j];
			}
			break;
		case 2:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << two[j];
			}
			break;
		case 3:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << three[j];
			}
			break;
		case 4:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << four[j];
			}
			break;
		case 5:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << five[j];
			}
			break;
		case 6:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << six[j];
			}
			break;
		case 7:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << seven[j];
			}
			break;
		case 8:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << eight[j];
			}
			break;
		case 9:
			for (int j = 0; j < 7; ++j) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 6 + j); cout << nine[j];
			}
			break;
		default:
			break;
		}

	}
}

void drawGameTitle() {
	gotoxy(0, MAP_HEIGHT / 4 - 7);
	cout << gameTitle;
}

void drawKeyGuide() {
	gotoxy(0, MAP_HEIGHT / 2 + 1);
	cout << keyGuide;
}

void drawGameOver(){
	gotoxy(0, MAP_HEIGHT/4);
	cout << gameOver;
}

#endif 
