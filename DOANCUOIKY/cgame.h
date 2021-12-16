#ifndef _CGAME_H_
#define _CGAME_H_

#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <conio.h>
#include "cpeople.h"
#include "canimal.h"
#include "cvehicle.h"
#include "ctraffic.h"
#include "cgraffic.h"

const int MIN_OBJECT = 2;
const int MAX_OBJECT = 3;
condition_variable cv;
char MOVING;
int SPEED = 50;
bool IS_RUNNING = true;
bool IS_PAUSE = false;
bool BLOCK_KEY = true;

using namespace std;

int pos[] = { 8, 14, 20, 26 }; // positions of the objects

class CGAME {
private:
    CTRUCK* truck;
    CCAR* car;
    CAMBULANCE* ambulance;
    CDEER* deer;
    CCOW* cow;
    CPEOPLE people;
    CTRAFFIC truckTraffic{ 100 + rand() % 50 };
    CTRAFFIC carTraffic{ 100 };
    int mScore;
    int mCount;
    int mLevel;

public:
    CGAME() {
        mScore = 0;
        mCount = 0;
        mLevel = 1;
        truck = new CTRUCK[MIN_OBJECT];
        car = new CCAR[MIN_OBJECT];
        deer = new CDEER[MIN_OBJECT];
        cow = new CCOW[MIN_OBJECT];
        ambulance = new CAMBULANCE;
        srand((unsigned)time(nullptr));
        shuffle(pos, pos + 4, std::mt19937(std::random_device()())); // randomize the positions of the objects
        for (int i = 0; i < MIN_OBJECT; ++i) { // create the objects
            int x = i * 30 + (rand() % (10));    // randomize the x position
            srand((unsigned)time(nullptr));
            truck[i].setX(30 * i + x + rand() % (10));
            truck[i].setY(pos[0]);
            srand((unsigned)time(nullptr));
            car[i].setX(30 * i + x + rand() % (10));
            car[i].setY(pos[1]);
            srand((unsigned)time(nullptr));
            deer[i].setX(20 * i + x + rand() % (10));
            deer[i].setY(pos[2]);
            srand((unsigned)time(nullptr));
            cow[i].setX(15 * i + x + rand() % (10));
            cow[i].setY(pos[3]);
        }
    }

    ~CGAME() { // destructor
        delete[] truck;
        delete[] car;
        delete ambulance;
        delete[] deer;
        delete[] cow;
    }

    static void pauseGame() {
        mutex lock;
        unique_lock<mutex> ulock(lock);
        cv.wait(ulock);
    }

    static void resumeGame() {
        cv.notify_all();
    }

    static void exitGame() {
        IS_RUNNING = false;
        system("cls");
    }

    void updateSpeed() const {          // speed up the game
        if (mCount * 4 < SPEED - 15)      // if the mScore is less than the speed
            Sleep(SPEED - mCount * 4); // sleep for the difference
        else                             // else
            Sleep(15);                      // sleep for 15 ms
    }


