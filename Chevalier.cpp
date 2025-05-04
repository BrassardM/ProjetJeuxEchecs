#include "Chevalier.h"

gameObjects::Chevalier::Chevalier(bool isBlack) : Piece(std::vector<std::pair<int, int>>{
	{2, 1},
	{2,-1},
	{1,2},
	{1,-2},
	{-1,2},
	{-1,-2},
	{-2,1},
	{-2,-1}
}
, false, isBlack, (QString)"C")
{
}