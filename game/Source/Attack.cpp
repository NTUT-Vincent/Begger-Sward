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
		_direction = 0;
		_fireIsFlying = false;
	}

	Attack::Attack()
	{
		_x = 280;
		_y = 280;
		_attribute = 0;
		_direction = 0;
		_fireIsFlying = false;
	}

	void Attack::loadBitmap()
	{
		fire_attack.LoadBitmap(IDB_FIREATTACK, RGB(0, 0, 0));
	}

	void Attack::OnMove(Maps * m)
	{
		if (_direction == 0) {
			if (m->isEmpty(_x, _y)) {
				_x -= 10;
			}
		}
		if (_direction == 1) {
			if (m->isEmpty(_x, _y)) {
				_x += 10;
			}
		}

	}

	void Attack::OnShow(Maps * m)
	{
		if (m->isEmpty(_x, _y)) {
			fire_attack.SetTopLeft(m->screenX(_x), m->screenY(_y));
			fire_attack.ShowBitmap();
		}
	}

	void Attack::setAttribute(int n)
	{
		_attribute = n;
	}

	void Attack::setXY(int x, int y)
	{
		if (!_fireIsFlying) {
			_x = x;
			_y = y;
		}
		
	}

	void Attack::setDirection(int direction)
	{
		_direction = direction;
	}

	void Attack::setFireIsFlying(bool b)
	{
		_fireIsFlying = b;
	}

}
