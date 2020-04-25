#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map1_6.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map1_6::Map1_6():Maps(-500, -1190) {
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				if (i > 2 && i < 21 && j >= 3 && j < 21) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		map[8][9] = map[9][9] = map[14][9] = map[15][9] = map[8][15] = map[9][15] = map[14][15] = map[15][15] = 1;
		map[2][10] = map[2][11] = map[2][12] = map[2][13] = map[2][14] = map[2][9] = 0;
		map[1][10] = map[1][11] = map[1][12] = map[1][13] = 0;
		map[9][2] = map[10][2] = map[11][2] = map[12][2] = map[13][2] =  map[14][2] = 0;
		map[10][1] = map[11][1] = map[12][1] = map[13][1] = 0;
		map[21][10] = map[21][11] = map[21][12] = map[21][13] = map[21][14] = map[21][9] = 0;
		map[22][10] = map[22][11] = map[22][12] = map[22][13] = 0;
		map[9][21] = map[10][21] = map[11][21] = map[12][21] = map[13][21] = map[14][21] = 0;
		map[10][22] = map[11][22] = map[12][22] = map[13][22] = 0;
	}

	Map1_6::~Map1_6()
	{

	}

	void Map1_6::Initialize()
	{
		setXY(-500, -1190);
	}

	bool Map1_6::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 0) {
			return true;
		}
		return false;
	}

	bool Map1_6::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map1_6::OnMove() {

	}

	void Map1_6::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP1_6);
	}

	void Map1_6::OnShow() {
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
	}

	void Map1_6::getHeroX(int x)
	{
		hx = x;
	}

	void Map1_6::getHeroY(int y)
	{
		hy = y;
	}

	int Map1_6::screenX(int x)
	{
		return x + getSX();
	}

	int Map1_6::screenY(int y)
	{
		return y + getSY();
	}

}