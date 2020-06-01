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

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map1_3::Map1_3():Maps(-200, -200) {
		all_enemy_clear = 0;
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 15; j++) {
				if (i > 1 && i < 16 && j > 2 && j < 13) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		
		map[2][3] = map[2][12] = map[15][3] = map[15][12] = 1;
		map[6][9] = map[7][8] = map[10][9] = map[11][8] = 1;

		map[8][2] = map[9][2] = 3;

		/*for (int j = 3; j < 15; j++) {
			if (j != 6 && j != 7 && j!= 10 && j != 11) {
				map[7][j] = 1;
				map[16][j] = 1;
			}
		}*/
		
		//map[11][2] = map[12][2] = 3;
		//map[2][3] = map[2][16] = map[21][3] = map[21][16] = 1;
		//map[7][5] = map[7][6] = map[4][9] = map[4][10] = map[7][13] = map[7][14] = map[16][5] = map[16][6] = map[16][14] = map[16][13] = map[19][9] = map[19][10] = 1;
		////map[7][7] = map[4][11] = map[7][15] = map[16][7] = map[16][15] = map[19][11] = 1;
		//map[11][10] = map[12][10] = 1;

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
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}

	bool Map1_3::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map1_3::OnMove() {

	}

	void Map1_3::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP1_3);
		char *filename1_1[4] = { ".\\bitmaps\\gate1.bmp",".\\bitmaps\\gate2.bmp",".\\bitmaps\\gate3.bmp",".\\bitmaps\\gate4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}

	void Map1_3::OnShow() {
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

}