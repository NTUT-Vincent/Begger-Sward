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

	Map1_6::Map1_6() {
		sx = -200;
		sy = -200;
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				if ((i > 3 && i < 22) && ((j >= 0 && j <= 3) || j == 10)) {
					map[i][j] = 1;
				}
				else if ((i <= 0 || i >= 22) && (j > 3 && j < 22)) {
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
				map[i][j] = 0;
			}
		}
		/*map[5][3] = 0;
		map[1][4] = map[2][4] = map[8][4] = map[9][4] = map[1][5] = map[9][5] = 1;
		map[1][9] = map[2][9] = map[8][9] = map[8][9] = map[1][8] = map[9][8] = 1;*/
		/*enemys[0] = Enemy();
		enemys[1] = Enemy(400, 450);
		enemysV.push_back(&enemys[0]);
		enemysV.push_back(&enemys[1]);
		enemysV[0]->Initialize();
		enemysV[1]->Initialize();*/
	}

	Map1_6::~Map1_6()
	{

	}

	/*void Map1_1::setPos(int x, int y) {
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = 1;
	}*/

	bool Map1_6::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 0) {
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
		firstmap.SetTopLeft(sx, sy);
		firstmap.ShowBitmap();
	}


	void Map1_6::addSX(int n)
	{
		sx += n;
	}

	void Map1_6::addSY(int n)
	{
		sy += n;
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
		return x + sx;
	}

	int Map1_6::screenY(int y)
	{
		return y + sy;
	}

	/*void Map1_1::setEnemys(Enemy **e) {
		enemys = e;
	}*/
	/*vector<Enemy*> Map1_1::returnEnemys()
	{
		return enemysV;
	}*/
	//void Map1_1::enemysLoadBitmap()
	//{
	//	for (int i = 0; i < 2; i++) {
	//		//enemys[i].LoadBitmap();
	//		enemysV[i]->LoadBitmap();
	//	}

	//}
	//void Map1_1::enemysOnMove()
	//{
	//	for (int i = 0; i < 2; i++) {
	//		//enemys[i].OnMove(this);
	//		enemysV[i]->OnMove(this);
	//	}
	//}
	//void Map1_1::enemysOnShow()
	//{
	//	for (int i = 0; i < 2; i++) {
	//		//enemys[i].OnShow(this);
	//		enemysV[i]->OnShow(this);
	//	}
	//}
	//bool Map1_1::bumpIntoEnemy(int x1, int x2, int y1, int y2)
	//{
	//	/*for (int i = 0; i < 2; i++) {
	//		if (enemysV[i]->cannotPass(x1, x2, y1, y2)) {
	//			return true;
	//		}
	//	}*/
	//	return false;
	//}
}