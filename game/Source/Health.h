#ifndef __HEALTH_H
#define __HEALTH_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具 : 永久增加生命值										   //
	// 道具可由箱子或擊殺怪物獲得												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Health: public Item
	{
	public:
		Health(int n);
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);				
	private:
		CMovingBitmap health_pic;
		int to_heal;						//要回復多少生命
	};
}
#endif