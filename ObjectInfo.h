#pragma once

#ifndef __OBJECT_INFO_H__
#define __OBJECT_INFO_H__

namespace ObjectInfo
{
	enum Category
	{
		C_PLAYER,
		C_ENEMY,
		C_BULLET,
		C_ITEM,
		C_STRUCT,
		END_CATEGORY
	};

	enum ObjectID
	{
		P_PINKY,
		E_DUCK,
		E_KAMIKAZE,
		B_SINGLE,
		B_SHOTGUN,
		B_AUTO,
		I_GUN,
		I_BOMB,
		I_HEAL_SHILD,
		END_OBJECTID
	};

	enum TileID
	{
		END_TILEID
	};
}

#endif // !__OBJECT_INFO_H__
