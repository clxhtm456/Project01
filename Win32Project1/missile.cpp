#include "Unit.h"
#include "missile.h"
#include "resource1.h"
#include <math.h>
#include "World.h"
#include "Sound.h"
#include "Player.h"
#include "Global.h"
class Linked_List;

	//����ü �۵�
HBITMAP missile::createMask(HDC hdcBitmap, int width, int height)
{
	// ����� ���� ���� ������� ��ȫ������ �����Ǿ� �ֽ��ϴٸ�,
	// ����̳� ���������� �Ͻ÷��� RGB(255, 255, 255) �Ǵ� RGB(0, 0, 0) ���� �����Ͻø� �˴ϴ�.
	COLORREF oldBackColor = SetBkColor(hdcBitmap, RGB(0, 0, 0));

	// ����ũ ��Ʈ���� ����ϴ�. (���� DC�� ���� ����ϴ�.)
	// ���� ����ũ ��Ʈ���� 1BPP ¥�� ��� ��Ʈ������ ����ϴ�.
	hdcMask = CreateCompatibleDC(NULL);
	hBitmapMask = CreateBitmap(width, height, 1, 1, NULL); // ����ũ ��Ʈ�� ����
	SelectObject(hdcMask, hBitmapMask);

	// hdcMask�� hBitmapMask�� hdcBitmap(����� ��������Ʈ)�� ����ũ�� ����ϴ�.
	BitBlt(
		hdcMask,
		0, 0,
		width, height,
		hdcBitmap,
		0, 0,
		NOTSRCCOPY);

	// ������ ���� ������ ���������ϴ�.    
	SetBkColor(hdcBitmap, oldBackColor);

	// ������ ����ũ��Ʈ���� ����
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
	deactcount--;//�����ð��� ����ü�� �۵�����
	
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
	yPos += desY;//�۵��� desx,desy�� ���ư�
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
	//for(int i = 0~�����Ѱ���)
	//{
	//	if(����[i]�� x y��ǥ�� �̻���x y��ǥ�� ���� �浹�Ұ��)
	//	{
	//		activate = FALSE;
	//		����[i]->Damagetaken(DMG);
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
		/////////////�����
		//Ellipse(deshdc, x - 5, y - 5, x + 5, y + 5);
		//////////////
		
	}
}