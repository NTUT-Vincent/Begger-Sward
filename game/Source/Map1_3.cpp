#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map1_3.h"
#include <vector>
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 請參考Map1_1.cpp														   //
	/////////////////////////////////////////////////////////////////////////////
	Map1_3::Map1_3():Maps(-200, -200)
	{
		all_enemy_clear = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 15; j++) {
				if (i > 1 && i < 16 && j > 2 && j < 13) 
				{
					map[i][j] = 0;
				}
				else 
				{
					map[i][j] = 1;
				}
			}
		}
		map[2][3] = map[2][12] = map[15][3] = map[15][12] = 1;
		map[6][9] = map[7][8] = map[10][9] = map[11][8] = 1;
		map[8][2] = map[9][2] = 3;
	}
	Map1_3::~Map1_3()
	{
	}
	void Map1_3::Initialize()
	{
		setXY(-200, -200);
	}
	void Map1_3::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}
	void Map1_3::setClear(bool b)
	{
		all_enemy_clear = b;
	}
	bool Map1_3::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1)
		{
			return true;
		}
		return false;
	}
	bool Map1_3::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) 
		{
			return true;
		}
		return false;
	}
	bool Map1_3::isOnIce(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 5)
		{
			return true;
		}
		return false;
	}
	void Map1_3::OnMove()
	{
	}
	void Map1_3::LoadBitmap()
	{
		firstmap.LoadBitmap(IDB_MAP1_3);
		char *filename1_1[4] = { ".\\bitmaps\\gate1.bmp",".\\bitmaps\\gate2.bmp",".\\bitmaps\\gate3.bmp",".\\bitmaps\\gate4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}
	void Map1_3::OnShow()
	{
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
		if (all_enemy_clear == 1)
		{
			gate.SetTopLeft(getSX()+512, getSY()+64);
			gate.OnMove();
			gate.OnShow();
		}
	}
	void Map1_3::getHeroX(int x)
	{
		hx = x;
	}
	void Map1_3::getHeroY(int y)
	{
		hy = y;
	}
	int Map1_3::screenX(int x)
	{
		return x + getSX();
	}
	int Map1_3::screenY(int y)
	{
		return y + getSY();
	}
	void Map1_3::setIceWallPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] += n;
	}
}