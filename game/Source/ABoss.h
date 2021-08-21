#ifndef ABOSS_H
#define ABOSS_H
#include "Maps.h"
#include "Character.h"
#include "BossBloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH 												   //
	// �L�Oboss	 															   //
	/////////////////////////////////////////////////////////////////////////////
	class ABoss :public Enemy
	{
	public:
		ABoss();						//�غc�l�A�ǵ�Character����W��
		ABoss(int x, int y, Hero *h);	//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~ABoss();
		void LoadBitmap();					//�[���ĤHBitmap
		void OnShow(Maps *m) override;		//��ܼĤH��e���W
		void OnMove(Maps *m);				//�ĤH����
		int GetX1();						//�^�ǳ̥���X��
		int GetY1();						//�^�ǳ̤W��Y��
		int GetX2();						//�^�ǳ̥k��X��
		int GetY2();						//�^�ǳ̤U��Y��
		void Initialize()override;			//��l��
		bool intersect(int x1, int x2, int y1, int y2) override;
		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);		//  �]�w�O�_���U���k����
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//
		void movement(Maps *m);			//�M�w���Ⲿ�ʪ��覡
		//�Ψӧ�����
		void attack();					//�ΨӧP�w�O�_�n����//
		void iceAttack();				//�P�w�O�_�n�ΦB���ޯ����
		void iceAttackMove(Maps *m);	//ice_attack��onMove
		void iceAttackShow(Maps *m);	//ice_attack��onShow
	private:
		BossBloodBar boss_blood_bar;	//boss�����
		CAnimation walkingLeft;			//�V���k�����ʵe
		CAnimation walkingRight;
		CAnimation normalAttackL;		//�V���k�������ʵe
		CAnimation normalAttackR;
		CAnimation prepare_attackL;		//�ǳƧ������ʵe
		CAnimation prepare_attackR;
		CAnimation back_to_walkL;		//�ǳƦ^�쨫�����A���ʵe
		CAnimation back_to_walkR;
		enum status {					//boss�������P���A�A�@���|�ت��A			
			WALKING,
			PREPARE,
			ATTACK,
			BACK_TO_WALK
		};
		int status;						//boss�����A
		int step_size;					//�C�����ʪ��t��
		int attack_damage;				//�����O
		bool isMovingRight;				//�O�_�W�U���k��
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;				//�O�_�b����
		int attack_cool_down;			//�������N�o�ɶ�
		int status_counter;				
		int move_or_not;				//�O�_���b����
		int time_bump_into_sth;
		int attack_target_location_x, attack_target_location_y;  //�n�������Ц�m
		Attack q_attack;				
		Attack ice_attack[18];			//�����ɥ᪺�F��
		int skillTimes;					//�ΨӺ�����n���h��
		bool isUsingQ;
	};
}
#endif 