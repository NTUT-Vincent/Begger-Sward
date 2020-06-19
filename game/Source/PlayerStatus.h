#ifndef __PLAYERSTATUS_H
#define __PLAYERSTATUS_H
#include "Maps.h"
#include "Character.h"
#include "Hero.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class�@���@�Ӥ��� : 												   //
	// ��ܧN�o�A�ͩR�ȥH�ΦU���ƭ�											   //
	/////////////////////////////////////////////////////////////////////////////
	class PlayerStatus
	{
	public:
		PlayerStatus();
		void Initialize(Hero *h);
		void loadPlayerStatus();
		void showPlayerStatus();
		void setXY(int x, int y);
		void loadDigitsBitmap(CMovingBitmap a[]);		//�ǤJ�@��bitmap�}�C ��}�Cload 1-9��bitmap
		void showQ();									//��ޯ�Ϥ�show�A���A���W
		void showE();
		void showW();
		void showR();
		void showHP();
		void showAttackFire();
		void showAttackIce();
		void showAttackPlant();
		void showItemsOfPlayer();						//��D��Ϥ�show�b�ޯ���W
	private:
		int _x, _y;
		CMovingBitmap status_bar;
		CMovingBitmap q_pic;
		CMovingBitmap skill_q_fire_pic;
		CMovingBitmap skill_q_ice_pic;
		CMovingBitmap skill_q_plant_pic;
		CMovingBitmap skill_e_pic;
		CMovingBitmap skill_w_pic;
		CMovingBitmap skill_r_pic;
		CMovingBitmap HP_first[10];						//hp�ӤQ�ʤd
		CMovingBitmap HP_ten[10];
		CMovingBitmap HP_hundred[10];
		CMovingBitmap HP_thousand[10];
		CMovingBitmap Q_cooldown_first[10];				//�ޯ�N�o�ɶ����Q��Ӧ��
		CMovingBitmap Q_cooldown_ten[10];
		CMovingBitmap W_cooldown_first[10];
		CMovingBitmap W_cooldown_ten[10];
		CMovingBitmap E_cooldown_first[10];
		CMovingBitmap E_cooldown_ten[10];
		CMovingBitmap R_cooldown_first[10];
		CMovingBitmap R_cooldown_ten[10];
		CMovingBitmap attack_fire_first[10];
		CMovingBitmap attack_fire_ten[10];
		CMovingBitmap attack_fire_hundred[10];
		CMovingBitmap attack_fire_thousand[10];
		CMovingBitmap attack_ice_first[10];
		CMovingBitmap attack_ice_ten[10];
		CMovingBitmap attack_ice_hundred[10];
		CMovingBitmap attack_ice_thousand[10];
		CMovingBitmap attack_plant_first[10];
		CMovingBitmap attack_plant_ten[10];
		CMovingBitmap attack_plant_hundred[10];
		CMovingBitmap attack_plant_thousand[10];
		Hero *_h;
	};
}
#endif 