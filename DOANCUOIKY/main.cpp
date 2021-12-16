#pragma comment(lib, "winmm.lib")
#include "cgame.h"
#include <conio.h>
#include <thread>

CGAME* cg = new CGAME();

void SubThread() {
    while (IS_RUNNING) {
        if (!cg->getPeople().isDead()) {
            if (IS_PAUSE)
                CGAME::pauseGame();
            cg->updatePosPeople(MOVING);
            MOVING = ' ';
            cg->updatePosVehicle();
            cg->updatePosAnimal();
            cg->drawGame();
            cg->isImpact();
            cg->updateSpeed();
            if (cg->getPeople().isFinish()) {
                CGAME::clearScore();
                cg->updateScore();
                cg->updatePeoplePos();
                cg->levelUp();
            }
            cg->drawScore();
            if (cg->getPeople().isDead()) {
                cg->drawDie();
                CGAME::playAgainMsg();
                BLOCK_KEY = false;
            }

        }
    }
}


void startGame(thread& t1) {
    while (true) {
        char temp = toupper(_getch());
        if (!cg->getPeople().isDead()) {
            if (temp == 27) {
                IS_RUNNING = false;
                t1.join();
                cg->resetGame();
                break;
            }
            else if (temp == 'P') {
                IS_PAUSE = true;
                Sleep(100);
                CGAME::drawPause();
            }
            else if (temp == 'L') {
                IS_PAUSE = true;
                Sleep(100);
                cg->saveGame();
                system("cls");
                CGAME::drawMap();
                CGAME::resumeGame();
                IS_PAUSE = false;
            }
            else {
                if (IS_PAUSE) {
                    system("cls");
                    CGAME::drawMap();
                    CGAME::resumeGame();
                    IS_PAUSE = false;
                }
                MOVING = temp;
            }
        }
        else {
            if (!BLOCK_KEY) {
                if (temp == 'Y') {
                    cg->resetGame();
                    system("cls");
                    Sleep(20);
                    CGAME::drawMap();
                }
                else {
                    IS_RUNNING = false;
                    t1.join();
                    cg->resetGame();
                    break;
                }
                BLOCK_KEY = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    fixConsole();
    resizeConsole(1120, 630);
    hideCursor();
    PlaySound(TEXT("song1.wav"), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
    const string menu[] = { "  New Game   ", "  Load Game  ", "  Settings   ",
                            "  Exit       " };
    const string songMenu[] = { "  Mute              ", "  Tornado Of Souls  ", "  You Say Run       ", "  Back              " };
    const int y = MAP_HEIGHT / 2;
    const int x = CONSOLE_WIDTH / 2 -6;
    int posMenu = 0;
    int posSong = 0;
    bool IS_EXIT = false;
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
                        CGAME::drawMap();
                        IS_RUNNING = true;
                        thread t1(SubThread);
                        startGame(t1);
                        break;
                    }
                    case 1: {
                        if (cg->loadGame()) {
                            system("cls");
                            CGAME::drawMap();
                            IS_RUNNING = true;
                            thread t1(SubThread);
                            startGame(t1);
                        }
                        textColor(7);
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
                                            PlaySound(nullptr, nullptr, 0);
                                            break;
                                        case 1:
                                            PlaySound(TEXT("song1.wav"), nullptr,
                                                SND_FILENAME | SND_ASYNC | SND_LOOP);
                                            break;
                                        case 2:
                                            PlaySound(TEXT("song2.wav"), nullptr,
                                                SND_FILENAME | SND_ASYNC | SND_LOOP);
                                            break;
                                        case 3:
                                            IS_EXIT = true;
                                            break;
                                        default: break;
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
                    case 3: {
                        CGAME::exitGame();
                        IS_EXIT = true;
                        break;
                    }
                    default: break;
                    }
                    break;
                }
            }
        }
        if (IS_EXIT) {
            break;
        }
    }
    delete cg;
    return EXIT_SUCCESS;
}