#ifndef _CGAME_H_
#define _CGAME_H_

#include "canimal.h"
#include "cpeople.h"
#include "cvehicle.h"
#include "ctraffic.h"
#include <conio.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> p = { 8, 14, 20, 26 };


class CGAME {
private:
	CTRUCK* truck;
	CCAR* car;
	CAMBU* ambu;
	CDEER* deer;
	CCOW* cow;
	CPEOPLE people;
	int score;
	CTRAFFIC truckTraffic{ 100 + rand() % 50 };
	CTRAFFIC carTraffic{ 100 };
public:
	CGAME() {
		score = 0;
		truck = new CTRUCK[MAX_VEHICLE];
		car = new CCAR[MAX_VEHICLE];
		deer = new CDEER[MAX_ANIMAL];
		cow = new CCOW[MAX_ANIMAL];
		ambu = new CAMBU;
		srand(time(0));
		random_shuffle(p.begin(), p.end());
		for (int i = 0; i < 3; ++i) {
			int x = i * 30 + (rand() % (10));
			srand(time(0));
			truck[i].setX(10 * i + x + rand() % (5));
			truck[i].setY(p[0]);
			srand(time(0));
			car[i].setX(5 * i + x + rand() % (5));
			car[i].setY(p[1]);
			srand(time(0));
			deer[i].setX(10 * i + x + rand() % (5));
			deer[i].setY(p[2]);
			srand(time(0));
			cow[i].setX(5 * i + x + rand() % (5));
			cow[i].setY(p[3]);
		}
	}

	void speedUp(int speed) {
		if (getScore() * 5 < speed) {
			Sleep(speed - getScore() * 5);
		}
		else
			Sleep(5);
	}

	void printScore() {
		gotoxy(100 + 20, 14);
		cout << "SCORE: " << getScore() * 100;
	}

	void drawMap() {
		textColor(14);

		gotoxy(1, 5);
		cout << R"(
														 ____ ____ ____ ____ ____ 
														||N |||H |||O |||M |||9 ||
														||__|||__|||__|||__|||__||
														|/__\|/__\|/__\|/__\|/__\|
)";


