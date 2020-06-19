#ifndef __PRETECTEDCOVER_H
#define __PROTECTEDCOVER_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具 : 防護罩											   //
	// 道具可由箱子或擊殺怪物獲得											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class ProtectiveCover: public Item
	{
	public:
		ProtectiveCover();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);				//道具的效果
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		CMovingBitmap clock_pic;
	};
}
#endif