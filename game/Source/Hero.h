#include "Maps.h"
#include "Character.h"
#include "Attack.h"
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
		int getX();
		int getY();
		void Initialize();
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
		void SetAttack(bool b);
	private:
		CMovingBitmap hero;
		int x, y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttack;

	};
}