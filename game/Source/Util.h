#ifndef UTIL_H
#define UTIL_H

	/////////////////////////////////////////////////////////////////////////////
	// 這個.h file 定義了參數的值，可以直接從這裡取用						   //
	/////////////////////////////////////////////////////////////////////////////
	constexpr int OBJS_DEFAULT_SPEED = 4; //物件固定移動速度;
	constexpr int SMOOTH_MOVE_TRESHOLD = OBJS_DEFAULT_SPEED * 3 - 1; //平滑移動門檻值
	constexpr int HERO_MOVE_SPEED = 5;		//英雄移動速度
	constexpr int SKILL_EVO_TVALUE = 22;	//技能進化的Treshold Value
	constexpr int MAX_ENEMY_PER_MAP = 10;//最大的敵人存量
	const double PROB_ENEMY_TURN = 0.02;//敵人自動轉向機率
	const double PROB_ITEM_GEN = 0.005;//打死敵人生寶物的機率
	///以下為各鍵值
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_A = 0x41;
	const char KEY_Q = 0x51;
	const char KEY_W = 0x57;
	const char KEY_E = 0x45;
	const char KEY_R = 0x52;
	const char CTRL = 17;
	const char NUM_0 = 0x30;	
	const char NUM_1 = 0x31;
	const char NUM_2 = 0x32;
	const char NUM_3 = 0x33;
	const char NUM_4 = 0x34;
	const char NUM_5 = 0x35;
	const char NUM_6 = 0x36;
	const char NUM_7 = 0x37;
	const char NUM_8 = 0x38;
	const char NUM_9 = 0x39	;
	//以下是一些留給跳躍關卡快捷鍵
	const char J_STG1_1 = 0x5A; //Z
	const char J_STG1_2 = 0x58 ; //X
	const char J_STG1_4 = 0x43; //C
	const char J_STG1_6 = 0x56; //V
	const char J_STG2_1 = 0x42; //B
	const char J_STG2_2 = 0x4E; //N
	const char J_STG2_3 = 0x4D; //M
	const char J_STG2_4 = 0x4A; //J
	///音效
	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT,				// 2
		AUDIO_GOLDENWIND,		// 3
		AUDIO_SWORD,			// 4
		AUDIO_FIRE,				//......以此類推
		AUDIO_SKILLE,			
		AUDIO_SKILLR_1,			
		AUDIO_SKILLR_2,			
		Audio_KNIFE,			
		AUDIO_ICE,
		AUDIO_HITTING,
		AUDIO_GRASSBALL,
		AUDIO_BEGGER,
		AUDIO_AWAKEN,
		AUDIO_DAMAGE1,
		AUDIO_ABOSS_WALK,
		AUDIO_ABOSS_PREPARE,
		AUDIO_GOODFLASH,
		AUDIO_BADFLASH,
		AUDIO_GAMEOVER,
		AUDIO_ICEBIRD_DIE,
		AUDIO_CHOOSE,
		AUDIO_BEING_ATTACKED,
		AUDIO_SCOLD,
		AUDIO_SHOE,
		AUDIO_SING
	};
	// 定義各關卡的編號
	enum STAGE {				
		STAGE_1_1,				
		STAGE_1_2,
		STAGE_1_3,
		STAGE_1_4,
		STAGE_2_1,
		STAGE_2_2,
		STAGE_2_3,
		STAGE_2_4,
		CONGRATULATION
	};
	// 定義各種屬性的編號
	enum ELEMENT_ATTRIBUTE {
		FIRE,					//火屬性
		ICE,					//冰屬性
		PLANT,					//植物屬性
		NO,

	};
	// 定義各種攻擊的編號
	enum ATTACK_NAME {
		FIRE_BALL,				//火球
		ICE_BALL,				//Q技能的冰
		GRASS_BALL,				//Q技能的草
		FIRE_FLAME,
		GRASS_TORNADO,
	};
#endif