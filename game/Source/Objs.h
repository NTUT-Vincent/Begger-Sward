#ifndef OBJS_H
#define OBJS_H


namespace game_framework {
	enum Direction
	{dirUp, dirDown, dirLeft, dirRight};
	enum ObjsAttribute
	{
		noDirObject,
		noMapCollisionObj,
		noCharacterCollisionObj,
		noAttackCollisionObj,
		altAllignMapObj
	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class�w�q�F���󪺦@�P����										   //
	/////////////////////////////////////////////////////////////////////////////
	class Objs
	{
	private:
		int x, y;
		int collisionCount;//�I�����ơA�]�p���ۨ���Enemy
		bool isMoving;//�b����(eg.Item���|����)
		bool isVisible;//�O�i����
		bool postToDead;

		Direction dir;
		ObjsAttribute att;
	protected:

	public:
		virtual void OnMove();
		virtual void OnShow();
		
		void RandomDirection();
		void CenterBy();
		
	};
	

	
}

#endif // !OBJS_H