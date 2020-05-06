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
		_attack_name = FIRE_BALL;
		_direction = 0;
		_attackIsFlying = false;
	}

	void Attack::loadBitmap()
	{
		fire_attack.LoadBitmap(IDB_FIREATTACK, RGB(0, 0, 0));
		ice_attack.LoadBitmap(IDB_ATTACK1, RGB(0, 0, 0));
		plant_attack.LoadBitmap(IDB_ATTACKPLANT, RGB(0, 0, 0));
		
		//向左火焰動畫
		
		char *filename1_1[6] = { ".\\bitmaps\\flameL1.bmp",".\\bitmaps\\flameL2.bmp",".\\bitmaps\\flameL3.bmp",".\\bitmaps\\flameL4.bmp", ".\\bitmaps\\flameL5.bmp", ".\\bitmaps\\flameL6.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			flame_L1.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[4] = { ".\\bitmaps\\flameL7.bmp",".\\bitmaps\\flameL8.bmp",".\\bitmaps\\flameL9.bmp",".\\bitmaps\\flameL8.bmp"};
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			flame_L2.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		
		//向右火焰動畫
		
		char *filename2_1[6] = { ".\\bitmaps\\flameR1.bmp",".\\bitmaps\\flameR2.bmp",".\\bitmaps\\flameR3.bmp",".\\bitmaps\\flameR4.bmp", ".\\bitmaps\\flameR5.bmp", ".\\bitmaps\\flameR6.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			flame_R1.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		char *filename2_2[4] = { ".\\bitmaps\\flameR7.bmp",".\\bitmaps\\flameR8.bmp",".\\bitmaps\\flameR9.bmp",".\\bitmaps\\flameR8.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			flame_R2.AddBitmap(filename2_2[i], RGB(0, 0, 0));
	}

	void Attack::OnMove(Maps * m)
	{
		if (_attack_name == FIRE_FLAME)
		{
			if(_direction == 0)
				
				flame_L2.OnMove();
			else
				flame_R2.OnMove();
			/*if (_direction == 0) {
				if (m->isEmpty(_x, _y)) {
					_x -= 10;
				}
			}
			if (_direction == 1) {
				if (m->isEmpty(_x, _y)) {
					_x += 10;
				}
			}*/
		}
		else
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
	}

	void Attack::OnShow(Maps * m)
	{
		if (_attack_name == FIRE_FLAME) {
			if (_direction == 0) 
			{
				if (m->isEmpty(_x, _y)) {
					flame_L2.SetTopLeft(m->screenX(_x)-192, m->screenY(_y));
					flame_L2.OnShow();
				}
			}
			if (_direction == 1) 
			{
				if (m->isEmpty(_x, _y)) {
					flame_R2.SetTopLeft(m->screenX(_x)+64, m->screenY(_y));
					flame_R2.OnShow();
				}
			}
		}
		if (_attack_name == FIRE_BALL) {
			if (m->isEmpty(_x, _y)) {
				fire_attack.SetTopLeft(m->screenX(_x), m->screenY(_y));
				fire_attack.ShowBitmap();
			}
		}
		if (_attack_name == ICE_BALL) {
			if (m->isEmpty(_x, _y)) {
				ice_attack.SetTopLeft(m->screenX(_x), m->screenY(_y));
				ice_attack.ShowBitmap();
			}
		}
		if (_attack_name == GRASS_BALL) {
			if (m->isEmpty(_x, _y)) {
				plant_attack.SetTopLeft(m->screenX(_x), m->screenY(_y));
				plant_attack.ShowBitmap();
			}
		}
		
	}

	void Attack::setAttribute(ELEMENT_ATTRIBUTE attribute)
	{
		_attribute = attribute;
	}

	void Attack::setAttackName(ATTACK_NAME name)
	{
		_attack_name = name;
	}

	void Attack::setXY(int x, int y)
	{
		if (_attack_name == FIRE_FLAME) {
			_x = x;
			_y = y;
		}
		else {
			if (!_attackIsFlying) {
				_x = x;
				_y = y;
			}
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
		if (_attack_name == FIRE_FLAME) {
			if (_direction == 0)
			{
				return _x - 192;
			}
			if (_direction == 1)
			{
				return _x + 64;
			}
		}
		return _x;
	}

	int Attack::getX2()
	{
		if (_attack_name == FIRE_BALL) {
			return _x + fire_attack.Width();
		}
		if (_attack_name == ICE_BALL) {
			return _x + ice_attack.Width();
		}
		if (_attack_name == GRASS_BALL) {
			return _x + plant_attack.Width();
		}
		if (_attack_name == FIRE_FLAME) {
			if (_direction == 0)
			{
				return getX1() + flame_L2.Width();
			}
			if (_direction == 1)
			{
				return getX1() + flame_R2.Width();
			}
		}
		return _x;
		
	}

	int Attack::getY1()
	{
		return _y;
	}

	int Attack::getY2()
	{
		if (_attack_name == FIRE_BALL) {
			return _y + fire_attack.Height();
		}
		if (_attack_name == ICE_BALL) {
			return _y + ice_attack.Height();
		}
		if (_attack_name == GRASS_BALL) {
			return _y + plant_attack.Height();
		}
		if (_attack_name == FIRE_FLAME) {
			if (_direction == 0)
			{
				return getY1() + flame_L2.Height();
			}
			if (_direction == 1)
			{
				return getY1() + flame_R2.Height();
			}
		}
		return _y;
	}

}
