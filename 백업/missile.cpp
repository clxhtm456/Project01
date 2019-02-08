#include "Unit.h"
#include "missile.h"
#include "resource1.h"
#include <math.h>
#include "World.h"
#include "Sound.h"
#include "Player.h"

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
		setSeta(master->getOSeta() + shotangle);
		switch (state)
		{
		case 0:
			xPos = master->getxPos() + 10 * cos(getSeta());
			yPos = master->getyPos() - 7 * sin(getSeta());
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
			xPos = master->getxPos() + 16 * cos(getSeta());
			yPos = master->getyPos() - 7 * sin(getSeta()) + 4;

			desX = missile_speed * cos(getSeta());
			desY = missile_speed * -sin(getSeta());
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
	
	for (int j = -20; j <20; j++)
	{
		for (int i = -80; i < 30; i++)
		{
			if (World->p[getxPos() + j][getyPos() + i] && World->p[getxPos() + j][getyPos() + i] != master&& World->p[getxPos() + j][getyPos() + i] != this
				&& RectToUnit(World->p[getxPos() + j][getyPos() + i]->getcollision()))
			{
				activate = FALSE;
				return;
			}
			if (World->collision[int(getxPos() / 5) + j][int(getyPos() / 5) + i] != 0)
			{
				if (i < 1 && i > -1 && j < 2 && j > -2)
				{
					activate = FALSE;
					return;
				}
			}
		}
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
			point[0].x = (long)(x - 25 * cos(getSeta()) - 15 * sin(getSeta()));
			point[0].y = (long)(y + 25 * sin(getSeta()) - 15 * cos(getSeta()));
			point[1].x = (long)(x + 25 * cos(getSeta()) - 15 * sin(getSeta()));
			point[1].y = (long)(y - 25 * sin(getSeta()) - 15 * cos(getSeta()));
			point[2].x = (long)(x - 25 * cos(getSeta()) + 15 * sin(getSeta()));
			point[2].y = (long)(y + 25 * sin(getSeta()) + 15 * cos(getSeta()));

			SelectObject(sourcehdc, firebit);
			PlgBlt(deshdc, point, sourcehdc, 0, 0, 16, 14, createMask(sourcehdc, 16, 14), 0, 0);
			DeleteObject(hBitmapMask);
			break;
		case 1:
			point[0].x = (long)(x - 45 * cos(getSeta()) - 18 * sin(getSeta()));
			point[0].y = (long)(y + 45 * sin(getSeta()) - 18 * cos(getSeta()));
			point[1].x = (long)(x + 45 * cos(getSeta()) - 18 * sin(getSeta()));
			point[1].y = (long)(y - 45 * sin(getSeta()) - 18 * cos(getSeta()));
			point[2].x = (long)(x - 45 * cos(getSeta()) + 18 * sin(getSeta()));
			point[2].y = (long)(y + 45 * sin(getSeta()) + 18 * cos(getSeta()));

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