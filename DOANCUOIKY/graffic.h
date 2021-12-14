#ifndef _GRAFFIC_H_
#define _GRAFFIC_H_
#include <string>
#include "console.h"
#include <iostream>
using namespace std;

const string zero[] = { " $$$$$$ ", "$$    $$", "$$    $$", "$$    $$",
					   "$$    $$", "$$    $$", " $$$$$$ " };
const string one[7] = { "   $$   ", "$$$$$   ", "   $$   ", "   $$   ",
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

void asci(int score) {
	string a = to_string(score);
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
	for (int i = 0; i < a.size(); i++) {
		switch (int(a[i]) - 48) {
		case 0:
			for (int j = 0; j < 7; j++) {
				gotoxy( i * 9 + i + MAP_WIDTH + t, 5 + j); cout << zero[j];
			}
			break;
		case 1:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << one[j];
			}
			break;
		case 2:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << two[j];
			}
			break;
		case 3:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << three[j];
			}
			break;
		case 4:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << four[j];
			}
			break;
		case 5:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << five[j];
			}
			break;
		case 6:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << six[j];
			}
			break;
		case 7:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << seven[j];
			}
			break;
		case 8:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << eight[j];
			}
			break;
		case 9:
			for (int j = 0; j < 7; j++) {
				gotoxy(  i * 9 + i + MAP_WIDTH + t  , 5 + j); cout << nine[j];
			}
			break;
		default:
			break;
		}

	}
}
#endif // !_GRAFFIC_H_
