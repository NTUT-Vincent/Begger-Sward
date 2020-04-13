#include "Enemy.h"

namespace game_framework {

	class Map1_6 : public Maps
	{
	public:
		Map1_6();
		~Map1_6();
		//void setPos(int x, int y);			//���A�ϥ�setPos�����i��z�ϰ�
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
		/*vector<Enemy*> returnEnemys() ;
		void enemysLoadBitmap();
		void enemysOnMove();
		void enemysOnShow();
		bool bumpIntoEnemy(int x1, int x2, int y1, int y2) override;*/

	private:
		CMovingBitmap firstmap;
		/*Enemy enemys[2];
		vector<Enemy*> enemysV;*/
		int map[25][25];
		int sx, sy;							//�a�ϳ̥��W�����y��
		int hx, hy;
		int stage_left, stage_top;
	};
}