    static void drawMap() { // draw the map
        textColor(7); // set the color to yellow
        drawKeyGuide();
        textColor(14); // set the color to yellow

        for (int i = 0; i < MAP_HEIGHT; ++i) { // draw the map
            gotoxy(0, i);                       // set the position
            cout << char(186);          // draw the map
            gotoxy(MAP_WIDTH, i);                // set the position
            cout << char(186);          // draw the map
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
    }

    void levelUp() {
        if ((mCount / 3) == mLevel) {
            mLevel++;
            randomPos();
            system("cls");
            drawMap();
        }
    }

    void drawScore() const {
        textColor(11);
        asci(mScore * 10);
        textColor(14);
    }

    static void clearScore() {
        for (int i = 0; i < 7; i++) {
            gotoxy(MAP_WIDTH + 7, 6 + i);
            cout
                << R"(                                   )";
        }
    }

    void updateScore() {
        mScore += mLevel;
        mCount++;
    }

    void updatePeoplePos() {             // reset the game
        for (int i = 3; i < 6; ++i) {
            gotoxy(1, i);
            cout
                << R"(                                                                                                   )";
        }
        people.draw();
        gotoxy(people.getX() + 3, people.getY());
        cout << "+" << mLevel * 10;
        Sleep(150);
        gotoxy(people.getX() + 3, people.getY());
        cout << "     ";
        people.setX(MAP_WIDTH / 2 - 1);
        people.setY(MAP_HEIGHT - 3); // reset the people

    }

    void drawGame() {                        // draw the game
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            deer[i].draw();                      // draw the deer
            cow[i].draw();                       // draw the cow
        }
        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            truck[i].draw();                     // draw the truck
            car[i].draw();                       // draw the car
        }
        people.draw(); // draw the people
    }

    inline CPEOPLE getPeople() { return people; } // get the people

    void updatePosPeople(char ch) { // update the position of the people
        if (ch == 'A') {              // if the key is A
            people.clear();             // clear the people
            people.Left(4);             // move the people to the left
        }
        else if (ch == 'D') {       // if the key is D
            people.clear();             // clear the people
            people.Right(4);            // move the people to the right
        }
        else if (ch == 'W') {       // if the key is W
            people.clear();             // clear the people
            people.Up(6);               // move the people to the up
        }
        else if (ch == 'S') {       // if the key is S
            people.clear();             // clear the people
            people.Down(6);             // move the people to the down
        }
    }

    void updatePosVehicle() { // update the position of the vehicle
        if (!truckTraffic.getState()) {           // if the truck moving
            if (truckTraffic.getTime() > 30)
                truckTraffic.drawGreenLight(truck->getY() - 1); // draw the green light
            else
                truckTraffic.drawYellowLight(truck->getY() - 1);
            for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i)            // for each object
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
                truckTraffic.setTime(100);                  // set the time to 150
            }
        }

        if (!carTraffic.getState()) {         // if the car moving
            if (carTraffic.getTime() > 30)
                carTraffic.drawGreenLight(car->getY() - 1); // draw the green light
            else
                carTraffic.drawYellowLight(car->getY() - 1);
            for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i)        // for each object
                car[i].move(1, 0);                       // move the car
            if (carTraffic.updateTime() < 0) {          // if the time is up
                carTraffic.setState(true);                // set the state to true
                carTraffic.setTime(50);                   // set the time to 50
            }
        }
        else {
            carTraffic.drawRedLight(car->getY() - 1); // draw the red light
            if (carTraffic.updateTime() < 0) {        // if the time is up
                carTraffic.setState(false);      // set the state to false
                carTraffic.setTime(100 +
                    rand() % 50); // set the time to 150 + random number
            }
        }
    }

    void updatePosAnimal() {                 // update the position of the animal
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            deer[i].move(-1, 0);                  // move the deer
            cow[i].move(1, 0);                   // move the cow
        }
    }

    bool isImpact() {                        // check if the people hit the object
        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            if (truck[i].getY() ==
                people.getY() -
                1) // if the truck is on the same line	with the people
                if (abs(truck[i].getX() - people.getX()) < 3 ||
                    (people.getX() > truck[i].getX() &&
                        people.getX() <
                        truck[i].getX() + truck[i].getLength())) { // if the people is in the truck
                    people.setState(false);             // set the state to 0
                    return true;                    // return true
                }
            if (car[i].getY() == people.getY() - 1) // if the car is on the same line
                if (abs(car[i].getX() - people.getX()) < 2 ||
                    (people.getX() > car[i].getX() &&
                        people.getX() <
                        car[i].getX() + car[i].getLength() + 1)) { // if the people is in the car
                    people.setState(false);           // set the state to 0
                    return true;                  // return true
                }
        }
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) {
            if (deer[i].getY() ==
                people.getY() - 1) // if the deer is on the same line
                if (abs(deer[i].getX() - people.getX()) < 3 ||
                    (people.getX() > deer[i].getX() + 1 &&
                        people.getX() <
                        deer[i].getX() + deer[i].getLength())) { // if the people is in the deer
                    people.setState(false);           // set the state to 0
                    return true;                  // return true
                }
            if (cow[i].getY() == people.getY() - 1) // if the cow is on the same line
                if (abs(cow[i].getX() - people.getX()) < 2 ||
                    (people.getX() > cow[i].getX() + 1 &&
                        people.getX() <
                        cow[i].getX() + cow[i].getLength() + 1)) { // if the people is in the cow
                    people.setState(false);           // set the state to 0
                    return true;                  // return true
                }
        }
        return false; // return false
    }

    void drawDie() {                      //	draw the ambulance
        ambulance->setX(MAP_WIDTH);          // set the x position to the map width
        ambulance->setY(people.getY() - 1); // set the y position to the people
        for (int i = MAP_WIDTH; i > -ambulance->getLength(); --i) { // for each x position
            ambulance->draw();                   // draw the ambulance
            ambulance->move(-1, 0);              // move the ambulance
            Sleep(10);                           // sleep for 10 ms
        }
        system("cls"); // clear the screen
    }

    void resetGame() { // reset the game
        people.reset();           // reset the people
        mScore = 0;                // set the mScore to t
        mCount = 0;
        mLevel = 1;
        randomPos();
    }

    void randomPos() {
        if (mLevel == 2) {
            delete[] deer;
            delete[] cow;
            deer = new CDEER[MAX_OBJECT];
            cow = new CCOW[MAX_OBJECT];
        }
        if (mLevel == 3) {
            delete[] truck;
            delete[] car;
            truck = new CTRUCK[MAX_OBJECT];
            car = new CCAR[MAX_OBJECT];
        }
        srand((unsigned)time(nullptr));                         // randomize the seed
        shuffle(pos, pos + 4, std::mt19937(std::random_device()())); // randomize the position

        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            int x = i * 30 + (rand() % (10));    // randomize the x position
            srand((unsigned)time(nullptr));                      // randomize the seed
            truck[i].setX(10 * i + x +
                rand() % (5)); // set the x position of the truck
            truck[i].setY(pos[0]);         // set the y position of the truck

            srand((unsigned)time(nullptr));                        // randomize the seed
            car[i].setX(5 * i + x + rand() % (5)); // set the x position of the car
            car[i].setY(pos[1]);
        }                     // set the y position of the car
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            int x = i * 30 + (rand() % (10));    // randomize the x position
            srand((unsigned)time(nullptr));                          // randomize the seed
            deer[i].setX(10 * i + x + rand() % (5)); // set the x position of the deer
            deer[i].setY(pos[2]);                      // set the y position of the deer

            srand((unsigned)time(nullptr));                        // randomize the seed
            cow[i].setX(5 * i + x + rand() % (5)); // set the x position of the cow
            cow[i].setY(pos[3]);                     // set the y position of the cow
        }
    }

    static void playAgainMsg() { // draw the continue
        textColor(14);      // set the text color to yellow
        drawGameOver();
        gotoxy(CONSOLE_WIDTH / 2 - 9, MAP_HEIGHT / 2 + 2); // set the position
        textColor(8);      // set the text color to yellow
        cout << " Play again?(y/N) ";                  // print the message
        textColor(15); // set the text color to white
    }

    void saveGame() {
        system("cls");
        drawGameTitle();
        string fileName;
        textColor(6);
        gotoxy(CONSOLE_WIDTH / 2 - 4, MAP_HEIGHT / 2 - 2);
        cout << "SAVE GAME";
        gotoxy(CONSOLE_WIDTH / 2 - 13, MAP_HEIGHT / 2);
        textColor(224);
        cout << "  Enter file name:          ";
        int index = 0;
        textColor(224);
        while (true) {
            if (_kbhit()) {
                gotoxy(CONSOLE_WIDTH / 2 + 6 + index, MAP_HEIGHT / 2);
                char ch = _getch();
                if (ch == 27) {
                    textColor(15);
                    return;
                }
                else if (ch == 13)
                    break;
                else if (ch == 8) {
                    if (index > 0) {
                        --index;
                        gotoxy(CONSOLE_WIDTH / 2 + 6 + index, MAP_HEIGHT / 2);
                        cout << " ";
                        if (!fileName.empty())
                            fileName.pop_back();
                    }
                }
                else {
                    gotoxy(CONSOLE_WIDTH / 2 + 6 + index, MAP_HEIGHT / 2);
                    ++index;
                    cout << ch;
                    fileName.push_back(ch);
                }
            }
        }
        textColor(15);
        ofstream ofs(fileName + ".txt");
        ofs << people.getX() << " " << people.getY() << endl;
        ofs << mScore << endl;
        ofs << mLevel << endl;
        ofs << mCount << endl;
        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); i++) {
            ofs << truck[i].getX() << " " << truck[i].getY() << endl;
            ofs << car[i].getX() << " " << car[i].getY() << endl;
        }
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); i++) {
            ofs << cow[i].getX() << " " << cow[i].getY() << endl;
            ofs << deer[i].getX() << " " << deer[i].getY() << endl;
        }
        ofs << truckTraffic.getTime() << " " << truckTraffic.getState() << endl;
        ofs << carTraffic.getTime() << " " << carTraffic.getState() << endl;
    }

    bool loadGame() {
        listTXT();
        string fileName;
        textColor(6);
        gotoxy(CONSOLE_WIDTH / 2 - 4, MAP_HEIGHT / 2 - 2);
        cout << "LOAD GAME";
        textColor(224);
        gotoxy(CONSOLE_WIDTH / 2 - 13, MAP_HEIGHT / 2);
        cout << "  Enter file name:           ";
        int index = 0;
        while (true) {
            if (_kbhit()) {
                gotoxy(CONSOLE_WIDTH / 2 + 6 + index, MAP_HEIGHT / 2);
                char ch = _getch();
                if (ch == 27)
                {
                    textColor(15);
                    return false;
                }
                else if (ch == 13)
                    break;
                else if (ch == 8) {
                    if (index > 0) {
                        --index;
                        gotoxy(CONSOLE_WIDTH / 2 + 6 + index, MAP_HEIGHT / 2);
                        cout << " ";
                        if (!fileName.empty())
                            fileName.pop_back();
                    }
                }
                else {
                    gotoxy(CONSOLE_WIDTH / 2 + 6 + index, MAP_HEIGHT / 2);
                    ++index;
                    cout << ch;
                    fileName.push_back(ch);
                }
            }
        }
        textColor(15);
        fileName += ".txt";
        ifstream ifs(fileName);
        if (ifs) {
            int x, y;
            ifs >> x >> y;
            people.setX(x);
            people.setY(y);
            ifs >> mScore;
            ifs >> mLevel;
            ifs >> mCount;
            delete[]truck;
            delete[]car;
            delete[]cow;
            delete[]deer;
            truck = new CTRUCK[(mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT)];
            car = new CCAR[(mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT)];
            cow = new CCOW[(mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT)];
            deer = new CDEER[(mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT)];
            for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) {
                ifs >> x >> y;
                truck[i].setX(x);
                truck[i].setY(y);
                ifs >> x >> y;
                car[i].setX(x);
                car[i].setY(y);
            }
            for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) {
                ifs >> x >> y;
                cow[i].setX(x);
                cow[i].setY(y);
                ifs >> x >> y;
                deer[i].setX(x);
                deer[i].setY(y);
            }
            ifs >> x >> y;
            truckTraffic.setTime(x);
            truckTraffic.setState(y);
            ifs >> x >> y;
            carTraffic.setState(y);
            carTraffic.setTime(x);
        }
        return true;
    }

    static void drawPause() {
        system("cls");
        drawGameTitle();
        textColor(6);
        gotoxy(73, CONSOLE_HEIGHT / 2);
        cout << "PAUSE";
        textColor(8);
        gotoxy(62, CONSOLE_HEIGHT / 2 + 1);
        cout << "(Press any key to continue)";
        textColor(14);
    }
};

#endif