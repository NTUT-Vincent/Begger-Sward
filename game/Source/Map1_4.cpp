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
	/////////////////////////////////////////////////////////////////////////////
	// 請參考Map1_1.cpp														   //
	/////////////////////////////////////////////////////////////////////////////
	Map1_4::Map1_4():Maps(-500, -1190) {
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				if (i > 2 && i < 22 && j >= 3 && j < 22) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		map[9][10] = map[15][10] = map[9][16] = map[15][16] = 1;
		for (int i = 10; i <= 14; i++) {
			map[i][1] = 0;
			map[i][2] = 0;
			map[i][22] = 0;
			map[i][23] = 0;
		}
		map[9][22] = map[15][22] = map[9][2] = map[15][2] = 0;
		for (int i = 10; i <= 14; i++) {
			map[1][i] = 0;
			map[2][i] = 0;
			map[22][i] = 0;
			map[23][i] = 0;
		}
		map[2][9] = map[22][9] = map[2][15] = map[22][15] = 0;
		map[12][1] = map[11][1] = 3;
	}
	Map1_4::~Map1_4()
	{
	}
	void Map1_4::Initialize()
	{
		setXY(-500, -1190);
	}
	void Map1_4::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}
	void Map1_4::setClear(bool b)
	{
		all_enemy_clear = b;
	}
	bool Map1_4::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}
	bool Map1_4::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}
	bool Map1_4::isOnIce(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 5) {
			return true;
		}
		return false;
	}
	void Map1_4::OnMove()
	{
	}
	void Map1_4::LoadBitmap()
	{
		firstmap.LoadBitmap(IDB_MAP1_4);
		char *filename1_1[4] = { ".\\bitmaps\\gate1.bmp",".\\bitmaps\\gate2.bmp",".\\bitmaps\\gate3.bmp",".\\bitmaps\\gate4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}
	void Map1_4::OnShow()
	{
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
		if (all_enemy_clear == 1)
		{
			gate.SetTopLeft(getSX() + 768, getSY() - 64);
			gate.OnMove();
			gate.OnShow();
		}
	}
	void Map1_4::getHeroX(int x)
	{
		hx = x;
	}
	void Map1_4::getHeroY(int y)
	{
		hy = y;
	}
	int Map1_4::screenX(int x)
	{
		return x + getSX();
	}
	int Map1_4::screenY(int y)
	{
		return y + getSY();
	}
	void Map1_4::setIceWallPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] += n;
	}
}