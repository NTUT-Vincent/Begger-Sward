#ifndef CHARACTER_H
#define CHARACTER_H


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class Character
	{
	protected:
		Character(string name) {
			_name = name;
		}

		Character() {

		}


	private:
		string _name;

	};
	

	
}

#endif // !CHARACTER_H