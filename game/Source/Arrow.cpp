#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "Arrow.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// Arrow: Item class													   //
	/////////////////////////////////////////////////////////////////////////////
	Arrow::Arrow(int x, int y)
	{
		_arrowX = x;
		_arrowY = y;
		fly_direction = 0;
		_attackIsFlying = false;
	}
	Arrow::Arrow()
	{
		_arrowX = 280;
		_arrowY = 280;
		fly_direction = 0;
		_attackIsFlying = false;
	}
	void Arrow::loadBitmap()
	{
		arrowLeft.LoadBitmap(".\\bitmaps\\arrowLeft.bmp", RGB(0, 0, 0));
		arrowRight.LoadBitmap(".\\bitmaps\\arrowRight.bmp", RGB(0, 0, 0));
		arrowUp.LoadBitmap(".\\bitmaps\\arrowUp.bmp", RGB(0, 0, 0));
		arrowDown.LoadBitmap(".\\bitmaps\\arrowDown.bmp", RGB(0, 0, 0));
	}
	void Arrow::OnMove(Maps * m)
	{
		if (m->isEmpty(_arrowX, _arrowY)) 
		{	//如果下個位置是empty就可以繼續飛
			if (fly_direction == 0 && m->isEmpty(_arrowX, _arrowY))
				_arrowX -= 8;
			if (fly_direction == 1 && m->isEmpty(_arrowX + arrowRight.Width(), _arrowY))
				_arrowX += 8;
			if (fly_direction == 2 && m->isEmpty(_arrowX, _arrowY))
				_arrowY -= 8;
			if (fly_direction == 3 && m->isEmpty(_arrowX, _arrowY + arrowDown.Height()))
				_arrowY += 8;
		}
	}
	void Arrow::OnShow(Maps * m)
	{
		if (fly_direction == 0) 
		{
			arrowLeft.SetTopLeft(m->screenX(_arrowX), m->screenY(_arrowY));
			arrowLeft.ShowBitmap();
		}
		if (fly_direction == 1)
		{
			arrowRight.SetTopLeft(m->screenX(_arrowX), m->screenY(_arrowY));
			arrowRight.ShowBitmap();
		}
		if (fly_direction == 2) 
		{
			arrowUp.SetTopLeft(m->screenX(_arrowX), m->screenY(_arrowY));
			arrowUp.ShowBitmap();
		}
		if (fly_direction == 3) 
		{
			arrowDown.SetTopLeft(m->screenX(_arrowX), m->screenY(_arrowY));
			arrowDown.ShowBitmap();
		}
	}
	void Arrow::setArrowXY(int x, int y)
	{
		_arrowX = x;
		_arrowY = y;
	}
	void Arrow::setDirection(int direction)
	{
		fly_direction = direction;
	}
	void Arrow::setAttackIsFlying(bool b)
	{
		_attackIsFlying = b;
	}
	int Arrow::getX1()
	{
		return _arrowX;
	}
	int Arrow::getX2()
	{
		if (fly_direction == 0)						
		{
			return arrowLeft.Width() + _arrowX;
		}
		if (fly_direction == 1)
		{
			return arrowRight.Width() + _arrowX;
		}
		if (fly_direction == 2)
		{
			return arrowUp.Width() + _arrowX;
		}
		else
		{
			return arrowDown.Width() + _arrowX;
		}
	}
	int Arrow::getY1()
	{
		return _arrowY;
	}
	int Arrow::getY2()
	{
		if (fly_direction == 0)
		{
			return arrowLeft.Height() + _arrowY;
		}
		if (fly_direction == 1)
		{
			return arrowRight.Height() + _arrowY;
		}
		if (fly_direction == 2)
		{
			return arrowUp.Height() + _arrowY;
		}
		else
		{
			return arrowDown.Height() + _arrowY;
		}
	}
}
