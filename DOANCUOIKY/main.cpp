#pragma comment(lib, "winmm.lib")
#include "cgame.h"
#include <conio.h>
#include <thread>

CGAME* cg = new CGAME(); // create game object

void SubThread()
{
    while (IS_RUNNING) { // run game
        if (!cg->getPeople().isDead()) { // if player is not dead
            if (IS_PAUSE) // if game is pause
                CGAME::pauseGame(); // pause game
            cg->updatePosPeople(MOVING); // update position of player
            MOVING = ' '; // stop moving
            cg->updatePosVehicle(); // update position of vehicle
            cg->updatePosAnimal(); // update position of animal
            cg->drawGame(); // draw game
            cg->isImpact(); // check impact
            cg->updateSpeed(); // update speed of object
            if (cg->getPeople().isFinish()) { // if player is cross the road
                CGAME::clearScore(); // clear score
                cg->updateScore(); // update score
                cg->updatePeoplePos(); // update position of player
                cg->levelUp(); // level up
            }
            cg->drawScore(); // draw score
            if (cg->getPeople().isDead()) { // if player is dead
                cg->drawDie(); // draw die animation
                CGAME::playAgainMsg(); // draw play again message
                BLOCK_KEY = false; // allow press key
            }
        }
    }
}

void startGame(thread& t1)
{
    while (true) {
        char temp = toupper(_getch()); // get key
        if (!cg->getPeople().isDead()) { // if player is not dead
            if (temp == 27) { // if press ESC
                IS_RUNNING = false; // stop game
                t1.join(); // wait thread to finish
                cg->resetGame(); // reset game
                break; // break
            }
            else if (temp == 'P') { // if press P
                IS_PAUSE = true; // pause game
                Sleep(100); // sleep 100ms
                CGAME::drawPause(); // draw pause message
            }
            else if (temp == 'L') { // if press L
                IS_PAUSE = true; // pause game
                Sleep(100); // sleep 100ms
                cg->saveGame(); // save game
                system("cls"); // clear screen
                CGAME::drawMap(); // draw map
                CGAME::resumeGame(); // resume game
                IS_PAUSE = false; // resume game
            }
            else if (temp == 'T') { // if press T
                IS_PAUSE = true; // pause game
                Sleep(100); // sleep 100ms
                system("cls"); // clear screen
                drawGameTitle(); // draw game title
                cg->loadGame(); // load game
                system("cls"); // clear screen
                CGAME::drawMap(); // draw map
                CGAME::resumeGame(); // resume game
                IS_PAUSE = false; // resume game
            }
            else {
                if (IS_PAUSE) { // if game is pause
                    system("cls"); // clear screen
                    CGAME::drawMap(); // draw map
                    CGAME::resumeGame(); // resume game
                    IS_PAUSE = false; // resume game
                }
                MOVING = temp; // set moving
            }
        }
        else {
            if (!BLOCK_KEY) { // if allow press key
                if (temp == 'Y') { // if press Y
                    cg->resetGame(); // reset game
                    system("cls"); // clear screen
                    Sleep(20); // sleep 20ms
                    CGAME::drawMap(); // draw map
                }
                else {
                    IS_RUNNING = false; // stop game
                    t1.join(); // wait thread to finish
                    cg->resetGame(); // reset game
                    break; // break
                }
                BLOCK_KEY = true; // block press key
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); // disable sync with stdio
    cin.tie(nullptr); // disable cin tie
    cout.tie(nullptr); // disable cout tie
    fixConsole(); // hide console zoom button
    resizeConsole(1120, 630); // resize console
    hideCursor(); // hide cursor
    PlaySound(TEXT("song1.wav"), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
    const string menu[] = { "  New Game   ", "  Load Game  ", "  Settings   ",
        "  Exit       " }; // game menu
    const string songMenu[] = { "  Mute              ", "  Tornado Of Souls  ", "  You Say Run       ", "  Back              " }; // song menu
    const int y = CONSOLE_HEIGHT / 2; // y of menu
    const int x = CONSOLE_WIDTH / 2 - 6; // x of menu
    int posMenu = 0; // position of menu
    int posSong = 0; // position of song menu
    while (true) {
        system("cls"); // clear screen
        textColor(14); // set text color to yellow
        drawGameTitle(); // draw game title
        textColor(6); // set text color to yellow
        gotoxy(CONSOLE_WIDTH / 2 - 4, CONSOLE_HEIGHT / 2 - 2); // set cursor to center of map
        cout << "MAIN MENU"; // draw main menu
        for (int i = 0; i < 4; ++i) { // draw menu
            if (i == posMenu) { // if position of menu is equal to posMenu
                textColor(224); // set background color to yellow
                gotoxy(x, y + i); // set cursor to position of menu
                cout << menu[i]; // draw menu
                textColor(15); // set text color to white
            }
            else {
                gotoxy(x, y + i); // set cursor to position of menu
                textColor(14); // set text color to yellow
                cout << menu[i]; // draw menu
            }
        }
        while (true) {
            if (_kbhit()) { // if press key
                char keyMenu = toupper(_getch()); // get key
                if (keyMenu == 'W') { // if press W
                    if (posMenu > 0) // if position of menu is not equal to 0
                        --posMenu; // decrease position of menu
                    else // if position of menu is equal to 0
                        posMenu = 3; // set position of menu to 3
                    break; // break
                }
                if (keyMenu == 'S') { // if press S
                    if (posMenu < 3) // if position of menu is not equal to 3
                        ++posMenu; // increase position of menu
                    else // if position of menu is equal to 3
                        posMenu = 0; // set position of menu to 0
                    break; // break
                }
                if (keyMenu == 13) { // if press ENTER
                    switch (posMenu) { // switch position of menu
                    case 0: { // if position of menu is equal to 0
                        system("cls"); // clear screen
                        CGAME::drawMap(); // draw map
                        IS_RUNNING = true; // start game
                        thread t1(SubThread); // create thread
                        startGame(t1); // start game
                        break; // break
                    }
                    case 1: {
                        if (cg->loadGame()) { // if load game success
                            system("cls"); // clear screen
                            CGAME::drawMap(); // draw map
                            IS_RUNNING = true; // start game
                            thread t1(SubThread); // create thread
                            startGame(t1); // start game
                        }
                        textColor(15); // set text color to white
                        break; // break
                    }
                    case 2: { // if position of menu is equal to 2
                        while (true) {
                            textColor(6); // set text color to yellow
                            gotoxy(CONSOLE_WIDTH / 2 - 7, MAP_HEIGHT / 2 - 2); // set cursor to center of map
                            cout << "AUDIO SETTINGS"; // draw audio settings
                            for (int j = 0; j < 4; ++j) { // draw song menu
                                if (j == posSong) { // if position of song menu is equal to posSong
                                    textColor(224); // set background color to yellow
                                    gotoxy(x - 3, y + j); // set cursor to position of song menu
                                    cout << songMenu[j]; // draw song menu
                                    textColor(15); // set text color to white
                                }
                                else {
                                    gotoxy(x - 3, y + j); // set cursor to position of song menu
                                    textColor(14); // set text color to yellow
                                    cout << songMenu[j]; // draw song menu
                                }
                            }
                            while (true) {
                                if (_kbhit()) { // if press key
                                    char keySong = toupper(_getch()); // get key
                                    if (keySong == 'W') { // if press W
                                        if (posSong > 0) // if position of song menu is not equal to 0
                                            --posSong; // decrease position of song menu
                                        else // if position of song menu is equal to 0
                                            posSong = 3; // set position of song menu to 3
                                        break;
                                    }
                                    else if (keySong == 'S') { // if press S
                                        if (posSong < 3) // if position of song menu is not equal to 3
                                            posSong++; // increase position of song menu
                                        else // if position of song menu is equal to 3
                                            posSong = 0; // set position of song menu to 0
                                        break;
                                    }
                                    if (keySong == 13) { // if press ENTER
                                        switch (posSong) { // switch position of song menu
                                        case 0: { // if position of song menu is equal to 0
                                            PlaySound(nullptr, nullptr, 0); // stop song
                                            break; // break
                                        }
                                        case 1: { // if position of song menu is equal to 1
                                            PlaySound(TEXT("song1.wav"), nullptr,
                                                SND_FILENAME | SND_ASYNC | SND_LOOP); // play song number 1
                                            break; // break
                                        }
                                        case 2: { // if position of song menu is equal to 2
                                            PlaySound(TEXT("song2.wav"), nullptr,
                                                SND_FILENAME | SND_ASYNC | SND_LOOP); // play song number 2
                                            break;
                                        }
                                        case 3: { // if position of song menu is equal to 3
                                            IS_EXIT = true; // exit game
                                            break;
                                        }
                                        default:
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                            if (IS_EXIT) { // if exit game
                                IS_EXIT = false; // set exit game to false
                                break; // break
                            }
                        }
                        system("cls"); // clear screen
                        break; // break
                    }
                    case 3: { // if position of menu is equal to 3
                        CGAME::exitGame(); // exit game
                        IS_EXIT = true; // set exit game to true
                        break; // break
                    }
                    default:
                        break;
                    } break;
                }
            }
        }
        if (IS_EXIT) { // if exit game
            break; // break
        }
    }
    delete cg; // free memory
    return EXIT_SUCCESS; // return success
}
