#ifndef _CGAME_H_
#define _CGAME_H_

#include "canimal.h"
#include "cpeople.h"
#include "ctraffic.h"
#include "cvehicle.h"
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include "graffic.h"

const int MAX_OBJECT = 3;
const int MIN_OBJECT = 2;

using namespace std;

vector<int> pos = { 8, 14, 20, 26 }; // positions of the objects

class CGAME {
private:
	CTRUCK* truck;
	CCAR* car;
	CAMBULANCE* ambulance;
	CDEER* deer;
	CCOW* cow;
	CPEOPLE people;
	int score;
	int count;
	int level;
	CTRAFFIC truckTraffic{ 100 + rand() % 50 };
	CTRAFFIC carTraffic{ 100 };

public:
	CGAME() {
		score = 0;
		count = 0;
		level = 1;
		truck = new CTRUCK[MIN_OBJECT];
		car = new CCAR[MIN_OBJECT];
		deer = new CDEER[MIN_OBJECT];
		cow = new CCOW[MIN_OBJECT];
		ambulance = new CAMBULANCE;
		srand((unsigned)time(0));
		random_shuffle(pos.begin(),
			pos.end()); // randomize the positions of the objects
		for (int i = 0; i < MIN_OBJECT; ++i) { // create the objects
			int x = i * 30 + (rand() % (10));    // randomize the x position
			srand((unsigned)time(0));
			truck[i].setX(10 * i + x + rand() % (5));
			truck[i].setY(pos[0]);
			srand((unsigned)time(0));
			car[i].setX(5 * i + x + rand() % (5));
			car[i].setY(pos[1]);
			srand((unsigned)time(0));
			deer[i].setX(10 * i + x + rand() % (5));
			deer[i].setY(pos[2]);
			srand((unsigned)time(0));
			cow[i].setX(5 * i + x + rand() % (5));
			cow[i].setY(pos[3]);
		}
	}


	void setSpeed(int speed) {          // speed up the game
		if (getScore() * 5 < speed)      // if the score is less than the speed
			Sleep(speed - getScore() * 5); // sleep for the difference
		else                             // else
			Sleep(5);                      // sleep for 5 ms
	}


	void drawMap() { // draw the map
		textColor(14); // set the color to yellow
		gotoxy(1, MAP_HEIGHT / 3 + 3); // set the position
		cout
			<< R"(							
													        	   _____ 
													        	  ||W ^||
													        	  ||___||
														     _____|/___\|_____
														    ||A <|||S v|||D >||
														    ||___|||___|||___||
														    |/___\|/___\|/___\|
														     _____ 
														    ||P  ||
														    ||___||  Pause Game
														    |/___\|	
														     _____ 
														    ||L  ||
														    ||___||  Save Game
														    |/___\|	   
											
)";

		for (int i = 0; i < MAP_HEIGHT; ++i) { // draw the map
			gotoxy(0, i);                       // set the position
			cout << char(186) << '\n';          // draw the map
		}
		for (int i = 0; i < MAP_HEIGHT; ++i) { // draw the map
			gotoxy(0, i);                       // set the position
			gotoxy(MAP_WIDTH, i);                // set the position
			cout << char(186) << '\n';          // draw the map
		}

		for (int i = 0; i < 5; ++i) {                     // draw the map
			gotoxy(1, 6 + 6 * i);                           // set the position
			for (int j = 0; j < (MAP_WIDTH - 1) / 11; ++j) { // draw the map
				cout << "==========|";                        // draw the map
			}
		}

		gotoxy(0, 0);                        // set the position
		cout << char(201);                   // draw the map
		for (int i = 1; i < MAP_WIDTH; i++) { // draw the map
			cout << char(205);                 // draw the map
		}
		cout << char(187); // draw the map

		gotoxy(0, MAP_HEIGHT);                // set the position
		cout << char(200);                   // draw the map
		for (int i = 1; i < MAP_WIDTH; i++) { // draw the map
			cout << char(205);                 // draw the map
		}
		cout << char(188); // draw the map

