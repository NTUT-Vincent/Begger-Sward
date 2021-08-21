#ifndef __BLOODBAR_H
#define __BLOODBAR_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѧ��													   //
	/////////////////////////////////////////////////////////////////////////////
	class BloodBar
	{
	public:
		BloodBar();
		void loadBloodBar();
		void showBloodBar(Maps *m, int hp);
		void setFullHP(int n);					//�]�w���媺��q
		void setXY(int x, int y);				//�]�w�����x y �y��
		int getFullHP();						//�^�Ǻ��媺��q
	private:
		CMovingBitmap blood_bar[12];			//���P���ת����
		double full_hp;
		int _x, _y;
	};
}
#endif // !BloodBar_H