#pragma comment(lib, "winmm.lib")
#include "cgame.h"
#include <thread>

CGAME cg;
char MOVING;
int speed = 50;

void SubThread()
{
	while (1) {
		while (!cg.getPeople().isDead())
		{
			cg.updatePosPeople(MOVING);
			MOVING = ' ';
			cg.printScore();
			cg.updatePosVehicle();//Cập nhật vị trí xe
			cg.updatePosAnimal(); //Cập nhật vị trí thú
			cg.drawGame();
			cg.isImpact();
			cg.reset();
			cg.speedUp(speed);
			if (cg.getPeople().isDead()) {
				cg.drawDie();
				cg.drawContinue();
			}
		}
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
	PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cg.Menu();
	thread t1(SubThread);
	while (true)
	{
		temp = toupper(_getch());
		if (!cg.getPeople().isDead())
		{
			if (temp == 27)
			{
				system("cls");
				cg.exitGame(t1.native_handle());
			}
			else if (temp == 'P')
			{
				cg.pauseGame(t1.native_handle());
			}
			else if (temp == 'L')
			{
				cg.pauseGame(t1.native_handle());
				cg.saveGame();
				system("cls");
				cg.drawMap();
				cg.resumeGame((HANDLE)t1.native_handle());
			}
			else
			{
				cg.resumeGame((HANDLE)t1.native_handle());
				MOVING = temp; //Cập nhật bước di chuyển
			}
		}
		else {
			if (temp == 'Y') {
				system("cls");
				cg.drawMap();
				cg.resetGame();
			}
			else {
				exit(0);
			}
		}
	}
}