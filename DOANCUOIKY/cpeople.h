#ifndef _CPEOPLE_H_
#define _CPEOPLE_H_

#include "cgame.h"
#include "console.h"
#include "cvehicle.h"
#include <iostream>
#include <string>

using namespace std;

class CPEOPLE {
private:
    int mX, mY;  // Position
    bool mState; // State
    const string people[3] = { "~D ", "(|)", "/ \\" };

public:
    CPEOPLE()
        : mX(MAP_WIDTH / 2 - 1), mY(MAP_HEIGHT - 3), mState(true) {} // Constructor

    void Up(int dY) {  // Move up
        if (mY - 1 != 1) // If not at the top
            mY -= dY;      // Move up
    }

    void Down(int dY) {        // Move down
        if (mY != MAP_HEIGHT - 3) // If not at the bottom
            mY += dY;              // Move down
    }

    void Left(int dX) { // Move left
        if (mX > 1)       // If not at the left
            mX -= dX;       // Move left
    }

    void Right(int dX) {     // Move right
        if (mX + 3 < MAP_WIDTH) // If not at the right
            mX += dX;            // Move right
    }

    void setX(int x) { mX = x; } // Set X

    void setY(int y) { mY = y; } // Set Y

    void setState(bool i) { mState = i; } // Set state

    inline bool isFinish() { return mY == 3; } // If finish

    inline bool isDead() { return !mState; } // If dead

    inline int getX() { return mX; } // Get X

    inline int getY() { return mY; } // Get Y

    void draw() {                   // Draw people
        textColor(6);                 // Set color
        for (int i = 0; i < 3; ++i) { // For each line
            gotoxy(mX, mY + i);         // Set position
            cout << people[i];          // Print people
        }
        textColor(7); // Set color
    }

    void clear() {                  // Clear people
        for (int i = 0; i < 3; ++i) { // For each line
            gotoxy(mX, mY + i);         // Set position
            cout << "   ";              // Print empty
        }
    }

    void reset() {
        mX = MAP_WIDTH / 2 - 1; // Reset X
        mY = MAP_HEIGHT - 3;    // Reset Y
        mState = true;         // Reset state
    }
};

#endif