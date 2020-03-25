#ifndef ENEMY_H
#define ENEMY_H


#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Enemy:public Character
	{
	public:
		Enemy();
		void LoadBitmap();
		void OnShow(Maps *m);
		void OnMove(Maps *m);
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();
		//bool cannotPass(Hero * hero);
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
	private:
		CMovingBitmap enemy;
		BloodBar blood_bar;
		int x, y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;

	};
}

#endif // !ENEMY_H