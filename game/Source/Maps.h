#ifndef __MAPS_H__
#define __MAPS_H__


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Maps
	{
	public:
		virtual bool isEmpty(int x, int y) const = 0;
		virtual void addSX(int n) {};
		virtual void addSY(int n) {};
		virtual int screenX(int x) { return 0; };
		virtual int screenY(int y) { return 0; };
		virtual void getHeroX(int x) {};
		virtual void getHeroY(int y) {};
		virtual void setPos(int x, int y) {};
		//virtual Enemy * returnEnemys(int n) {  };
	};
}
#endif