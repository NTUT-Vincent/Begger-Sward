#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map1_1::Map1_1():Maps(-200, -200) {
		//sx = -200;
		//sy = -200;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if ((i > 0 && i < 11) && ((j >= 0 && j <= 3) || j == 11)) {
					map[i][j] = 1;
				}
				else if ((i == 0 || i == 11) && (j > 0 && j < 12)) {
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
			}
		}
		map[5][2] = map[6][2] = 3;
		map[5][3] = map[6][3] = 0;
		map[1][4] = map[2][4] =  map[9][4] = map[1][5] = map[10][5] = 1;
		map[1][9] = map[1][10] = map[2][10] =  map[10][9] = map[9][10] = map[10][10] = 1;
	}

	Map1_1::~Map1_1()
	{

	}

	void Map1_1::Initialize()
	{
		setXY(-200, -200);
	}

	bool Map1_1::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}

	bool Map1_1::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map1_1::OnMove() {

	}

	void Map1_1::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP1_1);
	}

	void Map1_1::OnShow() {
		firstmap.SetTopLeft(getSX(),getSY());
		firstmap.ShowBitmap();
	}

	void Map1_1::getHeroX(int x)
	{
		hx = x;
	}

	void Map1_1::getHeroY(int y)
	{
		hy = y;
	}

	int Map1_1::screenX(int x)
	{
		return x + getSX();
	}

	int Map1_1::screenY(int y)
	{
		return y + getSY();
	}

	
}