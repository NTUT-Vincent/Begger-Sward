#ifndef UTIL_H
#define UTIL_H

	/////////////////////////////////////////////////////////////////////////////
	// �o��.h file �w�q�F�Ѽƪ��ȡA�i�H�����q�o�̨���						   //
	/////////////////////////////////////////////////////////////////////////////
	const int OBJS_DEFAULT_SPEED = 4; //����T�w���ʳt��
	const int SMOOTH_MOVE_TRESHHOLD = OBJS_DEFAULT_SPEED * 3 - 1; //���Ʋ��ʪ��e��

	const int HERO_MOVE_SPEED = 5;//�^�����ʳt��

	const int MAX_ENEMY_PER_MAP = 10;//�̤j���ĤH�s�q

	const double PROB_ENEMY_TURN = 0.02;//�ĤH�۰���V���v
	const double PROB_ITEM_GEN = 0.005;//�����ĤH���_�������v
	///�H�U���U���
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_A = 0x41;
	const char KEY_Q = 0x51;
	const char KEY_W = 0x57;
	const char KEY_E = 0x45;
	const char KEY_R = 0x52;

#endif // !UTIL_H