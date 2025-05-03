#include "Reine.h"

gameObjects::Reine::Reine(bool isBlack) :Piece(std::vector<std::pair<int, int>>{
	{1, 1},
	{ 1,-1 },
	{ -1,1 },
	{ -1,-1 },
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
}
, true, isBlack, (QString)"F")
{
}