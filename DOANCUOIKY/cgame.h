#ifndef _CGAME_H_
#define _CGAME_H_

#include "api.h"
#include "canimal.h"
#include "cgraphic.h"
#include "cpeople.h"
#include "ctraffic.h"
#include "cvehicle.h"
#include <Windows.h>
#include <algorithm>
#include <condition_variable>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <random>
#include <vector>

const int MIN_OBJECT = 2;
const int MAX_OBJECT = 3;

condition_variable cv;
char MOVING;
int SPEED = 50;
bool IS_RUNNING = true;
bool IS_PAUSE = false;
bool IS_EXIT = false; // exit game
bool BLOCK_KEY = true;

using namespace std;

int pos[] = { 8, 14, 20, 26 }; // y positions of the objects

class CGAME {
private:
    CTRUCK* truck; // pointer to the truck
    CCAR* car; // pointer to the car
    CAMBULANCE* ambulance; // pointer to the ambulance
    CCOW* cow; // pointer to the cow
    CDEER* deer; // pointer to the deer
    CPEOPLE people; // people
    CTRAFFIC truckTraffic{ 100 + rand() % 50 }; // traffic of the truck
    CTRAFFIC carTraffic{ 100 }; // traffic of the car
    int mScore; // score
    int mCount; // count time people cross the road
    int mLevel; // level

public:
    CGAME() // constructor
    {
        mScore = 0; // set score to 0
        mCount = 0; // set count to 0
        mLevel = 1; // set level to 1
        truck = new CTRUCK[MIN_OBJECT]; // create an array of truck
        car = new CCAR[MIN_OBJECT]; // create an array of car
        cow = new CCOW[MIN_OBJECT]; // create an array of cow
        deer = new CDEER[MIN_OBJECT]; // create an array of deer
        ambulance = new CAMBULANCE; // create an ambulance
        srand((unsigned)time(nullptr)); // set seed for random
        shuffle(pos, pos + 4, std::mt19937(std::random_device()())); // randomize the y positions of the objects
        for (int i = 0; i < MIN_OBJECT; ++i) { // for each object
            int x = i * 30 + (rand() % (10)); // randomize the x position

            srand((unsigned)time(nullptr)); // set seed for random
            truck[i].setX(30 * i + x + rand() % (10)); // randomize the x position of the truck
            truck[i].setY(pos[0]); // set the y position of the truck

            srand((unsigned)time(nullptr)); // set seed for random
            car[i].setX(30 * i + x + rand() % (10)); // randomize the x position of the car
            car[i].setY(pos[1]); // set the y position of the car

            srand((unsigned)time(nullptr)); // set seed for random
            cow[i].setX(15 * i + x + rand() % (10)); // randomize the x position of the cow
            cow[i].setY(pos[3]); // set the y position of the cow

            srand((unsigned)time(nullptr)); // set seed for random
            deer[i].setX(20 * i + x + rand() % (10)); // randomize the x position of the deer
            deer[i].setY(pos[2]); // set the y position of the deer
        }
    }

    ~CGAME() // destructor
    {
        delete[] truck; // delete truck array
        delete[] car; // delete car array
        delete ambulance; // delete ambulance
        delete[] deer; // delete deer array
        delete[] cow; // delete cow array
    }

    static void pauseGame() // pause the game
    {
        mutex lock;
        unique_lock<mutex> ulock(lock);
        cv.wait(ulock); // wait for the signal
    }

    static void resumeGame() // resume the game
    {
        cv.notify_all(); // notify the waiting thread
    }

    static void exitGame() // exit the game
    {
        IS_RUNNING = false; // set running to false
        system("cls"); // clear the screen
    }

    void updateSpeed() const // update the speed
    {
        if (mCount * 4 < SPEED - 15) // if the count is less than the speed - 15
            Sleep(SPEED - mCount * 4); // sleep for the remaining time
        else // if the count is greater than the speed - 15
            Sleep(15); // sleep for 15 ms
    }

