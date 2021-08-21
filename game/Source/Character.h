#ifndef CHARACTER_H
#define CHARACTER_H
#include "Maps.h"
namespace game_framework {
	class Character
	{
	protected:
		Character(string name) {				//�C�Ө��ⳣ�|���W�١A�N���ǦW�@�ˡA�@�����@��
			_name = name;
		}
		Character() {
		}
		string getName();						//�^�Ǩ���W��
		virtual void OnShow(Maps *m) {};
		int movement_speed;
	private:
		string _name;
	};
}
#endif