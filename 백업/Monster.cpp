#include "Monster.h"
#include "Unit.h"
#include "missile.h"
#include "World.h"
#include "Sound.h"
#include "resource1.h"
void Monster::init(Unit* U, HINSTANCE hinst, map* m)
{
	enemy = U;
	hInst = hinst;
	World = m;
}
	void Monster::setstate(int i)
	{
		ccount = 0;
		acount = 0;
		switch (i)
		{
		case 0:
			statecount = 6;
			anispeed = 4;
			break;
		case 1:
			statecount = 9;
			anispeed = 1;
			break;
		case 2:
			statecount = 10;
			anispeed = 1;
			break;
		case 3:
			statecount = 6;
			anispeed = 1;
			break;
		}
		state = i;
		UpdateBitmap();
	}
	void Monster::UpdateAI()
	{
		
		if (HP > boss_max_hp)
			HP = boss_max_hp;
		landing(weight, World);
		weight += gravity_speed;
		if (weight > gravity_max)
			weight = gravity_max;


		if (!pow(enemy, 1000))
			return;
		if (state != 1)
			setstate(1);
		if (getright())
		{
			rightmove(2);
		}
		else
		{
			leftmove(2);
		}

		if (roamingTimer < 1)
		{
			turn();
			roamingTimer = 80;
		}
		else
			roamingTimer -= 1;

		
		if (chase)
			Chase(enemy);
		
		Postrans();
	}

	void Monster::moving(double speed)
	{
		if (speed == 0)
			return;
		if (speed > 0)
		{
			for (int j = 0; j <sizex; j++)
			{
				for (int i = -80; i < 30; i++)
				{
					if (World->p[getxPos() + j][getyPos() + i] && World->p[getxPos() + j][getyPos() + i] != this
						&& RectToRect(World->p[getxPos() + j][getyPos() + i]->getcollision()))
					{
						speed = 0;
					}
					if (World->collision[int(getxPos() / 5) + j][int(getyPos() / 5) - i] != 0)
					{
						if (i < 3 && i > 0 && j < 11 && j > 1)
						{
							jump();
							speed = 0;
						}
					}
				}
			}
		}
		else if (speed < 0)
		{
			for (int j = 0; j <sizex; j++)
			{
				for (int i = -80; i < 30; i++)
				{
					if (World->p[getxPos() - j][getyPos() + i] && World->p[getxPos() - j][getyPos() + i] != this
						&& RectToRect(World->p[getxPos() - j][getyPos() + i]->getcollision()))
					{
						speed = 0;
					}
					if (World->collision[int(getxPos() / 5) - j][int(getyPos() / 5) - i] != 0)
					{
						
						if (i < 3 && i > 0 && j < 11 && j > 1)
						{
							jump();
							speed = 0;
						}
					}
				}
			}
		}

		if (speed > 0)
		{
			for (int i = 12; i < 16; i++)
			{
				for (int j = 1; j < 11; j++)
				{
					if (World->collision[int(getxPos() / 5) + j][int(getyPos() / 5) + i] == 1)
					{
						setyPos(getyPos() - (16 - i));
					}
				}
			}
		}
		else if (speed < 0)
		{
			for (int i = 12; i < 16; i++)
			{
				for (int j = 1; j < 11; j++)
				{
					if (World->collision[int(getxPos() / 5) - j][int(getyPos() / 5) + i] == 1)
					{
						setyPos(getyPos() - (16 - i));
					}
				}
			}
		}
		xPos += speed;
	}
	void Monster::Chase(Unit* U)
	{
		if (getright() == true && xPos < U->getxPos() - boss_hit * 3)
		{
			xPos += boss_dash_speed;
		}
		else if (getright() == false && xPos > U->getxPos() + boss_hit * 3)
		{
			xPos -= boss_dash_speed;
		}
	}
	void Monster::UpdateBitmap()
	{
		for (int i = 0; i < 19; i++)
		{
			DeleteObject(Bstandmask[i]);
			DeleteObject(Bstandbit[i]);
		}
		switch (state)
		{
		case 0:
			Bstandbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			Bstandbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			Bstandbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			Bstandbit[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			Bstandbit[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			Bstandbit[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));

			Bstandmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			break;
		case 1:
			Bstandbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK1));
			Bstandbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK2));
			Bstandbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK3));
			Bstandbit[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK4));
			Bstandbit[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK5));
			Bstandbit[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK6));
			Bstandbit[6] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK7));
			Bstandbit[7] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK8));
			Bstandbit[8] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK9));

			Bstandmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK1_MASK));
			Bstandmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK2_MASK));
			Bstandmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK3_MASK));
			Bstandmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK4_MASK));
			Bstandmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK5_MASK));
			Bstandmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK6_MASK));
			Bstandmask[6] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK7_MASK));
			Bstandmask[7] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK8_MASK));
			Bstandmask[8] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MODEN_WALK9_MASK));
			break;
		case 2:
			Bstandbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[6] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[7] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[8] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[9] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));

			Bstandmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[6] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[7] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[8] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[9] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			break;
		case 3:
			Bstandbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			Bstandbit[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));

			Bstandmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			Bstandmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN_MASK));
			break;
		}
	}
	void Monster::UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y)
	{
		ccount++;
		if (ccount > anispeed)
		{
			acount++;
			ccount = 0;
		}
		acount = acount%statecount;
		SelectObject(sourcehdc, Bstandmask[acount]);
		StretchBlt(deshdc, getright() ? x - 50 : x + 50, y - 50, getright() ? 180 : -180, 150, sourcehdc, 0, 0, 55, 50, SRCAND);
		SelectObject(sourcehdc, Bstandbit[acount]);
		StretchBlt(deshdc, getright() ? x - 50 : x + 50, y - 50, getright() ? 180 : -180, 150, sourcehdc, 0, 0, 55, 50, SRCPAINT);
		/////////////�����
		//Ellipse(deshdc, x - 5, y - 5, x + 5, y + 5);
		//Rectangle(deshdc, this->collision.left, this->collision.top, this->collision.right, this->collision.bottom);
		//Rectangle(deshdc, x - sizex / 2, y - sizey/2, x + sizex/2, y + sizey / 2);
		//////////////
		
	}