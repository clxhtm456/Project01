#include "Unit.h"
#include "resource1.h"
#include "World.h"
#include "Player.h"
#include <math.h>
#include "Sound.h"
#include "missile.h"
void Player::setweapon(int type)
{
	weapontype = type;
}

int Player::getweapon()
{
	return weapontype;
}
void Player::setgranadecool(int cool)
{
	granadecool = true;
	granadecooltime = cool;
}
int Player::getgranade()
{
	return hasgranade;
}
bool Player::getgranadecool()
{
	return granadecool;
}
void Player::setgranade(int t)
{
	hasgranade = t;
}
int Player::getgranadecooltime()
{
	return granadecooltime;
}
	////////set
void Player::setfirecool(int cool)
{
	firecool = true;
	if (cool == 0)
		firecooltime = fireball_cooltime;
	else
		firecooltime = cool;
}
	/////animation state
	void Player::setstate(int i)//하반신
	{
		if (state_0_timer < state_walk)
			state_0_timer = state_walk;
		if (getstate() == i)
			return;
		switch (i)
		{
		case setstate_stand:
			acount = 0;
			statecount = 6;
			break;
		case setstate_walk:
			acount = 0;
			statecount = 9;
			break;
		case setstate_jump:
			acount = 0;
			statecount = 1;
			break;
		case setstate_duck:
			statecount = 3;
			break;
		}
		state = i;
		UpdateBitmap();
	}

	void Player::settstate(int i)//상반신
	{
		if (tstate_0_timer < state_walk)
			tstate_0_timer = state_walk;
		if (gettstate() == i)
			return;
		
		switch (i)
		{
		case setstate_stand:
			tstatecount = 6;
			break;
		case setstate_shot:
			bcount = 0;
			tstatecount = 3;
			break;
		}
		tstate = i;
		UpdateBitmap();
	}
	void Player::fire_shot()
	{
		if (this->getfirecool() == true)
			return;
		
		
		if (getbullet() <= 0)
			setweapon(0);
		switch (getweapon())
		{
		case 0:
			fireshot(0);
			setfirecool();
			break;
		case 1:
			//PlaygSound(7);
			for (int i = 0; i < 2; i++)
			{
				int angle = 1;
				for (int j = 0; j < 3; j++,angle--, heavy_delay++)
				{
					fireshot(1, heavy_delay*3,angle*missile_shotgunrange);
				}
			}
			heavy_delay = 0;
			setfirecool(heavy_cool);
			break;
		}
		
	}
	void Player::throw_granade()
	{
		if (this->getgranadecool()== true)
			return;
		//settstate(setstate_granade);

		if (getgranade() <= 0)
			setweapon(0);
		switch (getweapon())
		{
		case 0:
			fireshot(0);
			setfirecool();
			break;
		}

	}
	void Player::fireshot(int t, int delay,int angle)
	{
		for (int i = 0; i < missile_count; i++)
		{
			if (b1[i] == NULL)
			{
				b1[i] = new missile(this, hInst, World,m_cam, t, delay,angle);
				
				return;
			}
		}
	}
	//////////////get
	bool Player::getfirecool()
	{
		return firecool;
	}
	int Player::getfirecooltime()
	{
		return firecooltime;
	}

	int Player::getstate()
	{
		return state;
	}
	int Player::gettstate()
	{
		return tstate;
	}
	/////////기타
	void Player::UpdateBitmap()
	{
		for (int i = 0; i < 10; i++)
		{
			DeleteObject(standmask[i]);
			DeleteObject(topmask[i]);
			DeleteObject(standbit[i]);
			DeleteObject(top[i]);
		}
		switch (state)
		{
		case 0:
			standbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1));
			standbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1));
			standbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2));
			standbit[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2));
			standbit[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3));
			standbit[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3));

			standmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1_MASK));
			standmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1_MASK));
			standmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2_MASK));
			standmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2_MASK));
			standmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3_MASK));
			standmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3_MASK));

			break;
		case 1:
			standbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK1));
			standbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK2));
			standbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK3));
			standbit[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK4));
			standbit[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK5));
			standbit[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK6));
			standbit[6] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK7));
			standbit[7] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK8));
			standbit[8] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK9));
			standmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK1_MASK));
			standmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK2_MASK));
			standmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK3_MASK));
			standmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK4_MASK));
			standmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK5_MASK));
			standmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK6_MASK));
			standmask[6] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK7_MASK));
			standmask[7] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK8_MASK));
			standmask[8] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK9_MASK));
			break;
		case 2:
			standbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK8));
			standmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_WALK8_MASK));
			break;
		case 4:
			standbit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_DUCK1));
			standbit[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_DUCK2));
			standbit[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_DUCK3));
			standmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_DUCK1_MASK));
			standmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_DUCK2_MASK));
			standmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_DUCK3_MASK));
			break;
		}
		switch (tstate)
		{
		case 0:
			if (!getweapon())
			{
				if (gettopping())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP1));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP1));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP2));
					top[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP2));
					top[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP3));
					top[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP3));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP1_MASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP1_MASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP2_MASK));
					topmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP2_MASK));
					topmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP3_MASK));
					topmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP3_MASK));
				}
				else if (getcruching())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
				}
				else
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1_TOP));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2_TOP));
					top[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3_TOP));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1_TOP));
					top[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2_TOP));
					top[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3_TOP));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1_TMASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2_TMASK));
					topmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3_TMASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND1_TMASK));
					topmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND2_TMASK));
					topmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND3_TMASK));
				}
			}
			else
			{
				if (gettopping())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1_TOP));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1_TOP));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2_TOP));
					top[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2_TOP));
					top[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3_TOP));
					top[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3_TOP));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1_TOPM));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1_TOPM));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2_TOPM));
					topmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2_TOPM));
					topmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3_TOPM));
					topmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3_TOPM));
				}
				else if (getcruching())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					top[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BEHIND));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
					topmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_STAND_BMASK));
				}
				else
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2));
					top[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2));
					top[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3));
					top[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1_MASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND1_MASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2_MASK));
					topmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND2_MASK));
					topmask[4] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3_MASK));
					topmask[5] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HSTAND3_MASK));
				}
			}
			break;
		case 3:
			if (!getweapon())
			{
				if (gettopping())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP_FIRE1));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP_FIRE2));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP_FIRE3));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP_FIRE1M));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP_FIRE2M));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_TOP_FIRE3M));
				}
				else if (getcruching())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE1_BEHIND));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE2_BEHIND));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE3_BEHIND));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE1_BEHINDM));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE2_BEHINDM));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE3_BEHINDM));
				}
				else
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE1_TOP));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE2_TOP));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE3_TOP));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE1_TMASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE2_TMASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE3_TMASK));
				}
				
			}
			else
			{
				if (gettopping())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE1_TOP));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE2_TOP));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE3_TOP));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE1_TOPM));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE2_TOPM));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE3_TOPM));
				}
				else if (getcruching())
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE1_TOP));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE2_TOP));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE3_TOP));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE1_TMASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE2_TMASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_FIRE3_TMASK));
				}
				else
				{
					top[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE1));
					top[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE2));
					top[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE3));
					topmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE1_TMASK));
					topmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE2_TMASK));
					topmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(PLAYER_HFIRE3_TMASK));
				}
			}
			break;
		}
	}
	void Player::UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y)
	{
		ccount++;
		if (ccount > Animation_speed)
		{
			acount++;
			bcount++;
			ccount = 0;
		}
		acount = acount%statecount;
		bcount = bcount%tstatecount;
		SelectObject(sourcehdc, standmask[acount]);
		StretchBlt(deshdc,getright() ? x-50 : x+50, y-120, getright() ? 180 : -180, 150, sourcehdc, 0, 0, 55, 50, SRCAND);
		SelectObject(sourcehdc, standbit[acount]);
		StretchBlt(deshdc, getright() ? x - 50 : x + 50, y - 120, getright() ? 180 : -180, 150, sourcehdc, 0, 0, 55, 50, SRCPAINT);
		SelectObject(sourcehdc, topmask[bcount]);
		StretchBlt(deshdc, getright() ? x - 50 : x + 50, y-210, getright() ? 180 : -180, 270, sourcehdc, 0, 0, 55, 90, SRCAND);
		SelectObject(sourcehdc, top[bcount]);
		StretchBlt(deshdc, getright() ? x - 50 : x + 50, y-210, getright() ? 180 : -180, 270, sourcehdc, 0, 0, 55, 90, SRCPAINT);
		if ((getstate() != 0) && ccount == 0)
		{
			if (bcount == 0)
			{
				settstate(setstate_stand);
			}
		}
		this->EffectAnimation(deshdc, sourcehdc, 0);
	}
	void Player::rightmove(int speed)
	{
		int speed2 = (speed - speedpenalt);
		int wall;
		if (m_cam->getrightlock())
			wall = m_cam->getxPos() + screensizeX / 10;
		else
			wall = Player_limit_right;
		if (getLand())
		{
			setstate(setstate_walk);
		}
		if (!getright())
		{
			setSeta(180-getOSeta());
			if (getLand() || gettstate() != 0)
				setright(true);
		}
		if (getxPos() + (speed2) < wall)
		{
			if (getLand() == TRUE)
			{
				moving(speed2);
			}
			else
				moving((speed2 - jumpdec_speed));
		}
	}
	void Player::leftmove(int speed)
	{
		int speed2 = (speed - speedpenalt);
		int wall;
		if (m_cam->getleftlock())
			wall = m_cam->getxPos() - screensizeX / 10;
		else
			wall = Player_limit_left;
		if (getLand())
		{
			setstate(setstate_walk);
		}
		if (getright())
		{
			setSeta(180 - getOSeta());
			if(getLand() || gettstate() != 0)
				setright(false);
		}
		if (getxPos() - speed2 > wall)
		{
			if (getLand() == TRUE)
			{
				moving(-1 * (speed2));
			}
			else
				moving(-1 * (speed2 - jumpdec_speed));
		}
	}
	void Player::jump()
	{
		
		if (getjumpcount() > 0)
		{
			jumpcount--;
			weight = -jumppower;
		}

	}
	void Player::Landing(BOOL l)
	{
		if (l)
		{
			jumpcount = max_jumpcount;
			
		}
		else
			if (!Land && getstate() != 2)
			{
				setstate(setstate_jump);
			}

		Land = l;
	}
	void Player::UpdateAI()
	{
		
		if (lookdefault)
		{
			setcruching(false);
			settopping(false);
			if (getright())
				increaseSeta(0);
			else
				increaseSeta(180);
		}
		else
			lookdefault = true;
		if (state_0_timer-- <= 0)
		{
			setstate(setstate_stand);
		}
		if (tstate_0_timer-- <= 0)
		{
			settstate(setstate_stand);
		}
		//HP MP가 최대치 이상으로 회복되는거 방지
		

						   //스킬쿨타임계산
		if (firecooltime-- <= 0)
			firecool = false;

		
		for (int i = 0; i < missile_count; i++)
		{
			if (b1[i])
			{
				if (!b1[i]->getactivate())
				{
					delete b1[i];
					b1[i] = NULL;
				}else
					b1[i]->UpdateAI();
			}
		}
		Unit::UpdateAI();
	}



	void Player::attack(Unit* U)
	{

		if (getstate() != 4)
		{
			setstate(4);
			switch (getright())
			{
			case true:
				if (yPos >= U->getyPos() - boss_hit * 2 && yPos <= U->getyPos() + boss_hit * 2 && xPos >= U->getxPos() - boss_hit * 3 && xPos <= U->getxPos())
				{
					quake(20);
					U->HPregen(-1* (int)DMG);
				}
				break;
			case false:
				if (yPos >= U->getyPos() - boss_hit * 2 && yPos <= U->getyPos() + boss_hit * 2 && xPos >= U->getxPos() && xPos <= U->getxPos() + boss_hit * 3)
				{
					quake(20);
					U->HPregen(-1*(int)DMG);
				}
				break;
			}
		}
	}

	void Player::UpdateMap()
	{
		
	}