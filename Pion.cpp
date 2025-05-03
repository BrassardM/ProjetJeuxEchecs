#include "Pion.h"

gameObjects::Pion::Pion(bool isBlack, bool aDejaBouger) : Piece(std::vector<std::pair<int, int>>{
	{1, 0}
}
, false, isBlack, (QString)"C"), aDejaBouger_(aDejaBouger)
{
}