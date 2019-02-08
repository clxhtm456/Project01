
#include "World.h"
#include "options.h"
#pragma once

class Camera
{
private:
	map* m;
	int xPos;
	int yPos;
	bool leftlock;
	bool rightlock;
	int highlock;
public :
	Camera(map* mp)
	{
		m = mp;
		xPos = 501;
		yPos = 0;
		leftlock = false;
		rightlock = false;
		highlock = Camera_high;
	}
	bool getleftlock();
	bool getrightlock();
	void sethighlock(int t);
	void setleftlock();
	void setrightlock();
	void Unitdelete();
	void Camtransport(Unit* U);
	int getxPos();
	int getyPos();
	void setxPos(int x);
	void setyPos(int y);
	void UpdateCam(HDC deshdc, HDC sourcehdc, HDC collhdc);
};