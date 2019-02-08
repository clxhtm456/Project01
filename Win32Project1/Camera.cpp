#include "Camera.h"
#include "Unit.h"
#include "Player.h"
#include "resource1.h"
void Camera::Camtransport(Unit* U)
{
	int x;
	int y = U->getyPos();
	if (U->getright())
		x = U->getxPos() + Camera_distance;
	else
		x = U->getxPos() - Camera_distance;

	if (abs(x - xPos) > mapsizeX)
	{
		setxPos(x);
	}

	static int speed = Camera_min_speed;
	if (highlock == -1)
		yPos = y-20;
	else
		yPos = highlock;
	//yPos = mapsizeY/2;
	if (abs(x-xPos) < 10)
	{
		speed = Camera_min_speed;
		return;
	}
	else
	{
		if (x < xPos)
		{
			if (!getleftlock())
				xPos -= speed;
		}
		else if (x > xPos)
		{
			if (!getrightlock())
				xPos += speed;
		}
		if (abs(x - xPos) > 10)
		{
			if (speed++ >= Camera_max_speed)
				speed = Camera_max_speed;
		}
		else
		{
			if (speed++ >= Player_speed)
				speed = Player_speed;
		}
	}
	
}
int Camera::getxPos()
{
	if (xPos >= 0)
		return (int)xPos;
	else
		return 0;
}
int Camera::getyPos()
{
	if (yPos >= 0)
		return (int)yPos;
	else
		return 0;
}
void Camera::setxPos(int x)
{
	xPos = x;
}
void Camera::setyPos(int y)
{
	yPos = y;
}
void Camera::UpdateCam(HDC deshdc, HDC sourcehdc,HDC collhdc)
{
	m->UpdateAnimation(deshdc, sourcehdc,collhdc, (this->getxPos()- screensizeX /5)*5, (this->getyPos()-20), mapsizeX, mapsizeY);

	for (int i = 0; i <Unit_Max_Count; i++)
	{
		if (m->pUnit[i])
		{
			m->pUnit[i]->UpdateAnimation(deshdc, sourcehdc, screensizeX /2+5*(m->pUnit[i]->getxPos()-this->getxPos()), 
				screensizeY /2+5*(m->pUnit[i]->getyPos()-this->getyPos()));
		}
	}
	
}

bool Camera::getleftlock()
{
	return leftlock;
}
bool Camera::getrightlock()
{
	return rightlock;
}
void Camera::setleftlock()
{
	if (leftlock)
		leftlock = false;
	else
		leftlock = true;
}
void Camera::setrightlock()
{
	if (rightlock)
		rightlock = false;
	else
		rightlock = true;
}
void Camera::sethighlock(int t)
{
	highlock = t;
}