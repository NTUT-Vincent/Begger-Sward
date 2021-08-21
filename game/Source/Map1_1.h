#include "Enemy.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖														   //
	/////////////////////////////////////////////////////////////////////////////
	class Map1_1 : public Maps
	{
	public:
		Map1_1();
		~Map1_1();
		void Initialize();
		void setPos(int x, int y, int n);			//將地圖座標的陣列設為傳入的數字
		void setClear(bool b);
		bool isEmpty(int x, int y) const;			//檢查是否為可以走的地方
		bool inFinishArea(int x, int y) override;	//是否在可以前往下一關的地方
		bool isOnIce(int x, int y);					//是否在冰上面
		void OnMove();
		void LoadBitmap();
		void OnShow();
		void getHeroX(int x) override;
		void getHeroY(int y) override;
		int screenX(int x) override;				//把絕對座標換成螢幕的做鰾
		int screenY(int y) override;
		void setIceWallPos(int x, int y, int n);	//設定icewall
	private:
		CMovingBitmap firstmap;
		CAnimation gate;
		bool all_enemy_clear;
		int map[12][12];
		int hx, hy;
		int stage_left, stage_top;
	};
}