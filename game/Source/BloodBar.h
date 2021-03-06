#ifndef __BLOODBAR_H
#define __BLOODBAR_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供血條													   //
	/////////////////////////////////////////////////////////////////////////////
	class BloodBar
	{
	public:
		BloodBar();
		void loadBloodBar();
		void showBloodBar(Maps *m, int hp);
		void setFullHP(int n);					//設定滿血的血量
		void setXY(int x, int y);				//設定血條的x y 座標
		int getFullHP();						//回傳滿血的血量
	private:
		CMovingBitmap blood_bar[12];			//不同長度的血條
		double full_hp;
		int _x, _y;
	};
}
#endif // !BloodBar_H