#include "Enemy.h"

namespace game_framework {

	class Map1_1 : public Maps
	{
	public:
		Map1_1();
		~Map1_1();
		void Initialize();
		//void setPos(int x, int y);			//不再使用setPos為不可穿透區域
		bool isEmpty(int x, int y) const;
		bool inFinishArea(int x, int y) override;
		void OnMove();
		void LoadBitmap();
		void OnShow();
		void getHeroX(int x) override;
		void getHeroY(int y) override;
		int screenX(int x) override;
		int screenY(int y) override;
		
	private:
		CMovingBitmap firstmap;
		int map[12][12];
		int hx, hy;
		int stage_left, stage_top;
	};
}