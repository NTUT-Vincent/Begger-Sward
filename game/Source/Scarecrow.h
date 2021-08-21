#ifndef SCARECROW_H
#define SCARECROW_H
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人												   //
	// 一個稻草人 															   //
	/////////////////////////////////////////////////////////////////////////////
	class Scarecrow :public Enemy
	{
	public:
		Scarecrow();								//建構子，傳給Character角色名稱
		Scarecrow(int x, int y, Hero *h);			//建構子，設定角色初始位置給Character()，方便vector一次建立
		~Scarecrow();
		void LoadBitmap();							//加載敵人Bitmap
		void OnShow(Maps *m) override;				//顯示敵人於畫面上
		void OnMove(Maps *m);						//敵人移動
		///以下函式回傳座標
		int GetX1();								//回傳最左側X值
		int GetY1();								//回傳最上側Y值
		int GetX2();								//回傳最右側X值
		int GetY2();								//回傳最下側Y值
		///以下函式初始化
		void Initialize()override;				
		///英雄是否和此敵人所在同一位置
		bool intersect(int x1, int x2, int y1, int y2) override;
		/////////////////////////////////////////////////////////////////////////////
		// 設定Enemy的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);					//下
		void SetMovingUp(bool b);					//上
		void SetMovingLeft(bool b);					//左
		void SetMovingRight(bool b);				//右
		void SetXY(int x, int y);					//x, y座標
		//用來攻擊的
		void attack();
		void attackShow(Maps *m);
	private:
		CMovingBitmap enemy;
		CAnimation normalAttackR;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		int attack_cool_down;						//攻擊的冷卻時間
	};
}
#endif 