#ifndef BLUEGOBLIN_H
#define BLUEGOBLIN_H
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
#include "Arrow.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH												   //
	//�@���Ŧ⪺�����L	 													   //
	/////////////////////////////////////////////////////////////////////////////
	class Arrow;
	class BlueGoblin :public Enemy
	{
	public:
		BlueGoblin();						//�غc�l�A�ǵ�Character����W��
		BlueGoblin(int x, int y, Hero *h);	//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~BlueGoblin();
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
		void SetMovingDown(bool b);			//�]�w�O�_���U���k����
		void SetMovingUp(bool b);			//�W
		void SetMovingLeft(bool b);			//��
		void SetMovingRight(bool b);		//�k
		void SetXY(int x, int y);			//�M�w���Ⲿ�ʪ��覡
		void movement(Maps *m);	
		///�Ψӧ�����
		void attack();						//�ΨӧP�w�O�_�n����
		void attackShow(Maps *m);
		void arrowAttack();					//�P�w�O�_�n�g�b����
		void arrowAttackMove(Maps *m);		//�g�bOnMove
		void arrowAttackShow(Maps *m);		//�g�b��OnShow
	private:
		CMovingBitmap arrowAttackL;
		CMovingBitmap arrowAttackR;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		Arrow arr;							//class Arrow
		int attack_damage;					//�����O
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		bool attackIsFlying;				//�����O�_���b��
		int attack_cool_down;				//�������N�o�ɶ�
		int move_or_not;
		int time_bump_into_sth;
		int arrowAttackCD;					//�g�b��cd
		int arrorClock;						//�b�b�Ť������ɶ�
	};
}
#endif 