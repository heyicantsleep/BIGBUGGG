#ifndef _CGAME_H_
#define _CGAME_H_

#include "canimal.h"
#include "cpeople.h"
#include "cvehicle.h"
#include <conio.h>
#include <time.h>

class CGAME {
private:
	CTRUCK* truck;
	CCAR* car;
	CAMBU* ambu;
	CDEER* deer;
	CCOW* cow;
	CPEOPLE people;
	int score;

public:
	CGAME() {
		score = 0;
		truck = new CTRUCK[MAX_VEHICLE];
		car = new CCAR[MAX_VEHICLE];
		deer = new CDEER[MAX_ANIMAL];
		cow = new CCOW[MAX_ANIMAL];
		ambu = new CAMBU;
		srand(time(0));
		for (int i = 0; i < 3; ++i) {
			int x = i * 30 + (rand() % (10));
			truck[i].setX(10*i + x + rand() % (5));
			truck[i].setY(26);
			srand(time(0));
			car[i].setX(5*i + x + rand() % (5));
			car[i].setY(14);
			srand(time(0));
			deer[i].setX(10*i + x + rand() % (5));
			deer[i].setY(20);
			srand(time(0));
			cow[i].setX(5*i + x + rand() % (5));
			cow[i].setY(8);
		}
	}

	void speedUp(int speed) {
		if (getScore() * 5 < speed) {
			Sleep(speed - getScore() * 5);
		}
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
										         	                | Press T to loadgame   |
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
			for (int j = 0; j < (consoleWidth - 1)/11; ++j) {
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

	void Menu() {
		const string menu[] = { " New Game  ", " Load Game ", " Settings  ",
							   " Exit      " };
		int pos = 0;
		const int y = consoleHeight/2;
		const int x = consoleWidth / 1.5 + 5;
		int flag = 0;
		while (1) {
			system("cls");
			textColor(14);
			gotoxy(1, 2);
			cout << R"(
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
                                                                            \______/                                                   )";

			for (int i = 0; i < 4; ++i) {
				if (i == pos) {
					textColor(224);
					gotoxy(x, y + i);
					cout << menu[i];
					textColor(7);
				}
				else {
					gotoxy(x, y + i);
					cout << menu[i];
				}
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 'W' || key == 'w') {
						if (pos > 0) {
							pos--;
						}
						else {
							pos = 4 - 1;
						}
						break;
					}
					if (key == 'S' || key == 's') {
						if (pos < 4 - 1) {
							pos++;
						}
						else {
							pos = 0;
						}
						break;
					}
					if (key == 13) {
						switch (pos) {
						case 0: {
							system("cls");
							flag = 1;
							break;
						}
						case 1: {
							system("cls");
							flag = 1;
							break;
						}
						case 2: {
							flag = 1;
							break;
						}
						case 3: {
							system("cls");
							exit(0);
							break;
						}
						}
						break;
					}
				}
			}
			if (flag)
				break;
		}
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
		for (int i = 0; i < MAX_VEHICLE; ++i) {
			truck[i].move(-1, 0);
			car[i].move(-1, 0);
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
			Sleep(20);
			ambu->move(-1, 0);
		}
		system("cls");
	}

	void pausePanel() {
		textColor(11);
		gotoxy(114, 7);
		cout << R"(P)";
		gotoxy(119, 7);
		cout << R"(A)"; 
		gotoxy(124, 7);
		cout << R"(U)";
		gotoxy(129, 7);
		cout << R"(S)";
		gotoxy(134, 7);
		cout << R"(E)";
		textColor(7);
	}
};

#endif