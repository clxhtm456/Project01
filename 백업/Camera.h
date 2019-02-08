#include <Windows.h>
#include "Unit.h"
#include "World.h"
#include "options.h"
#pragma once

class Camera
{
private:
	map* m;
	Unit* U[Camera_max_object];
	int xPos;
	int yPos;
public :
	Camera(map* mp)
	{
		m = mp;
		xPos = 501;
		yPos = 0;
	}
	void Unitinsert();
	void Unitdelete();
	void CamMove(int x, int y);
	void Camtransport(int x, int y);
	int getxPos();
	int getyPos();
	void setxPos(int x);
	void setyPos(int y);
	void UpdateCam(HDC deshdc, HDC sourcehdc, HDC collhdc);
	void UpdateAICam();
};