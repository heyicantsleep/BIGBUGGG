#ifndef _CTRAFFIC_H_
#define _CTRAFFIC_H_

#include <iostream>
#include "api.h"

using namespace std;

class CTRAFFIC {
private:
	int mTime;
	bool mState;
public:

	CTRAFFIC(int time) : mTime(time), mState(0)
	{
	}

	void setState(bool state) {
		mState = state;
	}

	void setTime(int time) {
		mTime = time;
	}

	inline bool getState() {
		return mState;
	}

	inline int getTime() {
		return mTime;
	}

	inline int updateTime() {
		return --mTime;
	}

	void drawRedLight(int y) {
		gotoxy(MAP_WIDTH + 1, y);
		textColor(68);
		cout << "  ";
		textColor(7);
	}

	void drawGreenLight(int y) {
		gotoxy(MAP_WIDTH + 1, y);
		textColor(34);
		cout << "  ";
		textColor(7);
	}

	void drawYellowLight(int y) {
		gotoxy(MAP_WIDTH + 1, y);
		textColor(102);
		cout << "  ";
		textColor(7);
	}
};

#endif