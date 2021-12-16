#ifndef _CANIMAL_H_
#define _CANIMAL_H_

#include "api.h"
#include <iostream>
#include <string>

using namespace std;

class CANIMAL {
protected:
    int mX, mY; // position

public:
    virtual void move(int dX, int dY) = 0; // move the animal
    virtual void draw() = 0; // draw the animal
    inline virtual int getLength() const = 0; // get the length of the animal
    inline int getX() const { return mX; } // get the x position
    inline int getY() const { return mY; } // get the y position
    void setX(int x) { mX = x; } // set the x position
    void setY(int y) { mY = y; } // set the y position
};

class CCOW : public CANIMAL {
private:
    const string cow[4] = { R"(           (__))", R"(    ______/(oO))",
        R"( *\(      /(__))", R"(   ||w----||   )" };
    const int cowLength = 14; // length of the cow

public:
    void move(int dX, int dY) override // move the cow
    {
        if (mX <= MAP_WIDTH) // if the cow is on the map
            mX += dX; // move the cow to the right
        else // if the cow is off the map
            setX(-getLength()); // set the cow to the left of the map
    }

    void draw() override // draw the cow
    {
        for (int i = 0; i < 4; ++i) { // for each line
            if (mX > 1) // if the cow is on the map
                gotoxy(mX, mY + i); // set the cursor to the cow position
            else // if the cow is off the map
                gotoxy(1, mY + i); // set the cursor to the left of the map
            for (int j = 0; j < getLength() + 1; ++j) // for each character
                if (mX + j > 0 && mX + j < MAP_WIDTH) // if the cow is on the map
                    cout << cow[i][j]; // print the cow
        }
    }

    inline int getLength() const override
    {
        return cowLength; // return the length of the cow
    }
};

class CDEER : public CANIMAL {
private:
    const string deer[4] = { R"(//_\\   )", R"(."\__   )", R"( \ __ \ )",
        R"(  || || )" };
    const int deerLength = 7; // length of the deer

public:
    void move(int dX, int dY) override // move the deer
    {
        if (mX >= -getLength()) // if the deer is on the map
            mX += dX; // move the deer to the left
        else // if the deer is off the map
            setX(MAP_WIDTH); // set the deer to the right of the map
    }

    void draw() override // draw the deer
    {
        for (int i = 0; i < 4; ++i) { // for each line
            if (mX > 1) // if the deer is on the map
                gotoxy(mX, mY + i); // set the cursor to the position of the deer
            else // if the deer is off the map
                gotoxy(1, mY + i); // set the cursor to the left of the map
            for (int j = 0; j < getLength() + 1; ++j) { // for each character
                if (mX + j > 0 && mX + j < MAP_WIDTH) // if the deer is on the map
                    cout << deer[i][j]; // print the deer
            }
        }
    }

    inline int getLength() const override
    {
        return deerLength; // return the length of the deer
    }
};

#endif