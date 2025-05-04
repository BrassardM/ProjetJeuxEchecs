#include "Tour.h"

gameObjects::Tour::Tour(bool isBlack) : Piece(std::vector<std::pair<int, int>>{
	{ 1, 0 },
	{ 0, 1 },
	{ 0,-1 },
	{ -1, 0 },
}
, true, isBlack, (QString)"T")
{
}
