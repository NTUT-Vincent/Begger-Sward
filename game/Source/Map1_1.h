#include "Enemy.h"
namespace game_framework {

	class Map1_1 : public Maps
	{
	public:
		Map1_1();
		~Map1_1();
		void setPos(int x, int y);
		bool isEmpty(int x, int y) const;
		void OnMove();
		void LoadBitmap();
		void OnShow();
		void addSX(int n) override;
		void addSY(int n) override;
		void getHeroX(int x) override;
		void getHeroY(int y) override;
		int screenX(int x) override;
		int screenY(int y) override;
		//void setEnemys(Enemy **e);
		Enemy * returnEnemys(int n);
		void enemysLoadBitmap();
		void enemysOnMove();
		void enemysOnShow();
		bool bumpIntoEnemy(int x1, int x2, int y1, int y2) override;

	private:
		CMovingBitmap firstmap;
		Enemy enemys[2];
		int map[12][12];
		int sx, sy;							//地圖最左上角的座標
		int hx, hy;
		int stage_left, stage_top;
	};
}