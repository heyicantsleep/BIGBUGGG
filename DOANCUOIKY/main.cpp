#pragma comment(lib, "winmm.lib")
#include "cgame.h"
#include <conio.h>
#include <thread>

CGAME cg;
char MOVING;
int speed = 50;
bool IS_RUNNING = true;
bool IS_PAUSE = false;
bool IS_DRAW_PAUSE = false;
bool BLOCK_KEY = true;

void SubThread() {
	while (IS_RUNNING) {
		if (!cg.getPeople().isDead()) {
			if (IS_PAUSE)
				cg.pauseGame();
			cg.updatePosPeople(MOVING);
			MOVING = ' ';
			cg.updatePosVehicle();
			cg.updatePosAnimal();
			cg.drawGame();
			cg.isImpact();
			cg.setSpeed(speed);
			if (cg.getPeople().isFinish()) {
				cg.clearScore();
				cg.updateScore();
				cg.updatePeoplePos();
				cg.levelUp();
			}
			cg.drawScore();
			if (cg.getPeople().isDead()) {
				cg.drawDie();
				cg.playAgainMsg();
				BLOCK_KEY = false;
			}

		}
	}
}


void startGame(thread& t1) {
	while (true) {
		char temp = toupper(_getch());
		if (!cg.getPeople().isDead()) {
			if (temp == 27) {
				IS_RUNNING = false;
				t1.join();
				cg.resetGame();
				break;
			}
			else if (temp == 'P') {
				IS_PAUSE = true;
				IS_DRAW_PAUSE = true;
				Sleep(100);
				cg.drawPause();
			}
			else if (temp == 'L') {
				IS_PAUSE = true;
				Sleep(100);
				cg.saveGame();
				system("cls");
				cg.drawMap();
				cg.resumeGame();
				IS_PAUSE = false;
			}
			else {
				if (IS_DRAW_PAUSE) {
					system("cls");
					cg.drawMap();
					IS_DRAW_PAUSE = false;
				}
				if (IS_PAUSE) {
					cg.resumeGame();
					IS_PAUSE = false;
				}
				MOVING = temp;
			}
		}
		else {
			if (!BLOCK_KEY) {
				if (temp == 'Y') {
					cg.resetGame();
					system("cls");
					Sleep(20);
					cg.drawMap();
				}
				else {
					IS_RUNNING = false;
					t1.join();
					cg.resetGame();
					break;
				}
				BLOCK_KEY = true;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fixConsole();
	resizeConsole(1120, 630);
	hideCursor();
	PlaySound(TEXT("song1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	const string menu[] = { "  New Game   ", "  Load Game  ", "  Settings   ",
						   "  Exit       " };
	const string songMenu[] = { "  Mute              ", "  Tornado Of Souls  ", "  You Say Run       ", "  Back              " };
	const int y = MAP_HEIGHT / 2;
	const int x = MAP_WIDTH / 1.5 + 3;
	int posMenu = 0;
	int posSong = 0;
	bool IS_EXIT = 0;
	while (true) {
		system("cls");
		textColor(14);
		drawGameTitle();
		for (int i = 0; i < 4; ++i) {
			if (i == posMenu) {
				textColor(224);
				gotoxy(x, y + i);
				cout << menu[i];
				textColor(7);
			}
			else {
				gotoxy(x, y + i);
				textColor(14);
				cout << menu[i];
			}
		}
		while (true) {
			if (_kbhit()) {
				char keyMenu = toupper(_getch());
				if (keyMenu == 'W') {
					if (posMenu > 0) 
						--posMenu;
					else 
						posMenu = 3;
					break;
				}
				if (keyMenu == 'S') {
					if (posMenu < 3) 
						++posMenu;
					else 
						posMenu = 0;
					break;
				}
				if (keyMenu == 13) {
					switch (posMenu) {
					case 0: {
						system("cls");
						cg.drawMap();
						IS_RUNNING = true;
						thread t1(SubThread);
						startGame(t1);
						break;
					}
					case 1: {
						cg.loadGame();
						system("cls");
						cg.drawMap();
						IS_RUNNING = true;
						thread t1(SubThread);
						startGame(t1);
						break;
					}
					case 2: {
						while (true) {
							for (int j = 0; j < 4; ++j) {
								if (j == posSong) {
									textColor(224);
									gotoxy(x - 3, y + j);
									cout << songMenu[j];
									textColor(7);
								}
								else {
									gotoxy(x - 3, y + j);
									textColor(14);
									cout << songMenu[j];
								}
							}
							while (true) {
								if (_kbhit()) {
									char keySong = toupper(_getch());
									if (keySong == 'W') {
										if (posSong > 0) 
											--posSong;
										else 
											posSong = 3;
										break;
									}
									else if (keySong == 'S') {
										if (posSong < 3) 
											posSong++;
										else 
											posSong = 0;
										break;
									}
									if (keySong == 13) {
										switch (posSong) {
										case 0:
											PlaySound(NULL, 0, 0);
											break;
										case 1:
											PlaySound(TEXT("song1.wav"), NULL,
												SND_FILENAME | SND_ASYNC | SND_LOOP);
											break;
										case 2:
											PlaySound(TEXT("song2.wav"), NULL,
												SND_FILENAME | SND_ASYNC | SND_LOOP);
											break;
										case 3:
											IS_EXIT = true;
											break;
										}
									}
									break;
								}
							}
							if (IS_EXIT) {
								IS_EXIT = false;
								break;
							}
						}
						system("cls");
						break;
					}
						  break;
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
	}
}