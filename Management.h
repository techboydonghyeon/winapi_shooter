#pragma once
#include "stdafx.h"

#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__
#include "ObjectInfo.h"
class Object;
class Tile;
namespace Management
{

	using namespace ObjectInfo;

	// ������Ʈ Ǯ
	using ObjectPool = unordered_map<enum Category, vector< Object*>>;
	using ObjectPoolIter = unordered_map<enum Category, vector< Object*>>::iterator;

	// Ÿ�� Ǯ
	using TilePool = vector<vector< Tile*>>;
	using TilePoolIter = vector<vector< Tile*>>::iterator;

	// �̹��� Ǯ
	using ImagePool = map<string, class GdiImg*>;
	using ImagePoolIter = map<string, class GdiImg*>::iterator;



}
#endif // !__MANAGEMENT_H__
