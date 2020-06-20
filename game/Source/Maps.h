#ifndef __MAPS_H__
#define __MAPS_H__
#include <vector>
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Maps���Ǧ�
	// 
	/////////////////////////////////////////////////////////////////////////////
	class Maps
	{
	public:
		Maps(int x, int y);
		virtual bool isEmpty(int x, int y) const = 0;
		virtual void addSX(int n);
		virtual void addSY(int n);
		virtual int screenX(int x) { return 0; };
		virtual int screenY(int y) { return 0; };
		virtual void getHeroX(int x) {};
		virtual void getHeroY(int y) {};
		virtual void setPos(int x, int y, int n) = 0;
		virtual void setIceWallPos(int x, int y, int n) = 0; // n = +1�h�B���X�� n = -1�B��Ѱ����ɭ�
		virtual void setClear(bool b) = 0;
		virtual bool inFinishArea(int x, int y) = 0;
		virtual bool isOnIce(int x, int y) = 0;
		void setXY(int x, int y);
		int getSX();
		int getSY();
	private:
		int _sx, _sy;
		bool all_enemy_clear;
	};
}
#endif