#ifndef GREENGOBLIN_H
#define GREENGOBLIN_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
#include "Arrow.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//註解請參照BlueGoblin.h 												   //
	/////////////////////////////////////////////////////////////////////////////
	class Arrow;
	class GreenGoblin :public Enemy
	{
	public:
		GreenGoblin();
		GreenGoblin(int x, int y, Hero *h);
		~GreenGoblin();
		void LoadBitmap();	
		void OnShow(Maps *m) override;
		void OnMove(Maps *m);
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize()override;
		bool intersect(int x1, int x2, int y1, int y2) override;
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
		void SetXY(int x, int y);
		void movement(Maps *m);
		void attack();
		void attackShow(Maps *m);
		void arrowAttack();
		void arrowAttackMove(Maps *m);
		void arrowAttackShow(Maps *m);
	private:
		CMovingBitmap arrowAttackL;
		CMovingBitmap arrowAttackR;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		Arrow arr;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		bool attackIsFlying;
		int attack_cool_down;
		int move_or_not;
		int time_bump_into_sth;
		int arrowAttackCD;
		int arrorClock;
	};
}
#endif 