#include "Maps.h"
#include "Character.h"
#include "Weapon.h"
#include "BloodBar.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
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
		~Hero();
	private:
		CMovingBitmap hero;
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
		int direction; //1���W 2���U 3���� 4���k
	};
}