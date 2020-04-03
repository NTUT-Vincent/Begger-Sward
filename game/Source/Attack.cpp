#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"
#include "Hero.h"
#include "Maps.h"
#include "Attack.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	Attack::Attack(int x, int y)
	{
		_x = x;
		_y = y;
		_attribute = 0;
	}

	Attack::Attack()
	{
		_x = 0;
		_y = 0;
		_attribute = 0;
	}

	void Attack::loadBitmap()
	{
		fire_attack.LoadBitmap(IDB_FIREATTACK, RGB(0, 0, 0));
	}

	void Attack::OnMove(Maps * m)
	{
		if (m->isEmpty(_x, _y)) {
			_x -= 4;
		}
	}

	void Attack::OnShow(Maps * m)
	{
		if (m->isEmpty(_x, _y)) {
			fire_attack.SetTopLeft(_x, _y);
			fire_attack.ShowBitmap();
		}
	}

	void Attack::setAttribute(int n)
	{
		_attribute = n;
	}

	void Attack::setXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

}
