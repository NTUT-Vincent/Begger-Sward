#ifndef ABOSS_H
#define ABOSS_H
#include "Maps.h"
#include "Character.h"
#include "BossBloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人 												   //
	// 他是boss	 															   //
	/////////////////////////////////////////////////////////////////////////////
	class ABoss :public Enemy
	{
	public:
		ABoss();						//建構子，傳給Character角色名稱
		ABoss(int x, int y, Hero *h);	//建構子，設定角色初始位置給Character()，方便vector一次建立
		~ABoss();
		void LoadBitmap();					//加載敵人Bitmap
		void OnShow(Maps *m) override;		//顯示敵人於畫面上
		void OnMove(Maps *m);				//敵人移動
		int GetX1();						//回傳最左側X值
		int GetY1();						//回傳最上側Y值
		int GetX2();						//回傳最右側X值
		int GetY2();						//回傳最下側Y值
		void Initialize()override;			//初始化
		bool intersect(int x1, int x2, int y1, int y2) override;
		/////////////////////////////////////////////////////////////////////////////
		// 設定Enemy的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);		//  設定是否往下左右移動
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//
		void movement(Maps *m);			//決定角色移動的方式
		//用來攻擊的
		void attack();					//用來判定是否要攻擊//
		void iceAttack();				//判定是否要用冰的技能攻擊
		void iceAttackMove(Maps *m);	//ice_attack的onMove
		void iceAttackShow(Maps *m);	//ice_attack的onShow
	private:
		BossBloodBar boss_blood_bar;	//boss的血條
		CAnimation walkingLeft;			//向左右走的動畫
		CAnimation walkingRight;
		CAnimation normalAttackL;		//向左右攻擊的動畫
		CAnimation normalAttackR;
		CAnimation prepare_attackL;		//準備攻擊的動畫
		CAnimation prepare_attackR;
		CAnimation back_to_walkL;		//準備回到走路狀態的動畫
		CAnimation back_to_walkR;
		enum status {					//boss有的不同狀態，共有四種狀態			
			WALKING,
			PREPARE,
			ATTACK,
			BACK_TO_WALK
		};
		int status;						//boss的狀態
		int step_size;					//每次移動的速度
		int attack_damage;				//攻擊力
		bool isMovingRight;				//是否上下左右走
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;				//是否在攻擊
		int attack_cool_down;			//攻擊的冷卻時間
		int status_counter;				
		int move_or_not;				//是否有在移動
		int time_bump_into_sth;
		int attack_target_location_x, attack_target_location_y;  //要攻擊的標位置
		Attack q_attack;				
		Attack ice_attack[18];			//攻擊時丟的東西
		int skillTimes;					//用來算攻擊要飛多遠
		bool isUsingQ;
	};
}
#endif 