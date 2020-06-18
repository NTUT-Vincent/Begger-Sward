#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "ProtectiveCover.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	ProtectiveCover::ProtectiveCover()
	{
	}

	void ProtectiveCover::load()
	{
		clock_pic.LoadBitmap(".\\bitmaps\\protected_cover.bmp", RGB(195, 195, 195));
		item_on_status_bar.LoadBitmapA(".\\bitmaps\\protected_cover.bmp");
	}

	void ProtectiveCover::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY();
		if (isExist() && intercect(h) && getNumOfBox() % 100 > 0 && getNumOfBox() % 100 <= 20) {	//用num_of_box決定這個道具會不會掉落
			ProtectiveCover * p = new ProtectiveCover();
			p->load();
			h->addItem(p);
			setExist(false);
		}
	}

	void ProtectiveCover::OnShow(Maps *m)
	{
		if (isExist() && getNumOfBox() % 100 > 0 && getNumOfBox() % 100 <= 20) {
			clock_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
			clock_pic.ShowBitmap();
		}
		
	}

	void ProtectiveCover::effect(Hero *h)						
	{
		h->setCantBeDamaged(true);					//使用道具的話 英雄就會進入不會被攻擊到的模式
		setIsUsed(false);
	}

	bool ProtectiveCover::intercect(Hero * h)
	{
		if (isExist()) {
			if (h->GetX2() >= _x + 10 && h->GetX1() <= _x + 20 && h->GetY2() >= _y + 10 && h->GetY1() <= _y + 20) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}


}
