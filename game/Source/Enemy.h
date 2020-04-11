#ifndef ENEMY_H
#define ENEMY_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH													   //
	// �L�W�o�A�L�٤��|�ۤv����												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Enemy :public Character
	{
	public:
		Enemy();						//�غc�l�A�ǵ�Character����W��
		Enemy(int x, int y, int hp, string name, Hero *h);			//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		virtual ~Enemy();
		virtual void LoadBitmap() = 0;				//�[���ĤHBitmap
		virtual void OnShow(Maps *m) = 0;	//��ܼĤH��e���W
		virtual void OnMove(Maps *m) = 0;			//�ĤH����

		virtual int GetX1() = 0;					//�^�ǳ̥���X��
		virtual int GetY1() = 0;					//�^�ǳ̤W��Y��
		virtual int GetX2() = 0;					//�^�ǳ̥k��X��
		virtual int GetY2() = 0;					//�^�ǳ̤U��Y��

		virtual void Initialize() = 0;				//��l��
										//�^���O�_�M���ĤH�Ҧb�P�@��m�A�e���OcannotPass
		virtual bool intersect(int x1, int x2, int y1, int y2) = 0;

		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//

		virtual void offsetHP(int offset);		//�W�Enemy����q(enemys->at->heroExistingArea(�������d��@�W��))
		//void showHp(Maps *m, int x, int y);
		bool isAlive();
		CRect * GetRect();				//�ثe�٨S�Ψ쪺�U��(�i��n�P�ɦbmygame.cpp�P���a��I�s�ɥΡAHero�]���@��)
		bool isAttack();
	protected:
		Hero * hero_on_map;
		BloodBar blood_bar;
		CRect EnemyRect;
		int _x, _y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;

	};
}

#endif // !ENEMY_H