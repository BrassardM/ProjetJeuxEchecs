#include "Fou.h"

gameObjects::Fou::Fou(bool isBlack):Piece(std::vector<std::pair<int, int>>{
	{1, 1},
	{1,-1},
	{-1,1},
	{-1,-1}
}
, true, isBlack, (QString)"F")
{
}