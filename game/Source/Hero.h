#ifndef HERO_H
#define HERO_H

#include "Util.h"
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
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
		void OnShow(Maps *m);
		void OnMove(Maps *m, vector<Enemy*> * enemys);
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
		bool cantPass(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2);
		bool isMoving();
		bool UsingSkillBitmap();			//�p�G�b�Χޯ�Areturn true	
		void skillEMove();
		void skillEShow();						
		void normalAttackMove();		//���\��Show, Move
		void normalAttackShow();
		void skillQ();
		void skillQMove(Maps *m);
		void skillQShow(Maps *m);
		~Hero();
	private:
		CMovingBitmap heroL, heroR;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation skillE;
		CAnimation normalAttackL; //�V�����\�ʵe
		CAnimation normalAttackR; //�V�k���\�ʵe
		BloodBar blood_bar;
		CRect RectHero;
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
		bool directionLR; //0���� 1���k
		bool directionUD; //0���W 1���U
		int skillTimes;   //�ΨӼƶ]�F�X��CAnimation�C
		Attack fire_attack;
	};
}

#endif // !HERO_H
