#ifndef HERO_H
#define HERO_H
#include "Util.h"
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
#include "Attack.h"
#include "Item.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供玩家操控的hero											   //
	/////////////////////////////////////////////////////////////////////////////
	class Enemy;
	class Item;
	class Hero :public Character
	{
	public:
		Hero();
		~Hero();
		void LoadBitmap();
		void OnShow(Maps *m) override;
		void OnMove(Maps *m, vector<Enemy*> * enemys);
		int GetX1();					//回傳最左側X值
		int GetY1();					//回傳最上側Y值
		int GetX2();					//回傳最右側X值
		int GetY2();					//回傳最下側Y值
		int GetQCoolDown();				//回傳冷卻時間
		int GetWCoolDown();
		int GetECoolDown();
		int GetRCoolDown();
		int getHP();					//回傳HP
		int getFullHP();				//回傳滿血狀態的HP
		int get_attack_fire();			//回傳火屬性的攻擊力
		int get_attack_ice();
		int get_attack_plant();
		bool GetIsMovingLeft();			//回傳是否在移動
		bool GetIsMovingRight();
		bool GetIsMovingUp();
		bool GetIsMovingDown();
		int GetStepSize();				//回傳每次移動的距離
		ELEMENT_ATTRIBUTE getCurrentAttribute();		//回傳現在的屬性
		vector<Item *> * getItemsOfPlayer();			//回傳道具欄的VECTOR
		void Initialize();
		/////////////////////////////////////////////////////////////////////////////
		// 設定Hero的座標的函式們													   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
		void SetXY(int num_x, int num_y);
		void addSX(int n, Maps *m);
		void addSY(int n, Maps *m);
		/////////////////////////////////////////////////////////////////////////////
		// 設定Hero使用技能的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetUsingA(bool b);
		void SetUsingQ(bool b);
		void SetUsingW(bool b);
		void SetUsingE(bool b);
		void SetUsingR(bool b);
		void SetElementAttribute(ELEMENT_ATTRIBUTE e);
		void SetAllCoolDownToZero();
		/////////////////////////////////////////////////////////////////////////////
		// 前身是cantPass，應該是本程式最重要的函式之一								   //
		// 1. 角色碰到敵人會扣血													   //
		// 2. 如果敵人在攻擊範圍內，且在攻擊狀態下，敵人會被扣血						   //
		/////////////////////////////////////////////////////////////////////////////
		bool gonnaBleeding(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2);
		void offsetHp(int n);
		void addHp(int n);
		void addAttack(int n, ELEMENT_ATTRIBUTE attribute);
		void addItem(Item * item);
		void cleanItems();
		void slide(Maps *m);
		////////////////////用道具的
		void speedUp();
		void setSpeedUp(bool b);
		void protectiveCoverCount();
		void setCantBeDamaged(bool b);
		void showProtectiveCover(Maps *m);
		/////////////////////////////////////////////////////////////////////////////
		bool isMoving();					// 在動
		bool isAlive();
		bool isInFinishArea(Maps *m);
		bool isUsingSkill();			// 如果在用技能，return true	
		void heroShow(Maps *m);
		bool intercect(int x1, int x2, int y1, int y2);
		/////////////////////////////////////////////////////////////////////////////
		void normalAttackMove();		// 普功的Move
		void normalAttackShow(Maps *m);		// 普功的Show
		void showHeroStatus();			//顯示hp 技能冷卻時間
		void gettingAttackedShow();
		/////////////////////////////////////////////////////////////////////////////
		void skillQ(); 
		void skillQMove(Maps *m);
		void skillQShow(Maps *m);
		void useItem(int n);
		void setShadePosition();
		void skillWMove(Maps *m);
		void skillWShow(Maps *m);
		void skillEMove();
		void skillEShow();
		void skillRMove();
		void skillRShow();
		/////////////////////////////////////////////////////////////////////////////
	private:
		CMovingBitmap heroL, heroR;
		CMovingBitmap shadeL, shadeR;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation skillE;
		CAnimation skillR_L;
		CAnimation skillR_R;
		CAnimation normalAttackL; // 向左普功動畫
		CAnimation normalAttackR; // 向右普功動畫
		CAnimation get_attacked;
		CAnimation protective_cover;
		BloodBar blood_bar;
		CRect RectHero;
		int x, y;
		int hp;
		int attack_fire;				//三種屬性的攻擊力
		int attack_ice;
		int attack_plant;
		ELEMENT_ATTRIBUTE _attribute;	//英雄現在的屬性
		vector<Item *> items;			//存放道具欄裡面道具的vector
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttack;
		bool isUsingA;
		bool isUsingQ;
		bool isUsingW;
		bool isUsingE;
		bool isUsingR;
		bool is_getting_attacked;
		int status;
		bool directionLR;				// 0為左 1為右
		bool directionUD;				// 0為上 1為下
		int skillTimes;					// 用來數跑了幾次CAnimation。
		Attack q_attack;
		///冷卻時間
		int skill_q_cool_down;			//cool down在每個skill的move function裡每秒-30
		int skill_w_cool_down;
		int skill_e_cool_down;
		int skill_r_cool_down;			
		//滑起來
		int slide_right, slide_left, slide_up, slide_down;
		bool isSlide;
		//道具造成狀態
		int item_shoe_clock;
		bool isSpeedingUp;
		bool cantBeDamaged;
		int item_protective_cover_clock;
		int skillW_shadeX;						//閃現前原本的X座標
		int skillW_shadeY;						//閃現前原本的Y座標
		unsigned int skillW_shadeShowCount;
	};
}
#endif
