#include "stdafx.h"
#include "Tile.h"
//--------------------------------------------------------
Tile::Tile(string ID_, int x_, int y_)
{
	ID = ID_,  x = x_,  y = y_;
	OBJECT->CreateTile(this);
}
//--------------------------------------------------------
void Tile::Render() 
{
	CAMERA->CAM_RENDER(ID, x, y);
}
//--------------------------------------------------------