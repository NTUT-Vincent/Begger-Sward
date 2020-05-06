#ifndef BLUESLIME_H
#define BLUESLIME_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH													   //
	// �L�W�o�A�L�٤��|�ۤv����												   //
	/////////////////////////////////////////////////////////////////////////////

	class BlueSlime :public Enemy
	{
	public:
		BlueSlime();						//�غc�l�A�ǵ�Character����W��
		BlueSlime(int x, int y, Hero *h);	//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~BlueSlime();
		void LoadBitmap();					//�[���ĤHBitmap
		void OnShow(Maps *m) override;		//��ܼĤH��e���W
		void OnMove(Maps *m);				//�ĤH����

		int GetX1();						//�^�ǳ̥���X��
		int GetY1();						//�^�ǳ̤W��Y��
		int GetX2();						//�^�ǳ̥k��X��
		int GetY2();						//�^�ǳ̤U��Y��

		void Initialize()override;			//��l��
											//�^���O�_�M���ĤH�Ҧb�P�@��m�A�e���OcannotPass
		bool intersect(int x1, int x2, int y1, int y2) override;

		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//
		void movement(Maps *m);

		//void attacked(int n, ELEMENT_ATTRIBUTE a);		//�W�Enemy����q(enemys->at->heroExistingArea(�������d��@�W��))
		CRect * GetRect();					//�ثe�٨S�Ψ쪺�U��(�i��n�P�ɦbmygame.cpp�P���a��I�s�ɥΡAHero�]���@��)
		//�Ψӧ�����
		void attack();
		void attackShow(Maps *m);
	private:
		CAnimation slime;
		CAnimation attack_animation;
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

#endif // !Scarecrow_H