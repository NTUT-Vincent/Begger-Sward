#include "ABoss.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Map1_2.h"
#include "Map1_3.h"
#include "Map1_4.h"
#include "Map2_1.h"
#include "Map2_2.h"
#include "Map2_3.h"
#include "Map2_4.h"
#include "Hero.h"
#include "Enemy.h"
#include "Util.h"
#include "Character.h"
#include "Scarecrow.h"
#include "GreenSlime.h"
#include "RedSlime.h"
#include "BlueSlime.h"
#include "RedGoblin.h"
#include "BlueGoblin.h"
#include "GreenGoblin.h"
#include "Box.h"
#include "PlayerStatus.h"

namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// mygame.h: 本檔案儲遊戲本身的class的interface							   //
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap selection;
		CMovingBitmap help;
		CMovingBitmap about;
		CMovingBitmap choose;
		int goto_status;								// 0是上面的 game start, 1是下面的 story
		bool isHelp;
		bool isAbout;
	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun : public CGameState 
	{
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void stage_process_move(Maps & stage_map, Hero & player, vector<Enemy*>& enemy_array, STAGE next_stage);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		bool allEnemyDie(vector<Enemy*> enemys);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		PlayerStatus	player_status;
		Map1_1			map_stg1_1;
		Map1_2			map_stg1_2;
		Map1_3			map_stg1_3;
		Map1_4			map_stg1_4;
		Map2_1			map_stg2_1;
		Map2_2			map_stg2_2;
		Map2_3			map_stg2_3;
		Map2_4			map_stg2_4;
		Hero			player1;
		vector<Enemy*>  enemys1_1;
		vector<Enemy*>  enemys1_2;
		vector<Enemy*>  enemys1_3;
		vector<Enemy*>  enemys1_4;
		vector<Enemy*>  enemys2_1;
		vector<Enemy*>  enemys2_2;
		vector<Enemy*>  enemys2_3;
		vector<Enemy*>  enemys2_4;
		STAGE			current_stage;
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		CMovingBitmap	corner;		// 角落圖
		CMovingBitmap you_win;
		CInteger		hits_left;	// 剩下的撞擊數
		bool isAllLevelPass;
		int all_level_pass_count;
		int change_song;
	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
		CAnimation gameover;
	};
}