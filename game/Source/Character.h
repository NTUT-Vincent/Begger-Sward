#ifndef CHARACTER_H
#define CHARACTER_H


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class Character
	{
	protected:
		Character(int hp) {
			_hp = hp;
		}


	private:
		int _hp;

	};
	

	
}

#endif // !CHARACTER_H