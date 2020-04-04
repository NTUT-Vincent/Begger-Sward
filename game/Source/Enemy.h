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

	class Enemy :public Character
	{
	public:
		Enemy();						//�غc�l�A�ǵ�Character����W��
		Enemy(int x, int y);			//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		void LoadBitmap();				//�[���ĤHBitmap
		void OnShow(Maps *m) override;	//��ܼĤH��e���W
		void OnMove(Maps *m);			//�ĤH����

		int GetX1();					//�^�ǳ̥���X��
		int GetY1();					//�^�ǳ̤W��Y��
		int GetX2();					//�^�ǳ̥k��X��
		int GetY2();					//�^�ǳ̤U��Y��

		void Initialize();				//��l��
										//�^���O�_�M���ĤH�Ҧb�P�@��m�A�e���OcannotPass
		bool intersect(int x1, int x2, int y1, int y2);

		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//

		void offsetHP(int offset);		//�W�Enemy����q(enemys->at->heroExistingArea(�������d��@�W��))
		bool isAlive();
		CRect * GetRect();				//�ثe�٨S�Ψ쪺�U��(�i��n�P�ɦbmygame.cpp�P���a��I�s�ɥΡAHero�]���@��)
	private:
		CMovingBitmap enemy;
		BloodBar blood_bar;
		CRect EnemyRect;
		int _x, _y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;

	};
}

#endif // !ENEMY_H