		gotoxy(1, consoleHeight / 2.5 + 3);
		cout << R"(									   
										         	                 _______________________ 
										         	           	| Press W,A,S,D to move |
										               	                | Press L to save game  |
										         	                | Press P to pause game |
										         	           	| Press ESC to exit     |
										         	           	 ----------------------- 
										         	           	         \  ^__^
										         	           	          \ (Oo)\_______
										         	           	            (__)\       )\/\
										         	           	                ||----w |
										         	           	                ||     ||)";

		for (int i = 0; i < consoleHeight; ++i) {
			gotoxy(0, i);
			cout << char(186) << '\n';
		}
		for (int i = 0; i < consoleHeight; ++i) {
			gotoxy(0, i);
			gotoxy(consoleWidth, i);
			cout << char(186) << '\n';
		}

		for (int i = 0; i < 5; ++i) {
			gotoxy(1, 6 + 6 * i);
			for (int j = 0; j < (consoleWidth - 1) / 11; ++j) {
				cout << "==========|";
			}
		}

		gotoxy(0, 0);
		cout << char(201);
		for (int i = 1; i < consoleWidth; i++) {
			cout << char(205);
		}
		cout << char(187);

		gotoxy(0, consoleHeight);
		cout << char(200);
		for (int i = 1; i < consoleWidth; i++) {
			cout << char(205);
		}
		cout << char(188);



		textColor(7);


	}

	int getScore() {
		return score;
	}

	void drawGame() {
		for (int i = 0; i < MAX_VEHICLE; ++i) {
			truck[i].draw();
			car[i].draw();
		}
		for (int i = 0; i < MAX_ANIMAL; ++i) {
			deer[i].draw();
			cow[i].draw();
		}
		people.draw();
	}

	~CGAME() {
		delete[] truck;
		delete[] car;
		delete ambu;
		delete[] deer;
		delete[] cow;
	}

	CPEOPLE getPeople() { return people; }

	void reset() {
		if (people.getY() < 5) {
			for (int i = 1; i < 6; i++) {
				gotoxy(1, i);
				cout << R"(                                                                                                   )";
			}
			people.draw();
			gotoxy(people.getX() + 3, people.getY());
			cout << "+100";
			Sleep(250);
			gotoxy(people.getX() + 3, people.getY());
			cout << "    ";
			people.setX(consoleWidth / 2 - 1);
			people.setY(consoleHeight - 3);
			score++;
		}
	}

	void pauseGame(HANDLE t)
	{
		SuspendThread(t);
	}

	void resumeGame(HANDLE t)
	{
		ResumeThread(t);
	}

	

	void updatePosPeople(char ch) {
		if (ch == 'A') {
			people.clear();
			people.Left(4);
		}
		else if (ch == 'W') {
			people.clear();
			people.Up(6);
		}
		else if (ch == 'D') {
			people.clear();
			people.Right(4);
		}
		else if (ch == 'S') {
			people.clear();
			people.Down(6);
		}
	}

	void updatePosVehicle() {
		if (truckTraffic.getState() == false) {
			truckTraffic.drawGreenLight(truck->getY() - 1);
			for (int i = 0; i < MAX_VEHICLE; ++i)
				truck[i].move(-1, 0);
			if (truckTraffic.updateTime() < 0) {
				truckTraffic.setState(true);
				truckTraffic.setTime(50);
			}
		}
		else {
			truckTraffic.drawRedLight(truck->getY() - 1);
			if (truckTraffic.updateTime() < 0) {
				truckTraffic.setState(false);
				truckTraffic.setTime(150);
			}
		}

		if (carTraffic.getState() == false) {
			carTraffic.drawGreenLight(car->getY() - 1);
			for (int i = 0; i < MAX_VEHICLE; ++i)
				car[i].move(-1, 0);
			if (carTraffic.updateTime() < 0) {
				carTraffic.setState(true);
				carTraffic.setTime(50);
			}
		}
		else {
			carTraffic.drawRedLight(car->getY() - 1);
			if (carTraffic.updateTime() < 0) {
				carTraffic.setTime(150 + rand() % 50);
				carTraffic.setState(false);
			}
		}
	}

	void updatePosAnimal() {
		for (int i = 0; i < MAX_ANIMAL; ++i) {
			deer[i].move(1, 0);
			cow[i].move(1, 0);
		}
	}

	bool isImpact() {
		for (int i = 0; i < MAX_VEHICLE; ++i) {
			if (truck[i].getY() == people.getY() - 1)
				if (abs(truck[i].getX() - people.getX()) < 3 || (people.getX() > truck[i].getX() && people.getX() < truck[i].getX() + 17)) {
					people.setState(0);
					return true;
				}
		}
		for (int i = 0; i < MAX_VEHICLE; ++i) {
			if (car[i].getY() == people.getY() - 1)
				if (abs(car[i].getX() - people.getX()) < 3 || (people.getX() > car[i].getX() && people.getX() < car[i].getX() + 16)) {
					people.setState(0);
					return true;
				}
		}
		for (int i = 0; i < MAX_ANIMAL; ++i) {
			if (deer[i].getY() == people.getY() - 1)
				if (abs(deer[i].getX() - people.getX()) < 2 || (people.getX() > deer[i].getX() + 1 && people.getX() < deer[i].getX() + 7)) {
					people.setState(0);
					return true;
				}
		}
		for (int i = 0; i < MAX_ANIMAL; ++i) {
			if (cow[i].getY() == people.getY() - 1)
				if (abs(cow[i].getX() - people.getX()) < 2 || (people.getX() > cow[i].getX() + 1 && people.getX() < cow[i].getX() + 15)) {
					people.setState(0);
					return true;
				}
		}
		return false;
	}

	void exitGame(HANDLE t) {
		system("cls");
		exit(0);
	}

	void drawDie() {
		ambu->setX(consoleWidth);
		ambu->setY(people.getY() - 1);
		for (int i = consoleWidth; i > -16; --i) {
			ambu->draw();
			ambu->move(-1, 0);
			Sleep(10);
		}
		system("cls");
	}

	void resetGame(int t = 0)
	{
		people.reset();
		score = t;

		srand(time(0));
		random_shuffle(p.begin(), p.end());

		for (int i = 0; i < 3; ++i) {
			int x = i * 30 + (rand() % (10));
			srand(time(0));
			truck[i].setX(10 * i + x + rand() % (5));
			truck[i].setY(p[0]);

			srand(time(0));
			car[i].setX(5 * i + x + rand() % (5));
			car[i].setY(p[1]);

			srand(time(0));
			deer[i].setX(10 * i + x + rand() % (5));
			deer[i].setY(p[2]);

			srand(time(0));
			cow[i].setX(5 * i + x + rand() % (5));
			cow[i].setY(p[3]);
		}
	}

	void drawContinue() {
		textColor(14);
		gotoxy(1, 2);
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
		gotoxy(consoleWidth / 1.5 + 3, consoleHeight / 2 - 1);
		cout << " Play again?(y/N) ";
		textColor(7);
	}

	void saveGame() {
		string fileName;
		gotoxy(101, 30);
		cout << "Enten file name: ";
		cin >> fileName;
		ofstream ofs(fileName+".txt");
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

	void listTXT()
	{
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
			gotoxy(consoleWidth / 1.5, 18 + i);
			cout << i+1 << ".              ";
		}
		for (int i = 0; i < names.size(); i++) {
			wstring a = names[i];
			gotoxy(consoleWidth / 1.5 + 3, 18 + i);
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
		gotoxy(consoleWidth/1.5, consoleHeight/2-2);
		cout << " Enter file name:          ";
		gotoxy(consoleWidth / 1.2 + 1 , consoleHeight / 2 - 2);
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

	void musicOff() {
		PlaySound(NULL, 0, 0);
	}
};

#endif