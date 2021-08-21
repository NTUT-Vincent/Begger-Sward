#ifndef GREENSLIME_H
#define GREENSLIME_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//註解請參照BlueSlime.h 													   //
	/////////////////////////////////////////////////////////////////////////////
	class GreenSlime :public Enemy
	{
	public:
		GreenSlime();
		GreenSlime(int x, int y, Hero *h);
		~GreenSlime();
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
	private:
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation normalAttackL;
		CAnimation normalAttackR;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		int attack_cool_down;
		int move_or_not;
		int time_bump_into_sth;
	};
}
#endif