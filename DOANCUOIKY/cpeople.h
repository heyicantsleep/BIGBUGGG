#ifndef _CPEOPLE_H_
#define _CPEOPLE_H_

#include "console.h"
#include <iostream>
#include <string>
#include "cvehicle.h"
#include "cgame.h"

using namespace std;

class CPEOPLE {
private:
	int mX, mY;
	bool mState;
	const string people[3] = { "~D ", "(|)", "/ \\" };

public:
	CPEOPLE() {
		mX = consoleWidth / 2 - 1;
		mY = consoleHeight - 3;
		mState = true;
	}

	~CPEOPLE() {}

	void Up(int dy) {
		if (mY - 1 != 1)
			mY -= dy;
	}
	void Left(int dx) {
		if (mX > 1)
			mX -= dx;
	}

	void Right(int dy) {
		if (mX + 3 < consoleWidth)
			mX += dy;
	}

	void Down(int dx) {
		if (mY != consoleHeight - 3)
			mY += dx;
	}

	void setX(int i) {
		mX = i;
	}

	void setY(int i) {
		mY = i;
	}


	bool isFinish() {
		return mY < 5;
	}

	void setState(bool j) {
		mState = j;
	}

	bool isDead() {
		return !mState;
	}

	int getX() { return mX; }

	int getY() { return mY; }

	bool getState() {
		return mState;
	}

	void draw() {
		textColor(6);
		for (int i = 0; i < 3; ++i) {
			gotoxy(mX, mY + i);
			cout << people[i];
		}
		textColor(7);
	}

	void clear() {
		for (int i = 0; i < 3; ++i) {
			gotoxy(mX, mY + i);
			cout << "   ";
		}
	}

	void reset() {
		mX = consoleWidth / 2 - 1;
		mY = consoleHeight - 3;
		mState = true;
	}
};

#endif
