#ifndef __ATTACK_H__
#define __ATTACK_H__
#include "Maps.h"
#include "Character.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Attack
	{
	public:
		Attack();
		Attack(int hx, int hy);
		bool HitEnemy(Enemy * enemy);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void LoadBitmap();				// 載入圖形
		bool isExist();
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetIsExist(bool flag);	// 設定是否正在往下移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
	protected:
		CMovingBitmap animation;		// 擦子的動畫
		int x, y;					// 擦子左上角座標
		bool is_exist;
	private:
		bool HitObject(int tx1, int ty1, int tx2, int ty2);
	};
}
#endif