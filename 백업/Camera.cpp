#include "Camera.h"
#include "Unit.h"
#include "Player.h"
#include "resource1.h"
void Camera::Unitinsert()
{
	int i = 0;
	int y;
	int x;
	//for (y = 0; y < mapMaxsizeY; y++)
	for ((this->getyPos() <= (mapsizeY / 2))? y = 0:y = this->getyPos() - (mapsizeY / 2); y < this->getyPos()+ mapsizeY /2 ; y++)
	{
		//for (x = 0 ; x < mapMaxsizeX; x++)
		for ((this->getxPos()  <= (mapsizeX / 2)) ? x = 0 : x = this->getxPos() - (mapsizeX / 2); x < this->getxPos() + mapsizeX /2; x++)
		{
			if (m->p[x][y] != NULL)
			{
				U[i] = m->p[x][y];
				if (i++ >= Camera_max_object-1)
					return;
			}
		}
	}
}
void Camera::Unitdelete()
{
	for (int i = 0; i < Camera_max_object; i++)
		U[i] = NULL;
}
void Camera::CamMove(int x, int y)
{
	xPos += x;
	yPos += y;
}
void Camera::Camtransport(int x, int y)
{
	if (abs(x - xPos) > mapsizeX)
	{
		setxPos(x);
	}
	if (x >= Player_limit_right || x <= Player_limit_left)
		return;
	static int speed = Camera_min_speed;
	yPos = Camera_high;
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
			xPos -= speed;
		}
		else if (x > xPos)
			xPos += speed;
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

		//BitBlt(deshdc, 0, 0, 1000, 720, sourcehdc, quake(), 0, SRCPAINT);
	m->UpdateAnimation(deshdc, sourcehdc,collhdc, (this->getxPos()- screensizeX /5)*5, (this->getyPos()-20), mapsizeX, mapsizeY);

	Unitinsert();

	
	///////////
	for (int i = 0; i <Camera_max_object; i++)
	{
		if (U[i])
		{
			U[i]->UpdateAnimation(deshdc, sourcehdc, screensizeX /2+5*(U[i]->getxPos()-this->getxPos()), screensizeY /2+5*(U[i]->getyPos()-this->getyPos()));
			//U[i]->UpdateAnimation(deshdc, sourcehdc, U[i]->getxPos()*5,U[i]->getyPos()*5);
			//Rectangle(deshdc, mapsizeX / 2 + (U[i]->getxPos() - this->getxPos()+ 40*cos(U[i]->getSeta())) - 5, mapsizeY / 2 + (U[i]->getyPos() - this->getyPos() - 40 * sin(U[i]->getSeta())) - 5, mapsizeX / 2 + (U[i]->getxPos() - this->getxPos() + 40 * cos(U[i]->getSeta())) + 5, mapsizeY / 2 + (U[i]->getyPos() - this->getyPos() - 40 * sin(U[i]->getSeta())) + 5);
			//Rectangle(deshdc, mapsizeX / 2 + 5*(U[i]->getxPos() - this->getxPos()) - 5, mapsizeY / 2 + 5*(U[i]->getyPos() - this->getyPos()) - 5, mapsizeX / 2 + 5*(U[i]->getxPos() - this->getxPos()) + 5, mapsizeY / 2 + 5*(U[i]->getyPos() - this->getyPos()) + 5);
			//Rectangle(deshdc, mapsizeX / 2 + getxPos() - 5, mapsizeY / 2 + getyPos() - 5, mapsizeX / 2 + getxPos()  + 5, mapsizeY / 2 + getyPos()  + 5);
			U[i] = NULL;
		}
	}
	///////////µð¹ö±ë//////////
	/*for (int x = 0; x < mapMaxsizeX; x++)
	{
		for (int y = 0; y < mapMaxsizeY; y++)
		{
			//if (m->p[x][y])
				//Ellipse(deshdc, mapsizeX / 2 + (x - this->getxPos()) - 5, mapsizeY / 2 + (y - this->getyPos()) - 5, mapsizeX / 2 + (x - this->getxPos()) + 5, mapsizeY / 2 + (y - this->getyPos()) + 5);
			//if (m->collision[x/5][y/5] != 0)
				//Ellipse(deshdc, mapsizeX / 2 + x*5 - 5, mapsizeY / 2 + y*5 - 5, mapsizeX / 2 + x*5 + 5, mapsizeY / 2 + y*5 + 5);
		}
	}*/
}

void Camera::UpdateAICam()
{
	Unitinsert();
	for (int i = 0; i <Camera_max_object; i++)
	{
		if (U[i] != NULL)
		{
			U[i]->UpdateAI();
			U[i] = NULL;
		}
	}
}