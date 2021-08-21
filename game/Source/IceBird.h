#ifndef ICEBIRD_H
#define ICEBIRD_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
#include "Arrow.h"
#include "BossBloodBar.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH													   //
	// �ĤG����Boss		 													   //
	/////////////////////////////////////////////////////////////////////////////
	class Arrow;
	class IceBird :public Enemy
	{
	public:
		IceBird();						//�غc�l�A�ǵ�Character����W��
		IceBird(int x, int y, Hero *h);	//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~IceBird();
		void LoadBitmap();						//�[���ĤHBitmap
		void OnShow(Maps *m) override;			//��ܼĤH��e���W
		void OnMove(Maps *m);					//�ĤH����
		int GetX1();							//�^�ǳ̥���X��
		int GetY1();							//�^�ǳ̤W��Y��
		int GetX2();							//�^�ǳ̥k��X��
		int GetY2();							//�^�ǳ̤U��Y��
		void Initialize()override;				//��l��
		//�^���O�_�M���ĤH�Ҧb�P�@��m�A�e���OcannotPass
		bool intersect(int x1, int x2, int y1, int y2) override;
		int distanceToHero();
		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);					//�U
		void SetMovingUp(bool b);					//�W
		void SetMovingLeft(bool b);					//��
		void SetMovingRight(bool b);				//�k
		void SetXY(int x, int y);					//x, y�y��
		void movement(Maps *m);
		//�Ψӧ�����
		void attack();
		void attackShow(Maps *m);
		void iceAttack();
		void iceAttackMove(Maps *m);
		void iceAttackShow(Maps *m);
		//�B��
		void iceWall(Maps *m);
		void iceWallMove(Maps *m);
		void iceWallShow(Maps *m);
		//�ɭ���
		void iceStorm(Maps *m);
		void iceStormMove(Maps *m);
		void iceStormShow(Maps *m);
		bool intersectStorm(int x1, int x2, int y1, int y2);
	private:
		BossBloodBar boss_blood_bar;
		CMovingBitmap arrowAttackL;
		CMovingBitmap arrowAttackR;
		CMovingBitmap icewall;
		CMovingBitmap icewallLeft;
		CMovingBitmap icewallRight;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation normalAttackL;
		CAnimation normalAttackR;
		CAnimation icewallL;
		CAnimation icewallR;
		CAnimation storm;
		Arrow arr;
		Attack ice_attack;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		bool isUsingIceWall;
		bool attackIsFlying;
		int attack_cool_down;
		int move_or_not;
		int time_bump_into_sth;
		bool icewall_direction;
		//�ۦ���cd
		int arrowAttackCD;
		int arrorClock;
		//�B��
		int ice_wall_clock;
		int ice_wall_x, ice_wall_y;
		int ice_wall_cd;
		//�ɭ���
		int storm_clock;
		int storm_x, storm_y;
		int storm_cd;
		bool isUsingStorm;
	};
}
#endif 