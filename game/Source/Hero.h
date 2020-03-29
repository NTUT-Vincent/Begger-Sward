#ifndef HERO_H
#define HERO_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Hero:public Character
	{
	public:
		Hero();
		void LoadBitmap();
		void OnShow();
		void OnMove(Maps *m);
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
		void SetUsingA(bool b);
		void SetUsingQ(bool b);
		void SetUsingW(bool b);
		void SetUsingE(bool b);
		void SetUsingR(bool b);
		bool cantPass(Maps *m);
		bool isMoving();
		~Hero();
	private:
		CMovingBitmap heroL, heroR;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		BloodBar b;
		int x, y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttack;
		bool isUsingA;
		bool isUsingQ;
		bool isUsingW;
		bool isUsingE;
		bool isUsingR;
		int status;
		bool directionLR; //0為左 1為右
		bool directionUD; //0為上 1為下
	};
}

#endif // !HERO_H
