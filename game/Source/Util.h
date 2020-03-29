#ifndef UTIL_H
#define UTIL_H

	/////////////////////////////////////////////////////////////////////////////
	// 這個.h file 定義了參數的值，可以直接從這裡取用						   //
	/////////////////////////////////////////////////////////////////////////////
	const int OBJS_DEFAULT_SPEED = 4; //物件固定移動速度
	const int SMOOTH_MOVE_TRESHHOLD = OBJS_DEFAULT_SPEED * 3 - 1; //平滑移動門檻值

	const int HERO_MOVE_SPEED = 5;//英雄移動速度

	const int MAX_ENEMY_PER_MAP = 10;//最大的敵人存量

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

#endif // !UTIL_H