#ifndef _CTRAFFIC_H_
#define _CTRAFFIC_H_

#include "console.h"
#include <iostream>

using namespace std;

class CTRAFFIC {
private:
	int mTime;
	bool mState;
public:

	CTRAFFIC(int time): mTime(time), mState(0)
	{
	}

	void setState(bool i) {
		mState = i;
	}

	bool getState() {
		return mState;
	}

	void setTime(int time) {
		mTime = time;
	}

	inline int getTime() {
		return mTime;
	}

	inline int updateTime() {
		return --mTime;
	}

	void drawRedLight(int index) {
		gotoxy(101, index);
		textColor(196);
		cout << "  ";
		textColor(7);
	}

	void drawGreenLight(int index) {
		gotoxy(101, index);
		textColor(34);
		cout << "  ";
		textColor(7);
	}
};

	

#endif