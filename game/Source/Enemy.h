#ifndef ENEMY_H
#define ENEMY_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人													   //
	// 他超廢，他還不會自己攻擊												   //
	/////////////////////////////////////////////////////////////////////////////

	class Enemy :public Character
	{
	public:
		Enemy();						//建構子，傳給Character角色名稱
		Enemy(int x, int y);			//建構子，設定角色初始位置給Character()，方便vector一次建立
		void LoadBitmap();				//加載敵人Bitmap
		void OnShow(Maps *m) override;	//顯示敵人於畫面上
		void OnMove(Maps *m);			//敵人移動

		int GetX1();					//回傳最左側X值
		int GetY1();					//回傳最上側Y值
		int GetX2();					//回傳最右側X值
		int GetY2();					//回傳最下側Y值

		void Initialize();				//初始化
										//英雄是否和此敵人所在同一位置，前身是cannotPass
		bool intersect(int x1, int x2, int y1, int y2);

		/////////////////////////////////////////////////////////////////////////////
		// 設定Enemy的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//

		void offsetHP(int offset);		//增減此Enemy的血量(enemys->at->heroExistingArea(的攻擊範圍作增減))
		bool isAlive();
		CRect * GetRect();				//目前還沒用到的垃圾(可能要同時在mygame.cpp同等地位呼叫時用，Hero也有一組)
	private:
		CMovingBitmap enemy;
		BloodBar blood_bar;
		CRect EnemyRect;
		int _x, _y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;

	};
}

#endif // !ENEMY_H