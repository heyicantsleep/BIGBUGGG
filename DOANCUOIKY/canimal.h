#ifndef _CANIMAL_H_
#define _CANIMAL_H_

#include "console.h"
#include <iostream>
#include <string>

const int MAX_ANIMAL = 3;

using namespace std;

class CANIMAL {
protected:
    int mX, mY;

public:
    virtual void move(int dx, int dy) = 0;
     int getX() const { return mX; }
     int getY() const { return mY; }
     void setX(int x) { mX = x; }
     void setY(int y) { mY = y; }
};

class CDEER : public CANIMAL {
private:
    const string deer[4] = { R"(   //_\\)", R"(  __/". )", R"( / __ | )", R"(  || || )" };

public:
    void move(int dx, int dy) {
        if (mX <= 100)
            mX += dx;
        else {
            setX(-8);
        }
    }

     void draw() {
        for (int i = 0; i < 4; ++i) {
            if (mX > 1)
                gotoxy(mX, mY + i);
            else
                gotoxy(1, mY + i);
            for (int j = 0; j < 8; ++j) {
                if (mX + j > 0 && mX + j < consoleWidth) {
                    cout << deer[i][j];
                }
            }
        }
    }
};

class CCOW : public CANIMAL {
private:
    const string cow[4] = { R"(           (__))", R"(    ______/(@@))",
                      R"( *\(      /(__))", R"(    ||w----||   )" };
    int length = 15;

public:
    void move(int dx, int dy) {
        if (mX <= 100)
            mX += dx;
        else {
            setX(-15);
        }
    }

     int getLength() {
        return length;
    }

     void draw() {
        for (int i = 0; i < 4; ++i) {
            if (mX > 1)
                gotoxy(mX, mY + i);
            else
                gotoxy(1, mY + i);
            for (int j = 0; j < 15; ++j) {
                if (mX + j > 0 && mX + j < consoleWidth) {
                    cout << cow[i][j];
                }
            }
        }
    }
};

#endif