    static void drawMap() // draw the map
    {
        textColor(7); // set the color to white
        drawKeyGuide(); // draw the key guide
        textColor(14); // set the color to yellow

        for (int i = 0; i < MAP_HEIGHT; ++i) { // draw the map
            gotoxy(0, i); // set the cursor to the position
            cout << char(186); // draw the top border
            gotoxy(MAP_WIDTH, i); // set the cursor to the position of the bottom border
            cout << char(186); // draw the bottom border
        }

        for (int i = 0; i < 5; ++i) { // draw the map
            gotoxy(1, 6 + 6 * i); // set the cursor to the position of the left border
            for (int j = 0; j < (MAP_WIDTH - 1) / 11; ++j) { // draw the map
                cout << "==========|"; // draw the fence
            }
        }

        gotoxy(0, 0); // set the cursor to the position of the top left corner
        cout << char(201); // draw the top left corner
        for (int i = 1; i < MAP_WIDTH; ++i) { // draw the map
            cout << char(205); // draw the vertical border
        }
        cout << char(187); // draw the top right corner

        gotoxy(0, MAP_HEIGHT); // set the cursor to the position of the bottom left corner
        cout << char(200); // draw the bottom left corner
        for (int i = 1; i < MAP_WIDTH; ++i) { // draw the map
            cout << char(205); // draw the vertical border
        }
        cout << char(188); // draw the bottom right corner
    }

    void levelUp() // level up
    {
        if ((mCount / 3) == mLevel) { // if the count is divisible by 3
            mLevel++; // increase the level
            randomPos(); // randomize the x and y positions of the objects
            system("cls"); // clear the screen
            drawMap(); // draw the map
        }
    }

    void drawScore() const // draw the score
    {
        textColor(11); // set the color to light blue
        drawAsciiScore(mScore * 10); // draw the drawAsciiScorei score
        textColor(14); // set the color to yellow
    }

    static void clearScore() // clear the score
    {
        for (int i = 0; i < 7; ++i) { // for each line
            gotoxy(MAP_WIDTH + 7, 6 + i); // set the cursor to the position of the score
            cout
                << R"(                              )"; // clear the score
        }
    }

    void updateScore() // update the score
    {
        mScore += mLevel; // increase the score
        mCount++; // increase the count
    }

    void updatePeoplePos() // update the position of the people
    {
        for (int i = 3; i < 6; ++i) { // for each line of the finish line
            gotoxy(1, i); // set the cursor to the position of the finish line
            cout
                << R"(                                                                                                   )"; // clear the previous people
        }
        people.draw(); // draw the people
        gotoxy(people.getX() + 3, people.getY()); // set the cursor to the position of the people to the right
        cout << "+" << mLevel * 10; // draw score animation
        Sleep(150); // sleep for 150 ms
        gotoxy(people.getX() + 3, people.getY()); // set the cursor to the position of the people to the right
        cout << "     "; // clear the score animation
        people.reset(); // reset the people
    }

