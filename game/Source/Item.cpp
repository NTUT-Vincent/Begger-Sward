#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	Item::Item()
	{
	}

	void Item::Initialize()
	{
		_isExist = true;
		random_num = rand();
	}

	bool Item::isExist()
	{
		return _isExist;
	}

	void Item::setExist(bool b)
	{
		_isExist = b;
	}

	void Item::setXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Item::setRandomNum(int n)
	{
		random_num = n;
	}

	int Item::getX()
	{
		return _x;
	}

	int Item::getY()
	{
		return _y;
	}

	int Item::getRandomNum()
	{
		return random_num;
	}

	bool Item::intercect(Hero * h)
	{
		if (isExist()) {
			if (h->GetX2() >= _x+10 && h->GetX1() <= _x + 20 && h->GetY2() >= _y + 10 && h->GetY1() <= _y + 20) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}

}
