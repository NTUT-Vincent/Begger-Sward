#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "Clock.h"
namespace game_framework 
{
	Clock::Clock()
	{
	}
	void Clock::load()
	{
		clock_pic.LoadBitmap(IDB_ITEMCLOCK);
		item_on_status_bar.LoadBitmapA(IDB_ITEMCLOCK);
	}
	void Clock::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY();
		if (isExist() && intercect(h) && getNumOfBox() % 100 > 40 && getNumOfBox() % 100 <= 50) 
		{ //如果num_ofBox%100 = 40-50 箱子會掉這個道具
			Clock * p = new Clock();
			p->load();
			h->addItem(p);				//如果英雄撿到，會被推進道具欄
			setExist(false);
		}
	}
	void Clock::OnShow(Maps *m)
	{
		if (isExist() && getNumOfBox() % 100 > 40 && getNumOfBox() % 100 <= 50)
		{
			clock_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
			clock_pic.ShowBitmap();
		}
	}
	void Clock::effect(Hero *h)
	{
		h->SetAllCoolDownToZero();			//將英雄的技能冷卻時間全部重製
		setIsUsed(false);
	}
	bool Clock::intercect(Hero * h)
	{
		if (isExist()) 
		{
			if (h->GetX2() >= _x + 10 && h->GetX1() <= _x + 20 && h->GetY2() >= _y + 10 && h->GetY1() <= _y + 20) 
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
}
