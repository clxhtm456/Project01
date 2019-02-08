#include "Unit.h"
#include "missile.h"
#include "resource1.h"
#include <math.h>
#include "World.h"
#include "Sound.h"
#include "Player.h"
#include "Global.h"
class Linked_List;

	//투사체 작동
HBITMAP missile::createMask(HDC hdcBitmap, int width, int height)
{
	// 투명색 지정 현재 투명색은 분홍색으로 지정되어 있습니다만,
	// 흰색이나 검정색으로 하시려면 RGB(255, 255, 255) 또는 RGB(0, 0, 0) 으로 수정하시면 됩니다.
	COLORREF oldBackColor = SetBkColor(hdcBitmap, RGB(0, 0, 0));

	// 마스크 비트맵을 만듭니다. (물론 DC도 같이 만듭니다.)
	// 보통 마스크 비트맵은 1BPP 짜리 흑백 비트맵으로 만듭니다.
	hdcMask = CreateCompatibleDC(NULL);
	hBitmapMask = CreateBitmap(width, height, 1, 1, NULL); // 마스크 비트맵 생성
	SelectObject(hdcMask, hBitmapMask);

	// hdcMask와 hBitmapMask에 hdcBitmap(출력할 스프라이트)의 마스크를 만듭니다.
	BitBlt(
		hdcMask,
		0, 0,
		width, height,
		hdcBitmap,
		0, 0,
		NOTSRCCOPY);

	// 배경색을 원래 색으로 돌려놓습니다.    
	SetBkColor(hdcBitmap, oldBackColor);

	// 생성된 마스크비트맵을 리턴
	DeleteDC(hdcMask);
	
	return hBitmapMask;


	//  http://kin.naver.com/qna/detail.nhn?d1id=1&dirId=1040101&docId=125251132
}

void missile::UpdateAI()
{
	if (delaycount>0)
	{
		delaycount--;
		return;
	}

	if (delaycount == 0)
	{
		/*if (master->getbullet() <= 0)
		{
			activate = FALSE;
			return;
		}*/
		master->settstate(setstate_shot);
		setSeta(master->getOSeta() + shotangle);
		switch (state)
		{
		case 0:
			PlaygSound(5);
			xPos = master->getxPos() + 10 * cos(getSeta());
			yPos = master->getyPos() - 7 * sin(getSeta())-14;
			desX = missile_speed * cos(getSeta());
			desY = missile_speed * -sin(getSeta());
			if (abs(desX) > abs(desY))
			{
				desY = 0;
			}
			else
				desX = 0;
			break;
		case 1:
			if (shotangle == 0)
				PlaygSound(7);
			xPos = master->getxPos() + 16 * cos(getSeta());
			yPos = master->getyPos() - 7 * sin(getSeta()) -10;

			desX = missile_speed * cos(getSeta());
			desY = missile_speed * -sin(getSeta());
			master->setbullet(master->getbullet() - 1);
			break;
		}
		deactcount = missile_deacttimer;
		delaycount--;
	}
	deactcount--;//일정시간후 투사체는 작동멈춤
	
	if (deactcount <= 0)
	{
		activate = FALSE;
		return;
	}

	
	if (xPos + desX >= Player_limit_right || xPos + desX <= Player_limit_left)
	{
		activate = FALSE;
		return;
	}
	
	xPos += desX;
	yPos += desY;//작동시 desx,desy로 날아감
	int cx = (cmapsizeX / 2 - (m_cam->getxPos() - getxPos()) / 2) % cmapsizeX;
	int cy = (cmapsizeY / 2 - (m_cam->getyPos() - getyPos()) / 2) % cmapsizeY;
	if (cx < 0)
		cx = 0;
	if (cy < 0)
		cy = 0;

	
		for (int i = 0; i < Unit_Max_Count; i++)
		{
			if (World->pUnit[i] && World->pUnit[i]->getfaction() != this->getfaction()&& World->pUnit[i] != this
				&& RectToUnit(World->pUnit[i]->getcollision()))
			{
				activate = FALSE;
				World->pUnit[i]->Damagetaken(DMG);
				return;
			}
		}
	//for(int i = 0~유닛총개수)
	//{
	//	if(유닛[i]의 x y좌표랑 미사일x y좌표를 비교해 충돌할경우)
	//	{
	//		activate = FALSE;
	//		유닛[i]->Damagetaken(DMG);
	//		return;
	//	}
	//}
	if (World->collision[cx][cy] == 1)
	{
		activate = FALSE;
		return;
	}
	Postrans();
}
BOOL missile::getactivate()
{
	return activate;
}
void missile::UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y)
{
	
	if (getactivate())
	{
		switch (state)
		{
		case 0:
			point[0].x = (long)(x - 20 * cos(getSeta()) - 20 * sin(getSeta()));
			point[0].y = (long)(y + 20 * sin(getSeta()) - 20 * cos(getSeta()));
			point[1].x = (long)(x + 20 * cos(getSeta()) - 20 * sin(getSeta()));
			point[1].y = (long)(y - 20 * sin(getSeta()) - 20 * cos(getSeta()));
			point[2].x = (long)(x - 20 * cos(getSeta()) + 20 * sin(getSeta()));
			point[2].y = (long)(y + 20 * sin(getSeta()) + 20 * cos(getSeta()));

			SelectObject(sourcehdc, firebit);
			PlgBlt(deshdc, point, sourcehdc, 0, 0, 16, 14, createMask(sourcehdc, 16, 14), 0, 0);
			DeleteObject(hBitmapMask);
			break;
		case 1:
			point[0].x = (long)(x - 65 * cos(getSeta()) - 25 * sin(getSeta()));
			point[0].y = (long)(y + 65 * sin(getSeta()) - 25 * cos(getSeta()));
			point[1].x = (long)(x + 65 * cos(getSeta()) - 25 * sin(getSeta()));
			point[1].y = (long)(y - 65 * sin(getSeta()) - 25 * cos(getSeta()));
			point[2].x = (long)(x - 65 * cos(getSeta()) + 25 * sin(getSeta()));
			point[2].y = (long)(y + 65 * sin(getSeta()) + 25 * cos(getSeta()));

			SelectObject(sourcehdc, firebit);
			PlgBlt(deshdc, point, sourcehdc, 0, 0, 38, 14, createMask(sourcehdc, 38, 14), 0, 0);
			DeleteObject(hBitmapMask);
			break;
		}
		/////////////디버깅
		//Ellipse(deshdc, x - 5, y - 5, x + 5, y + 5);
		//////////////
		
	}
}