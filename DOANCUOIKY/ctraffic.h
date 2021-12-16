#ifndef _CTRAFFIC_H_
#define _CTRAFFIC_H_

#include "api.h"
#include <iostream>

using namespace std;

class CTRAFFIC {
private:
    int mTime; // traffic time
    bool mState; // traffic state

public:
    CTRAFFIC(int time) // constructor
        : mTime(time)
        , mState(0)
    {
    }

    void setState(bool state) // set traffic state
    {
        mState = state;
    }

    void setTime(int time) // set traffic time
    {
        mTime = time;
    }

    inline bool getState() // get traffic state
    {
        return mState;
    }

    inline int getTime() // get traffic time
    {
        return mTime;
    }

    inline int updateTime() // update traffic time
    {
        return --mTime;
    }

    void drawRedLight(int y) // draw red light
    {
        gotoxy(MAP_WIDTH + 1, y); // set red light position
        textColor(68); // change color to red
        cout << "  "; // draw red light
        textColor(15); // change color to white
    }

    void drawGreenLight(int y) // draw green light
    {
        gotoxy(MAP_WIDTH + 1, y); // set green light position
        textColor(34); // change color to green
        cout << "  "; // draw green light
        textColor(15); // change color to white
    }

    void drawYellowLight(int y) // draw yellow light
    {
        gotoxy(MAP_WIDTH + 1, y); // set yellow light position
        textColor(102); // change color to yellow
        cout << "  "; // draw yellow light
        textColor(15); // change color to white
    }
};

#endif