		textColor(7); // set the color to white
	}

	inline int getScore() {
		if ((count / 5) == level) {
			level++;  randomPos(); system("cls"); drawMap();
		};
		return score;
	} // get the score

	void printScore() {                      // print the score
		gotoxy(100 + 20, 14);                  // set the position
		cout << "SCORE: " << score * 100; // print the score
		gotoxy(100 + 20, 15);                  // set the position
		cout << "level: " << level; // print the score

	}


	void reset() {             // reset the game
		if (people.isFinish()) { // if the people is at the top
			for (int i = 1; i < 6; i++) {
				gotoxy(1, i);
				cout
					<< R"(                                                                                                   )";
			}
			people.draw();
			gotoxy(people.getX() + 3, people.getY());
			cout << "+" << level * 100;
			Sleep(250);
			gotoxy(people.getX() + 3, people.getY());
			cout << "    ";
			people.setX(MAP_WIDTH / 2 - 1);
			people.setY(MAP_HEIGHT - 3); // reset the people
			score += level;                    // increment the score
			count++;
		}
	}
	void drawGame() {                        // draw the game
		for (int i = 0; i < (level >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
			deer[i].draw();                      // draw the deer
			cow[i].draw();                       // draw the cow
		}
		for (int i = 0; i < (level >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
			truck[i].draw();                     // draw the truck
			car[i].draw();                       // draw the car
		}
		people.draw(); // draw the people
	}

	~CGAME() { // destructor
		delete[] truck;
		delete[] car;
		delete ambulance;
		delete[] deer;
		delete[] cow;
	}

	inline CPEOPLE getPeople() { return people; } // get the people

	void pauseGame(HANDLE t) { SuspendThread(t); } // pause the game

	void resumeGame(HANDLE t) { ResumeThread(t); } // resume the game

	void updatePosPeople(char ch) { // update the position of the people
		if (ch == 'A') {              // if the key is A
			people.clear();             // clear the people
			people.Left(4);             // move the people to the left
		}
		else if (ch == 'W') {       // if the key is W
			people.clear();             // clear the people
			people.Up(6);               // move the people to the up
		}
		else if (ch == 'D') {       // if the key is D
			people.clear();             // clear the people
			people.Right(4);            // move the people to the right
		}
		else if (ch == 'S') {       // if the key is S
			people.clear();             // clear the people
			people.Down(6);             // move the people to the down
		}
	}

	void updatePosVehicle() { // update the position of the vehicle
		if (truckTraffic.getState() == false) {           // if the truck moving
			truckTraffic.drawGreenLight(truck->getY() - 1); // draw the green light
			for (int i = 0; i < (level >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i)            // for each object
				truck[i].move(-1, 0);                         // move the truck
			if (truckTraffic.updateTime() < 0) {            // if the time is up
				truckTraffic.setState(true);                  // set the state to true
				truckTraffic.setTime(50);                     // set the time to 50
			}
		}
		else {
			truckTraffic.drawRedLight(truck->getY() - 1); // draw the red light
			if (truckTraffic.updateTime() < 0) {          // if the time is up
				truckTraffic.setState(false);               // set the state to false
				truckTraffic.setTime(150);                  // set the time to 150
			}
		}

		if (carTraffic.getState() == false) {         // if the car moving
			carTraffic.drawGreenLight(car->getY() - 1); // draw the green light
			for (int i = 0; i < (level >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i)        // for each object
				car[i].move(1, 0);                       // move the car
			if (carTraffic.updateTime() < 0) {          // if the time is up
				carTraffic.setState(true);                // set the state to true
				carTraffic.setTime(50);                   // set the time to 50
			}
		}
		else {
			carTraffic.drawRedLight(car->getY() - 1); // draw the red light
			if (carTraffic.updateTime() < 0) {        // if the time is up
				carTraffic.setTime(150 +
					rand() % 50); // set the time to 150 + random number
				carTraffic.setState(false);      // set the state to false
			}
		}
	}

	void updatePosAnimal() {                 // update the position of the animal
		for (int i = 0; i < (level >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
			deer[i].move(-1, 0);                  // move the deer
			cow[i].move(1, 0);                   // move the cow
		}
	}

	bool isImpact() {                        // check if the people hit the object
		for (int i = 0; i < (level >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
			if (truck[i].getY() ==
				people.getY() -
				1) // if the truck is on the same line	with the people
				if (abs(truck[i].getX() - people.getX()) < 3 ||
					(people.getX() > truck[i].getX() &&
						people.getX() <
						truck[i].getX() + truck[i].getLength())) { // if the people is in the truck
					people.setState(0);             // set the state to 0
					return true;                    // return true
				}
			if (car[i].getY() == people.getY() - 1) // if the car is on the same line
				if (abs(car[i].getX() - people.getX()) < 2 ||
					(people.getX() > car[i].getX() &&
						people.getX() <
						car[i].getX() + car[i].getLength() + 1)) { // if the people is in the car
					people.setState(0);           // set the state to 0
					return true;                  // return true
				}
			if (deer[i].getY() ==
				people.getY() - 1) // if the deer is on the same line
				if (abs(deer[i].getX() - people.getX()) < 3 ||
					(people.getX() > deer[i].getX() + 1 &&
						people.getX() <
						deer[i].getX() + deer[i].getLength())) { // if the people is in the deer
					people.setState(0);           // set the state to 0
					return true;                  // return true
				}
			if (cow[i].getY() == people.getY() - 1) // if the cow is on the same line
				if (abs(cow[i].getX() - people.getX()) < 2 ||
					(people.getX() > cow[i].getX() + 1 &&
						people.getX() <
						cow[i].getX() + cow[i].getLength() + 1)) { // if the people is in the cow
					people.setState(0);           // set the state to 0
					return true;                  // return true
				}
		}
		return false; // return false
	}

	void exitGame(HANDLE t) { // exit the game
		system("cls");          // clear the screen
		exit(0);                // exit the game
	}

	void drawDie() {                      //	draw the ambulance
		ambulance->setX(MAP_WIDTH);          // set the x position to the map width
		ambulance->setY(people.getY() - 1); // set the y position to the people
		for (int i = MAP_WIDTH; i > -16; --i) { // for each x position
			ambulance->draw();                   // draw the ambulance
			ambulance->move(-1, 0);              // move the ambulance
			Sleep(10);                           // sleep for 10 ms
		}
		system("cls"); // clear the screen
	}

	void resetGame() { // reset the game
		people.reset();           // reset the people
		score = 0;                // set the score to t
		count = 0;
		level = 1;
		randomPos();
	}

	void randomPos() {
		if (level == 2) {
			delete[] deer;
			delete[] cow;
			deer = new CDEER[MAX_OBJECT];
			cow = new CCOW[MAX_OBJECT];
		}
		if (level == 3) {
			delete[] truck;
			delete[] car;
			truck = new CTRUCK[MAX_OBJECT];
			car = new CCAR[MAX_OBJECT];
		}
		srand((unsigned)time(0));                         // randomize the seed
		random_shuffle(pos.begin(), pos.end()); // randomize the position

		for (int i = 0; i < (level >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
			int x = i * 30 + (rand() % (10));    // randomize the x position
			srand((unsigned)time(0));                      // randomize the seed
			truck[i].setX(10 * i + x +
				rand() % (5)); // set the x position of the truck
			truck[i].setY(pos[0]);         // set the y position of the truck

			srand((unsigned)time(0));                        // randomize the seed
			car[i].setX(5 * i + x + rand() % (5)); // set the x position of the car
			car[i].setY(pos[1]);
		}                     // set the y position of the car
		for (int i = 0; i < (level >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
			int x = i * 30 + (rand() % (10));    // randomize the x position
			srand((unsigned)time(0));                          // randomize the seed
			deer[i].setX(10 * i + x + rand() % (5)); // set the x position of the deer
			deer[i].setY(pos[2]);                      // set the y position of the deer

			srand((unsigned)time(0));                        // randomize the seed
			cow[i].setX(5 * i + x + rand() % (5)); // set the x position of the cow
			cow[i].setY(pos[3]);                     // set the y position of the cow
		}
	}

	void drawContinue() { // draw the continue
		textColor(14);      // set the text color to yellow
		gotoxy(1, 2);       // set the position
		cout << R"(
				 $$$$$$\                                           $$$$$$\                                 
				$$  __$$\                                         $$  __$$\                                
				$$ /  \__| $$$$$$\  $$$$$$\$$$$\   $$$$$$\        $$ /  $$ |$$\    $$\  $$$$$$\   $$$$$$\  
				$$ |$$$$\  \____$$\ $$  _$$  _$$\ $$  __$$\       $$ |  $$ |\$$\  $$  |$$  __$$\ $$  __$$\ 
				$$ |\_$$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |      $$ |  $$ | \$$\$$  / $$$$$$$$ |$$ |  \__|
				$$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|      $$ |  $$ |  \$$$  /  $$   ____|$$ |      
				\$$$$$$  |\$$$$$$$ |$$ | $$ | $$ |\$$$$$$$\        $$$$$$  |   \$  /   \$$$$$$$\ $$ |      
				 \______/  \_______|\__| \__| \__| \_______|       \______/     \_/     \_______|\__|      
)";
		gotoxy(MAP_WIDTH / 1.5 + 3, MAP_HEIGHT / 2 - 1); // set the position
		cout << " Play again?(y/N) ";                  // print the message
		textColor(7); // set the text color to white
	}

	void saveGame() {
		char fileName[9];
		gotoxy(MAP_WIDTH + 12, 30);
		textColor(224);
		cout << " Enter file name:          ";
		gotoxy(MAP_WIDTH + 30, 30);
		cin.getline(fileName, 8);
		textColor(7);
		string temp = fileName;
		ofstream ofs(temp + ".txt");
		ofs << people.getX() << " " << people.getY() << endl;
		for (int i = 0; i < 3; i++) {
			ofs << truck[i].getX() << " " << truck[i].getY() << endl;
			ofs << car[i].getX() << " " << car[i].getY() << endl;
			ofs << cow[i].getX() << " " << cow[i].getY() << endl;
			ofs << deer[i].getX() << " " << deer[i].getY() << endl;
		}
		ofs << score << endl;
		ofs << truckTraffic.getTime() << " " << truckTraffic.getState() << endl;
		ofs << carTraffic.getTime() << " " << carTraffic.getState() << endl;
	}

	std::wstring ExePath() {
		TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
		return std::wstring(buffer).substr(0, pos);
	}

	void listTXT() {
		vector<wstring> names;
		wstring temp = ExePath();
		while (temp.back() != '\\') {
			temp.pop_back();
		}
		temp += L"\\DOANCUOIKY\\*.txt";
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(temp.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(MAP_WIDTH / 1.5, 18 + i);
			cout << i + 1 << ".              ";
		}
		for (auto i = 0; i < names.size(); i++) {
			wstring a = names[i];
			gotoxy(MAP_WIDTH / 1.5 + 3, 18 + i);
			do {
				a.pop_back();
			} while (a.back() != '.');
			a.pop_back();
			wcout << a << endl;
		}
	}

	void loadGame() {

		listTXT();
		string s;
		textColor(224);
		gotoxy(MAP_WIDTH / 1.5, MAP_HEIGHT / 2 - 2);
		cout << " Enter file name:          ";
		gotoxy(MAP_WIDTH / 1.2 + 1, MAP_HEIGHT / 2 - 2);
		cin >> s;
		textColor(7);
		s += ".txt";
		ifstream ifs(s);
		if (ifs) {
			int x, y;
			ifs >> x >> y;
			people.setX(x);
			people.setY(y);
			for (int i = 0; i < 3; i++) {
				ifs >> x >> y;
				truck[i].setX(x);
				truck[i].setY(y);
				ifs >> x >> y;
				car[i].setX(x);
				car[i].setY(y);
				ifs >> x >> y;
				cow[i].setX(x);
				cow[i].setY(y);
				ifs >> x >> y;
				deer[i].setX(x);
				deer[i].setY(y);
			}
			ifs >> score;
			ifs >> x >> y;
			truckTraffic.setTime(x);
			truckTraffic.setState(y);
			ifs >> x >> y;
			carTraffic.setState(y);
			carTraffic.setTime(x);
		}
	}

	void musicOff(int i) {
		if (i == 0)
			PlaySound(NULL, 0, 0);
		else if (i == 1)
			PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else if (i == 2)
			PlaySound(TEXT("song1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}

	void drawPause() {
		gotoxy(120, 30);
		textColor(224);
		cout << " Pause ";
		textColor(7);
	}
};

#endif