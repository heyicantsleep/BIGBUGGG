#ifndef _CPEOPLE_H_
#define _CPEOPLE_H_

#include "api.h"
#include <iostream>
#include <string>

using namespace std;

class CPEOPLE {
private:
    int mX, mY; // Position
    bool mState; // State
    const string people[3] = { "~D ", "(|)", "/ \\" };

public:
    CPEOPLE() // Constructor
        : mX(MAP_WIDTH / 2 - 1)
        , mY(MAP_HEIGHT - 3)
        , mState(true)
    {
    }

    void Up(int dY) // Move
    {
        if (mY - 1 != 1) // If not at the top
            mY -= dY; // Move up
    }

    void Down(int dY) // Move down
    {
        if (mY != MAP_HEIGHT - 3) // If not at the bottom
            mY += dY; // Move down
    }

    void Left(int dX) // Move left
    {
        if (mX > 1) // If not at the left map edge
            mX -= dX; // Move left
    }

    void Right(int dX) // Move right
    {
        if (mX + 3 < MAP_WIDTH) // If not at the right map edge
            mX += dX; // Move right
    }

    void setX(int x) { mX = x; } // Set X position

    void setY(int y) { mY = y; } // Set Y position

    void setState(bool state) { mState = state; } // Set state

    inline bool isFinish() const { return mY == 3; } // Check finish

    inline bool isDead() const { return !mState; } // Check dead

    inline int getX() const { return mX; } // Get X position

    inline int getY() const { return mY; } // Get Y position

    void draw() // draw the people
    {
        textColor(6); // change color to yellow
        for (int i = 0; i < 3; ++i) { // For each line
            gotoxy(mX, mY + i); // Set position
            cout << people[i]; // draw people
        }
        textColor(15); // change color to white
    }

    void clear() const // clear the people
    {
        for (int i = 0; i < 3; ++i) { // For each line
            gotoxy(mX, mY + i); // Set position
            cout << "   "; // clear people
        }
    }

    void reset()
    {
        mX = MAP_WIDTH / 2 - 1; // Reset X position
        mY = MAP_HEIGHT - 3; // Reset Y position
        mState = true; // Reset state
    }
};

#endif