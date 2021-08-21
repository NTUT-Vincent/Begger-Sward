#ifndef CHARACTER_H
#define CHARACTER_H
#include "Maps.h"
namespace game_framework {
	class Character
	{
	protected:
		Character(string name) {				//每個角色都會有名稱，就像學名一樣，一對應一種
			_name = name;
		}
		Character() {
		}
		string getName();						//回傳角色名稱
		virtual void OnShow(Maps *m) {};
		int movement_speed;
	private:
		string _name;
	};
}
#endif