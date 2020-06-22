#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "Shoe.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// Shoe: Item class														   //
	/////////////////////////////////////////////////////////////////////////////
	Shoe::Shoe()
	{
	}
	void Shoe::load()
	{
		clock_pic.LoadBitmap(".\\bitmaps\\shoes.bmp", RGB(246, 246, 246));
		item_on_status_bar.LoadBitmapA(".\\bitmaps\\shoes.bmp", RGB(246, 246, 246));
	}
	void Shoe::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY();
		if (isExist() && intercect(h) && getNumOfBox() % 100 > 0 && getNumOfBox() % 100 <= 100)  //如果num_ofBox%100 = 20-40 箱子會掉這個道具
		{
			Shoe * p = new Shoe();
			p->load();
			h->addItem(p);
			setExist(false);
		}
	}
	void Shoe::OnShow(Maps *m)
	{
		if (isExist() && getNumOfBox() % 100 > 00 && getNumOfBox() % 100 <= 100) 
		{
			clock_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
			clock_pic.ShowBitmap();
		}
		
	}
	void Shoe::effect(Hero *h)
	{
		//改變Hero的速度(瞬間加速)
		h->setSpeedUp(true);
		setIsUsed(false);
	}
	bool Shoe::intercect(Hero * h)
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
