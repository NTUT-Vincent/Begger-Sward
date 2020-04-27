#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
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
		_attribute = FIRE;
		_direction = 0;
		_attackIsFlying = false;
	}

	Attack::Attack()
	{
		_x = 280;
		_y = 280;
		_attribute = FIRE;
		_direction = 0;
		_attackIsFlying = false;
	}

	void Attack::loadBitmap()
	{
		fire_attack.LoadBitmap(IDB_FIREATTACK, RGB(0, 0, 0));
		ice_attack.LoadBitmap(IDB_ATTACK1, RGB(0, 0, 0));
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
		if (_attribute == FIRE) {
			if (m->isEmpty(_x, _y)) {
				fire_attack.SetTopLeft(m->screenX(_x), m->screenY(_y));
				fire_attack.ShowBitmap();
			}
		}
		if (_attribute == ICE) {
			if (m->isEmpty(_x, _y)) {
				ice_attack.SetTopLeft(m->screenX(_x), m->screenY(_y));
				ice_attack.ShowBitmap();
			}
		}
		
	}

	void Attack::setAttribute(ELEMENT_ATTRIBUTE attribute)
	{
		_attribute = attribute;
	}

	void Attack::setXY(int x, int y)
	{
		if (!_attackIsFlying) {
			_x = x;
			_y = y;
		}
		
	}

	void Attack::setDirection(int direction)
	{
		_direction = direction;
	}

	void Attack::setAttackIsFlying(bool b)
	{
		_attackIsFlying = b;
	}

	int Attack::getX1()
	{
		return _x;
	}

	int Attack::getX2()
	{
		if (_attribute == FIRE) {
			return _x + fire_attack.Width();
		}
		if (_attribute == ICE) {
			return _x + ice_attack.Width();
		}
		return _x;
		
	}

	int Attack::getY1()
	{
		return _y;
	}

	int Attack::getY2()
	{
		if (_attribute == FIRE) {
			return _y + fire_attack.Height();
		}
		if (_attribute == ICE) {
			return _y + ice_attack.Height();
		}
		return _y;
	}

}
