#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map1_4.h"
#include <vector>
namespace game_framework 
{
	Maps::Maps(int x, int y)
	{
		_sx = x;
		_sy = y;
	}
	void Maps::addSX(int n)			//sx+=n 就是地圖向左移動n
	{
		_sx += n;
	}
	void Maps::addSY(int n)			//sx+=n 就是地圖上移動n
	{
		_sy += n;
	}
	void Maps::setXY(int x, int y)
	{
		_sx = x;
		_sy = y;
	}
	int Maps::getSX()
	{
		return _sx;
	}
	int Maps::getSY()
	{
		return _sy;
	}
}