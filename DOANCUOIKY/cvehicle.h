#ifndef _CVEHICLE_H_
#define _CVEHICLE_H_

#include "api.h"
#include <iostream>
#include <string>

using namespace std;

class CVEHICLE {
protected:
    int mX, mY; // position

public:
    virtual void move(int dX, int dY) = 0; // move the vehicle
    virtual void draw() = 0; // draw the vehicle
    inline virtual int getLength() const = 0; // get the length of the vehicle
    inline int getX() const { return mX; } // get the x position
    inline int getY() const { return mY; } // get the y position
    void setX(int x) { mX = x; } // set the x position
    void setY(int y) { mY = y; } // set the y position
};

class CTRUCK : public CVEHICLE {
private:
    const string truck[4] = { R"(      ____        )", R"( ____//_]|_______ )",
        R"(|o _ |  -|  _  o| )", R"('-(o)------(o)--' )" };
    const int truckLength = 17; // length of the truck
public:
    void move(int dX, int dY) override // move the truck
    {
        if (mX >= -getLength()) // if the truck is on the map
            mX += dX; // move the truck to the left
        else // if the truck is off the map
            setX(MAP_WIDTH); // set the truck to the right edge of the screen
    }

    void draw() override // draw the truck
    {
        for (int i = 0; i < 4; ++i) { // for each line of the truck
            if (mX > 1) // if the truck is on the map
                gotoxy(mX, mY + i); // set the cursor to the truck position
            else // if the truck is off the map
                gotoxy(1, mY + i); // set the cursor to the left edge of the screen
            for (int j = 0; j < getLength() + 1; ++j) { // for each character in the line
                if (mX + j > 0 && mX + j < MAP_WIDTH) // if the character is on the map
                    cout << truck[i][j]; // draw the character
            }
        }
    }

    inline int getLength() const override
    {
        return truckLength; // return the length of the truck
    }
};

class CCAR : public CVEHICLE {
private:
    const string car[4] = { R"(     _____       )", R"(  __/__|_\\_____ )",
        R"( |o _ -|-    _ o|)", R"( '-(o)------(o)-')" };
    const int carLength = 16; // length of the car
public:
    void move(int dX, int dY) override // move the car
    {
        if (mX <= MAP_WIDTH) // if the car is on the map
            mX += dX; // move the car to the right
        else // if the car is off the map
            setX(-getLength()); // set the car to the left edge of the map
    }

    void draw() override // draw the car
    {
        for (int i = 0; i < 4; ++i) { // for each line of the car
            if (mX > 1) // if the car is on the map
                gotoxy(mX, mY + i); // set the cursor to the car position
            else // if the car is off the map
                gotoxy(1, mY + i); // set the cursor to the left edge of the map
            for (int j = 0; j < getLength() + 1; ++j) { // for each character in the line
                if (mX + j > 0 && mX + j < MAP_WIDTH) // if the character is on the map
                    cout << car[i][j]; // draw the character
            }
        }
    }

    inline int getLength() const override
    {
        return carLength; // return the length of the car
    }
};

class CAMBULANCE : public CVEHICLE {
private:
    const string ambulance[4] = { R"(     __________ )", R"( ___//_]|  +  | )",
        R"(| _ |  -|  _  | )", R"('(o)------(o)-' )" };
    const int ambulanceLength = 15; // length of the ambulance

public:
    void move(int dX, int dY) override // move the ambulance
    {
        if (mX >= -getLength()) // if the ambulance is on the map
            mX += dX; // move the ambulance to the left
        else // if the ambulance is off the map
            setX(MAP_WIDTH); // set the ambulance to the right edge of the map
    }

    void draw() override // draw the ambulance
    {
        for (int i = 0; i < 4; ++i) { // for each line of the ambulance
            if (mX > 1) // if the ambulance is on the map
                gotoxy(mX, mY + i); // set the cursor to the ambulance position
            else // if the ambulance is off the map
                gotoxy(1, mY + i); // set the cursor to the left edge of the map
            for (int j = 0; j < getLength() + 1; ++j) { // for each character in the line
                if (mX + j > 0 && mX + j < MAP_WIDTH) { // if the character is on the map
                    if (j == 8 && i == 0) { // if the character is the first line and the 8th character
                        textColor(68); // set the text color to red
                        cout << ambulance[i][j]; // draw the character
                        textColor(15); // set the text color to white
                    }
                    else // if the character is not the first line or the 8th character
                        cout << ambulance[i][j]; // draw the character
                }
            }
        }
    }

    inline int getLength() const override
    {
        return ambulanceLength; // return the length of the ambulance
    }
};
#endif