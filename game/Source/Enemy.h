#ifndef ENEMY_H
#define ENEMY_H


#include "Maps.h"
#include "Character.h"
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
		int getX();
		int getY();
		void Initialize();
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
	private:
		CMovingBitmap enemy;
		int x, y;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;

	};
}

#endif // !ENEMY_H