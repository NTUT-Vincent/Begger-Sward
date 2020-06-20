#ifndef __ATTACK_H
#define __ATTACK_H
#include "Maps.h"
#include "Character.h"
#include "Util.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѦU�ا����ۦ�											   //
	/////////////////////////////////////////////////////////////////////////////
	class Attack 
	{
	public:
		Attack(int x, int y);
		Attack();
		void loadBitmap();
		void OnMove(Maps *m);
		void OnShow(Maps *m);
		void setAttribute(ELEMENT_ATTRIBUTE attribute); //�]�w�����ݩ�
		void setAttackName(ATTACK_NAME name);			//�]�w�����W��
		void setXY(int x, int y);
		void setDirection(int direction);				//�]�w��V
		void setAttackIsFlying(bool b);					//�]�wattackIsFlying
		void setStepSize(int x, int y);					//�]�w�C��onMove���ʪ��y�Фj�p
		void resetAnimation(ATTACK_NAME atk);			//reset�ʵe
		int getX1();
		int getX2();
		int getY1();
		int getY2();
	private:
		CMovingBitmap fire_attack;
		CAnimation flame_L1;
		CAnimation flame_L2;
		CAnimation flame_R1;
		CAnimation flame_R2;
		CAnimation ice_ball;
		CAnimation fire_ball;
		CAnimation grass_ball;
		CAnimation tornado;
		CMovingBitmap fire_attack_boom;
		CMovingBitmap ice_attack;
		CMovingBitmap plant_attack;
		bool flame_status;
		int _x, _y;
		int step_size_x, step_size_y;					//�C��onMove�n���ʪ��y��
		int _direction;									//0=left, 1=right
		ELEMENT_ATTRIBUTE _attribute;
		ATTACK_NAME	_attack_name;						//�����������q�o��Call
		bool _attackIsFlying;							//�����O�_���b��
	};
}
#endif 