#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"

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
		enemys[0] = Enemy();
		enemys[1] = Enemy(400, 450);
		enemys[0].Initialize();
		enemys[1].Initialize();
	}

	Map1_1::~Map1_1()
	{

	}

	void Map1_1::setPos(int x, int y) {
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = 1;
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
		return x + sx;
	}

	int Map1_1::screenY(int y)
	{
		return y + sy;
	}

	/*void Map1_1::setEnemys(Enemy **e) {
		enemys = e;
	}*/
	Enemy * Map1_1::returnEnemys(int n)
	{
		return &enemys[n];
	}
	void Map1_1::enemysLoadBitmap()
	{
		for (int i = 0; i < 2; i++) {
			enemys[i].LoadBitmap();
		}

	}
	void Map1_1::enemysOnMove()
	{
		for (int i = 0; i < 2; i++) {
			enemys[i].OnMove(this);
		}
	}
	void Map1_1::enemysOnShow()
	{
		for (int i = 0; i < 2; i++) {
			enemys[i].OnShow(this);
		}
	}
	bool Map1_1::bumpIntoEnemy(int x1, int x2, int y1, int y2)
	{
		for (int i = 0; i < 2; i++) {
			if (enemys[i].cannotPass(x1, x2, y1, y2)) {
				return true;
			}
		}
		return false;
	}
}