    void drawGame() // draw the game
    {
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            deer[i].draw(); // draw the deer
            cow[i].draw(); // draw the cow
        }
        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            truck[i].draw(); // draw the truck
            car[i].draw(); // draw the car
        }
        people.draw(); // draw the people
    }

    inline CPEOPLE getPeople() { return people; } // get the people

    void updatePosPeople(char ch)
    { // update the position of the people
        if (ch == 'A') { // if the key is A
            people.clear(); // clear the people
            people.Left(4); // move the people to the left
        }
        else if (ch == 'D') { // if the key is D
            people.clear(); // clear the people
            people.Right(4); // move the people to the right
        }
        else if (ch == 'W') { // if the key is W
            people.clear(); // clear the people
            people.Up(6); // move the people to the up
        }
        else if (ch == 'S') { // if the key is S
            people.clear(); // clear the people
            people.Down(6); // move the people to the down
        }
    }

    void updatePosVehicle() // update the position of the vehicle
    {
        if (!truckTraffic.getState()) { // if the truck moving
            if (truckTraffic.getTime() > 30) // if the time is greater than 30
                truckTraffic.drawGreenLight(truck->getY() - 1); // draw the green light
            else // if the time is less than 30
                truckTraffic.drawYellowLight(truck->getY() - 1); // draw the yellow light
            for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
                truck[i].move(-1, 0); // move the truck to the left
            }
            if (truckTraffic.updateTime() < 0) { // if the time is up
                truckTraffic.setState(true); // set the state to true
                truckTraffic.setTime(50); // set the time to 50
            }
        }
        else {
            truckTraffic.drawRedLight(truck->getY() - 1); // draw the red light
            if (truckTraffic.updateTime() < 0) { // if the time is up
                truckTraffic.setState(false); // set the state to false
                truckTraffic.setTime(100); // set the time to 150
            }
        }

        if (!carTraffic.getState()) { // if the car moving
            if (carTraffic.getTime() > 30) // if the time is greater than 30
                carTraffic.drawGreenLight(car->getY() - 1); // draw the green light
            else // if the time is less than 30
                carTraffic.drawYellowLight(car->getY() - 1); // draw the yellow light
            for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) // for each object
                car[i].move(1, 0); // move the car to the right
            if (carTraffic.updateTime() < 0) { // if the time is up
                carTraffic.setState(true); // set the state to true
                carTraffic.setTime(50); // set the time to 50
            }
        }
        else {
            carTraffic.drawRedLight(car->getY() - 1); // draw the red light
            if (carTraffic.updateTime() < 0) { // if the time is up
                carTraffic.setState(false); // set the state to false
                carTraffic.setTime(100 + rand() % 50); // set the time to 150 + random number
            }
        }
    }

    void updatePosAnimal() // update the position of the animal
    {
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            deer[i].move(-1, 0); // move the deer to the left
            cow[i].move(1, 0); // move the cow to the right
        }
    }

    bool isImpact() // check if the people is hit the object
    {
        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            if (truck[i].getY() == people.getY() - 1) // if the truck is on the same line with the people
                if (abs(truck[i].getX() - people.getX()) < 3 || (people.getX() > truck[i].getX() && people.getX() < truck[i].getX() + truck[i].getLength())) { // if the people is hit the truck
                    people.setState(false); // set the state to false
                    return true; // return true
                }

            if (car[i].getY() == people.getY() - 1) // if the car is on the same line
                if (abs(car[i].getX() - people.getX()) < 2 || (people.getX() > car[i].getX() && people.getX() < car[i].getX() + car[i].getLength() + 1)) { // if the people is hit the car
                    people.setState(false); // set the state to false
                    return true; // return true
                }
        }
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) {
            if (cow[i].getY() == people.getY() - 1) // if the cow is on the same line
                if (abs(cow[i].getX() - people.getX()) < 2 || (people.getX() > cow[i].getX() + 1 && people.getX() < cow[i].getX() + cow[i].getLength() + 1)) { // if the people is hit the cow
                    people.setState(false); // set the state to false
                    return true; // return true
                }

            if (deer[i].getY() == people.getY() - 1) // if the deer is on the same line
                if (abs(deer[i].getX() - people.getX()) < 3 || (people.getX() > deer[i].getX() + 1 && people.getX() < deer[i].getX() + deer[i].getLength())) { // if the people is hit the deer
                    people.setState(false); // set the state to false
                    return true; // return true
                }
        }
        return false; // return false
    }

    void drawDie() // draw ambulance
    {
        ambulance->setX(MAP_WIDTH); // set the x position to the map width
        ambulance->setY(people.getY() - 1); // set the y position to the people
        for (int i = MAP_WIDTH; i > -ambulance->getLength(); --i) { // for each x position
            ambulance->draw(); // draw the ambulance to the left
            ambulance->move(-1, 0); // move the ambulance to the left
            Sleep(10); // sleep for 10 ms
        }
        system("cls"); // clear the screen
    }

    void resetGame() // reset the game
    {
        people.reset(); // reset the people position
        mScore = 0; // set the mScore to 0
        mCount = 0; // set the mCount to 0
        mLevel = 1; // set the mLevel to 1
        randomPos(); // random object position
    }

    void randomPos() // random object position
    {
        if (mLevel == 2) { // if the level is 2
            delete[] cow; // delete the cow array
            delete[] deer; // delete the deer array
            cow = new CCOW[MAX_OBJECT]; // create the cow array
            deer = new CDEER[MAX_OBJECT]; // create the deer array
        }
        if (mLevel == 3) { // if the level is 3
            delete[] truck; // delete the truck array
            delete[] car; // delete the car array
            truck = new CTRUCK[MAX_OBJECT]; // create the truck array
            car = new CCAR[MAX_OBJECT]; // create the car array
        }
        srand((unsigned)time(nullptr)); // randomize the seed
        shuffle(pos, pos + 4, std::mt19937(std::random_device()())); // randomize the position

        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            int x = i * 30 + (rand() % (10)); // randomize the x position
            srand((unsigned)time(nullptr)); // randomize the seed
            truck[i].setX(10 * i + x + rand() % (5)); // set the x position of the truck
            truck[i].setY(pos[0]); // set the y position of the truck

            srand((unsigned)time(nullptr)); // randomize the seed
            car[i].setX(5 * i + x + rand() % (5)); // set the x position of the car
            car[i].setY(pos[1]);
        } // set the y position of the car
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            int x = i * 30 + (rand() % (10)); // randomize the x position
            srand((unsigned)time(nullptr)); // randomize the seed
            cow[i].setX(5 * i + x + rand() % (5)); // set the x position of the cow
            cow[i].setY(pos[3]); // set the y position of the cow

            srand((unsigned)time(nullptr)); // randomize the seed
            deer[i].setX(10 * i + x + rand() % (5)); // set the position of the deer
            deer[i].setY(pos[2]); // set the y position of the deer
        }
    }

    static void playAgainMsg() // draw play again message
    {
        textColor(14); // set the text color to yellow
        drawGameOver(); // draw game over title
        gotoxy(CONSOLE_WIDTH / 2 - 9, CONSOLE_HEIGHT / 2 + 2); // set the position of the text
        textColor(8); // set the text color to white
        cout << " Play again?(y/N) "; // print the message
        textColor(15); // set the text color to white
    }

    void saveGame() // save the game
    {
        system("cls"); // clear the screen
        drawGameTitle(); // draw the game title
        string fileName; // string to store the file name
        textColor(6); // set the text color to yellow
        gotoxy(CONSOLE_WIDTH / 2 - 4, CONSOLE_HEIGHT / 2 - 2); // set the position of the text
        cout << "SAVE GAME"; // print the message
        gotoxy(CONSOLE_WIDTH / 2 - 13, CONSOLE_HEIGHT / 2); // set the position of the text
        textColor(224); // set the text color to yellow
        cout << "  Enter file name:          "; // print the message
        int index = 0; // index of the file name
        textColor(224); // set the text color to yellow
        while (true) { // while true
            if (_kbhit()) { // if the keyboard is hit
                gotoxy(CONSOLE_WIDTH / 2 + 6 + index, CONSOLE_HEIGHT / 2); // set the position of the text
                char ch = _getch(); // get the character
                if (ch == 27) { // if the character is escape
                    textColor(15); // set the text color to white
                    return; // return
                }
                else if (ch == 13) // if the character is enter
                    break; // break
                else if (ch == 8) { // if the character is backspace
                    if (index > 0) { // if the index is greater than 0
                        --index; // decrease the index
                        gotoxy(CONSOLE_WIDTH / 2 + 6 + index, CONSOLE_HEIGHT / 2); // set the position of the text
                        cout << " "; // delete the last character
                        if (!fileName.empty()) // if the file name is not empty
                            fileName.pop_back(); // pop the last character
                    }
                }
                else { // if the character is not backspace or enter or escape
                    gotoxy(CONSOLE_WIDTH / 2 + 6 + index, CONSOLE_HEIGHT / 2); // set the position of the text
                    ++index; // increase the index
                    cout << ch; // print the character
                    fileName.push_back(ch); // push the character to the file name
                }
            }
        }
        textColor(15); // set the text color to white
        ofstream ofs(fileName + ".txt"); // open the file
        ofs << people.getX() << " " << people.getY() << '\n'; // write the people position
        ofs << mScore << '\n'; // write the score
        ofs << mLevel << '\n'; // write the level
        ofs << mCount << '\n'; // write the count
        for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            ofs << truck[i].getX() << " " << truck[i].getY() << '\n'; // write the truck position
            ofs << car[i].getX() << " " << car[i].getY() << '\n'; // write the car position
        }
        for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
            ofs << cow[i].getX() << " " << cow[i].getY() << '\n'; // write the cow position
            ofs << deer[i].getX() << " " << deer[i].getY() << '\n'; // write the deer position
        }
        ofs << truckTraffic.getTime() << " " << truckTraffic.getState() << '\n'; // write the truck traffic
        ofs << carTraffic.getTime() << " " << carTraffic.getState() << '\n'; // write the car traffic
    }

    bool loadGame() // load the game
    {
        listTXT(); // list the txt files
        string fileName; // string to store the file name
        textColor(6); // set the text color to yellow
        gotoxy(CONSOLE_WIDTH / 2 - 4, CONSOLE_HEIGHT / 2 - 2); // set the position of the text
        cout << "LOAD GAME"; // print the message
        textColor(224); // set the text color to yellow
        gotoxy(CONSOLE_WIDTH / 2 - 13, CONSOLE_HEIGHT / 2); // set the position of the text
        cout << "  Enter file name:           "; // print the message
        int index = 0; // index of the file name
        while (true) { // while true
            if (_kbhit()) { // if the keyboard is hit
                gotoxy(CONSOLE_WIDTH / 2 + 6 + index, CONSOLE_HEIGHT / 2); // set the position of the text
                char ch = _getch(); // get the character
                if (ch == 27) { // if the character is escape
                    textColor(15); // set the text color to white
                    return false; // return
                }
                else if (ch == 13) // if the character is enter
                    break; // break
                else if (ch == 8) { // if the character is backspace
                    if (index > 0) { // if the index is greater than 0
                        --index; // decrease the index
                        gotoxy(CONSOLE_WIDTH / 2 + 6 + index, CONSOLE_HEIGHT / 2); // set the position of the text
                        cout << " "; // delete the last character
                        if (!fileName.empty()) // if the file name is not empty
                            fileName.pop_back(); // pop the last character
                    }
                }
                else { // if the character is not backspace or enter or escape
                    gotoxy(CONSOLE_WIDTH / 2 + 6 + index, CONSOLE_HEIGHT / 2); // set the position of the text
                    ++index; // increase the index
                    cout << ch; // print the character
                    fileName.push_back(ch); // push the character to the file name
                }
            }
        }
        textColor(15); // set the text color to white
        ifstream ifs(fileName += ".txt"); // open the file
        if (ifs) { // if the file is open
            int x, y; // x and y position
            ifs >> x >> y; // read the people position
            people.setX(x); // set the people x position
            people.setY(y); // set the people y position
            ifs >> mScore; // read the score
            ifs >> mLevel; // read the level
            ifs >> mCount; // read the count
            delete[] truck; // delete the truck
            delete[] car; // delete the car
            delete[] cow; // delete the cow
            delete[] deer; // delete the deer
            truck = new CTRUCK[(mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT)]; // create the truck
            car = new CCAR[(mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT)]; // create the car
            cow = new CCOW[(mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT)]; // create the cow
            deer = new CDEER[(mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT)]; // create the deer
            for (int i = 0; i < (mLevel >= 3 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
                ifs >> x >> y; // read the truck position
                truck[i].setX(x); // set the truck x position
                truck[i].setY(y); // set the truck y position
                ifs >> x >> y; // read the car position
                car[i].setX(x); // set the car x position
                car[i].setY(y); // set the car y position
            }
            for (int i = 0; i < (mLevel >= 2 ? MAX_OBJECT : MIN_OBJECT); ++i) { // for each object
                ifs >> x >> y; // read the cow position
                cow[i].setX(x); // set the cow x position
                cow[i].setY(y); // set the cow y position
                ifs >> x >> y; // read the deer position
                deer[i].setX(x); // set the deer x position
                deer[i].setY(y); // set the deer y position
            }
            ifs >> x >> y; // read the truck traffic
            truckTraffic.setTime(x); // set the truck traffic time
            truckTraffic.setState(y); // set the truck traffic state
            ifs >> x >> y; // read the car traffic
            carTraffic.setState(y); // set the car traffic state
            carTraffic.setTime(x); // set the car traffic time
        }
        return true; // return true
    }

    static void drawPause() // draw the pause message
    {
        system("cls"); // clear the screen
        drawGameTitle(); // draw the game title
        textColor(6); // set the text color to yellow
        gotoxy(CONSOLE_WIDTH / 2 - 2, CONSOLE_HEIGHT / 2 - 1); // set the position of the text
        cout << "PAUSE"; // print the message
        textColor(8); // set the text color to white
        gotoxy(CONSOLE_WIDTH / 2 - 13, CONSOLE_HEIGHT / 2); // set the position of the text
        cout << "(Press any key to continue)"; // print the message
        textColor(14); // set the text color to yellow
    }
};

#endif
