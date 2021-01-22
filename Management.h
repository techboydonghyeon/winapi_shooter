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

	// 오브젝트 풀
	using ObjectPool = unordered_map<enum Category, vector< Object*>>;
	using ObjectPoolIter = unordered_map<enum Category, vector< Object*>>::iterator;

	// 타일 풀
	using TilePool = vector<vector< Tile*>>;
	using TilePoolIter = vector<vector< Tile*>>::iterator;

	// 이미지 풀
	using ImagePool = map<string, class GdiImg*>;
	using ImagePoolIter = map<string, class GdiImg*>::iterator;



}
#endif // !__MANAGEMENT_H__
