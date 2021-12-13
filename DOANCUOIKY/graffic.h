#ifndef _GRAFFIC_H_
#define _GRAFFIC_H_
#include <string>

using namespace std;

const string zero[] = { " $$$$$ ", "$$   $$", "$$   $$", "$$   $$", "$$   $$", "$$   $$", " $$$$$ " };
const string one[] = { "  $$ ", "$$$$ ", "  $$ ", "  $$ ", "  $$ ", "  $$ ", "$$$$$" };
const string two[] = { " $$$$$ ", "$$   $$", "     $$", " $$$$$ ", "$$     ", "$$     ", "$$$$$$$" };
const string three[] = { " $$$$$ ", "$$   $$", "     $$", "  $$$$ ", "     $$", "$$   $$", " $$$$$ " };
const string four[] = { "$$   $$", "$$   $$", "$$   $$", "$$$$$$$", "     $$", "     $$" , "     $$" };
const string five[] = { "$$$$$$ ", "$$     ", "$$     ", "$$$$$$ ", "     $$", "$$   $$" , " $$$$$ " };
const string six[] = { " $$$$$ ", "$$   $$", "$$     ", "$$$$$$ ", "$$   $$", "$$   $$" , " $$$$$ " };
const string seven[] = { "$$$$$$$", "     $$", "    $$ ", "   $$  ", "  $$   ", " $$    " , "$$     " };
const string eight[] = { " $$$$$ ", "$$$$$$$", "$$$$$$$", " $$$$$ ", "$$$$$$$", "$$$$$$$" , " $$$$$ " };
const string nine[] = { " $$$$$ ", "$$$$$$$", "$$$$$$$", " $$$$$$", "     $$", "$$$$$$$" , " $$$$$ " };

void asci(int score) {
	string a = to_string(score);
	string i[7];
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < 7; j++) {
			switch (a[i]) {
			case 0: 
			}
		}
	}
}

#endif // !_GRAFFIC_H_
