#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map1_1::Map1_1() {
		sx = -200;
		sy = -200;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if ((i > 0 && i < 11) && ((j >= 0 && j <= 3) || j == 10)) {
					map[i][j] = 1;
				}
				else if ((i == 0 || i == 10) && (j > 0 && j < 11)) {
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
			}
		}
		map[5][3] = 0;
		map[1][4] = map[2][4] = map[8][4] = map[9][4] = map[1][5] = map[9][5] = 1;
		map[1][9] = map[2][9] = map[8][9] = map[8][9] = map[1][8] = map[9][8] = 1;
	}

	bool Map1_1::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 0) {
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
		firstmap.SetTopLeft(sx, sy);
		firstmap.ShowBitmap();
	}


	void Map1_1::addSX(int n)
	{
		sx += n;
	}

	void Map1_1::addSY(int n)
	{
		sy += n;
	}

	int Map1_1::screenX(int x) 
	{
		return x + sx;
	}

	int Map1_1::screenY(int y)
	{
		return y + sy;
	}
}