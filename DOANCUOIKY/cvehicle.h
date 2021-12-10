#ifndef _CVEHICLE_H_
#define _CVEHICLE_H_

#include "console.h"
#include <iostream>
#include <string>

const int MAX_VEHICLE = 3;

using namespace std;

class CVEHICLE {
protected:
    int mX, mY;

public:
    virtual void move(int dx, int dy) = 0;
     int getX() const { return mX; }
     int getY() const { return mY; }
     void setX(int x) { mX = x; }
     void setY(int y) { mY = y; }
};

class CTRUCK : public CVEHICLE {
private:
    const string truck[4] = { R"(      ____        )", R"( ____//_]|_______ )",
                       R"(|o _ |  -|  _  o| )", R"('-(o)------(o)--' )" };

public:
    void move(int x, int y) {
        if (mX > -18)
            mX += x;
        else {
            setX(consoleWidth);
        }
    }

     void draw() {
        for (int i = 0; i < 4; ++i) {
            if (mX > 1)
                gotoxy(mX, mY + i);
            else
                gotoxy(1, mY + i);
            for (int j = 0; j < 18; ++j) {
                if (mX + j > 0 && mX + j < consoleWidth) {
                    cout << truck[i][j];
                }
            }
        }
    }
};

class CCAR : public CVEHICLE {
private:
    const string car[4] = { R"(      _____      )", R"( ____//_|_\\___  )",
                     R"(|o _   -|-  _ o| )", R"('-(o)------(o)-' )"};

public:
    void move(int x, int y) {
        if (mX > - 17) {
            mX += x;
        }
        else {
            setX(consoleWidth);
        }
    }

     void draw() {
        for (int i = 0; i < 4; ++i) {
            if (mX > 1)
                gotoxy(mX, mY + i);
            else
                gotoxy(1, mY + i);
            for (int j = 0; j < 17; ++j) {
                if (mX + j > 0 && mX + j < consoleWidth) {
                    cout << car[i][j];
                }
            }
        }
    }
};


class CAMBU : public CVEHICLE {
private:
    const string ambu[4] = { R"(     __________ )", R"( ___//_]|  +  | )",
                       R"(| _ |  -|  _  | )", R"('(o)------(o)-' )" };

public:
    void move(int x, int y) {
        if (mX > -17)
            mX += x;
        else {
            setX(consoleWidth);
        }
    }

    void draw() {
        for (int i = 0; i < 4; ++i) {
            if (mX > 1)
                gotoxy(mX, mY + i);
            else
                gotoxy(1, mY + i);
            for (int j = 0; j < 16; ++j) {
                if (mX + j > 0 && mX + j < consoleWidth) {
                    if (j == 8 && i == 0) {
                        textColor(196);
                        cout << ambu[i][j];
                        textColor(7);
                    }
                    else
                    cout << ambu[i][j];
                }
            }
        }
    }
};
#endif
