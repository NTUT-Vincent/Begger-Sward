#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map2_4.h"
#include <vector>
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 請參考Map1_1.cpp														   //
	/////////////////////////////////////////////////////////////////////////////
	Map2_4::Map2_4():Maps(-200, -200)
	{
		all_enemy_clear = 0;
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 18; j++) 
			{
				if (i > 4 && i < 19 && j > 2 && j < 15)
				{
					map[i][j] = 0;
				}
				else 
				{
					map[i][j] = 1;
				}
			}
		}
		for (int j = 3; j < 15; j++)
		{
			if (j != 6 && j != 7 && j!= 10 && j != 11) 
			{
				map[7][j] = 1;
				map[16][j] = 1;
			}
		}
		map[11][2] = map[12][2] = 3;
	}
	Map2_4::~Map2_4()
	{
	}
	void Map2_4::Initialize()
	{
		setXY(-200, -200);
	}
	void Map2_4::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}
	void Map2_4::setClear(bool b)
	{
		all_enemy_clear = b;
	}
	bool Map2_4::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1 && map[gx][gy] != 2) 
		{
			return true;
		}
		return false;
	}
	bool Map2_4::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) 
		{
			return true;
		}
		return false;
	}
	bool Map2_4::isOnIce(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 5) 
		{
			return true;
		}
		return false;
	}
	void Map2_4::OnMove() 
	{
	}
	void Map2_4::LoadBitmap() 
	{
		firstmap.LoadBitmap(IDB_MAP2_4);
		char *filename1_1[4] = { ".\\bitmaps\\gate5.bmp",".\\bitmaps\\gate6.bmp",".\\bitmaps\\gate7.bmp",".\\bitmaps\\gate8.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}
	void Map2_4::OnShow()
	{
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
		if (all_enemy_clear == 1)
		{
			gate.SetTopLeft(getSX()+704, getSY());
			gate.OnMove();
			gate.OnShow();
		}
	}
	void Map2_4::getHeroX(int x)
	{
		hx = x;
	}
	void Map2_4::getHeroY(int y)
	{
		hy = y;
	}
	int Map2_4::screenX(int x)
	{
		return x + getSX();
	}
	int Map2_4::screenY(int y)
	{
		return y + getSY();
	}
	void Map2_4::setIceWallPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] += n;
	}
}