#ifndef SCARECROW_H
#define SCARECROW_H
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH												   //
	// �@�ӽ_��H 															   //
	/////////////////////////////////////////////////////////////////////////////
	class Scarecrow :public Enemy
	{
	public:
		Scarecrow();								//�غc�l�A�ǵ�Character����W��
		Scarecrow(int x, int y, Hero *h);			//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~Scarecrow();
		void LoadBitmap();							//�[���ĤHBitmap
		void OnShow(Maps *m) override;				//��ܼĤH��e���W
		void OnMove(Maps *m);						//�ĤH����
		///�H�U�禡�^�Ǯy��
		int GetX1();								//�^�ǳ̥���X��
		int GetY1();								//�^�ǳ̤W��Y��
		int GetX2();								//�^�ǳ̥k��X��
		int GetY2();								//�^�ǳ̤U��Y��
		///�H�U�禡��l��
		void Initialize()override;				
		///�^���O�_�M���ĤH�Ҧb�P�@��m
		bool intersect(int x1, int x2, int y1, int y2) override;
		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);					//�U
		void SetMovingUp(bool b);					//�W
		void SetMovingLeft(bool b);					//��
		void SetMovingRight(bool b);				//�k
		void SetXY(int x, int y);					//x, y�y��
		//�Ψӧ�����
		void attack();
		void attackShow(Maps *m);
	private:
		CMovingBitmap enemy;
		CAnimation normalAttackR;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		int attack_cool_down;						//�������N�o�ɶ�
	};
}
#endif 