#ifndef _CTRAFFIC_H_
#define _CTRAFFIC_H_

#include "console.h"
#include <iostream>

using namespace std;

class CTRAFFIC {
private:
	int t;
	bool status;
public:
	CTRAFFIC(){}

	CTRAFFIC(int t1): t(t1), status(0)
	{
		t = t1;
		status = 0;
	}
	~CTRAFFIC() {}

	void setStatus(int i) {
		status = i;
	}

	bool getStatus() {
		return status;
	}

	void setTime(int t1) {
		t = t1;
	}

	int getTime() {
		return t;
	}

	int updateTime() {
		return t--;
	}

	void drawSignalRed(int i) {
		gotoxy(101, i);
		textColor(196);
		cout << "  ";
		textColor(7);
	}

	void drawSignalGreen(int i) {
		gotoxy(101, i);
		textColor(34);
		cout << "  ";
		textColor(7);
	}
};

	

#endif