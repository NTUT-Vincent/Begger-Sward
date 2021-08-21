#ifndef ARROW_H
#define ARROW_H
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人												   //
	// 他是哥布林的專屬武器     											   //
	/////////////////////////////////////////////////////////////////////////////
	class Arrow{
	public:
		Arrow(int x, int y);
		Arrow();
		void loadBitmap();
		void OnMove(Maps *m);
		void OnShow(Maps *m);
		void setArrowXY(int x, int y);
		void setDirection(int direction);					//設定方向
		void setAttackIsFlying(bool b);						//設定始飛到一半
		int getX1();									
		int getX2();
		int getY1();
		int getY2();
	private:
		CMovingBitmap arrowLeft;							//arrow向上下左右的圖
		CMovingBitmap arrowRight;
		CMovingBitmap arrowUp;
		CMovingBitmap arrowDown;
		int _arrowX, _arrowY;								//arrow的座標
		int fly_direction;									//0=left, 1=right
		bool _attackIsFlying;
	};
}

#endif // !Scarecrow_H