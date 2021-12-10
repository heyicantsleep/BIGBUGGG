#pragma comment(lib, "winmm.lib")
#include "cgame.h"
#include <thread>

CGAME cg;
char MOVING;
int speed = 50;

void SubThread()
{
	while (!cg.getPeople().isDead())
	{
		cg.updatePosPeople(MOVING);
		MOVING = ' ';
		cg.printScore();
		cg.updatePosVehicle();//Cập nhật vị trí xe
		cg.updatePosAnimal(); //Cập nhật vị trí thú
		cg.drawGame();
		cg.isImpact();
		if (cg.getPeople().isDead()) {
			cg.drawDie();
		}
		cg.reset();
		cg.speedUp(speed);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fixConsole();
	resizeConsole(1100, 630);
	hideCursor();
	system("cls");
	char temp;
	bool key = 0;
	cg.Menu();
	PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cg.drawMap();
	thread t1(SubThread);
	while (true)
	{
		temp = toupper(_getch());
		if (!cg.getPeople().isDead())
		{
			if (temp == 27)
			{
				cg.exitGame(t1.native_handle());
			}
			else if (temp == 'P')
			{
				cg.pauseGame(t1.native_handle());
				key = 1;
				cg.pausePanel();
			}
			else if (temp == 'L')
			{
				cg.pauseGame(t1.native_handle());
				//cg->saveGame();
			}
			else if (temp == 'T')
			{
				//mciSendStringA("stop nen.mp3", 0, NULL, 0);
				//cg->pauseGame(t1.native_handle());
				//system("cls");
				//cg->loadGame();
				//cg->startGame();
				//cg->drawGame();
				//mciSendStringA("play nen.mp3", 0, NULL, 0);
			}
			else
			{
				if (key == 1) {
					cg.drawMap();
					key = 0;
				}
				cg.resumeGame((HANDLE)t1.native_handle());
				MOVING = temp; //Cập nhật bước di chuyển
			}
		}
	}
}