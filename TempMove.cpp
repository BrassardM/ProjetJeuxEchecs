#include "TempMove.h"

using namespace gameObjects;

TempMove::TempMove(std::pair<int, int> originalPos, std::pair<int, int> stealpos, Board* input) : originalPos_(originalPos), movePos_(stealpos), board_(input)
{
	stolen = board_->stealPiece(stealpos.first,stealpos.second);
	gameObjects::Piece* movePiece = board_->stealPiece(originalPos.first, originalPos.second);
	board_->displayPiece(stealpos.first,stealpos.second,movePiece);
}

TempMove::~TempMove()
{
	gameObjects::Piece* movePiece = board_->stealPiece(movePos_.first, movePos_.second);
	board_->displayPiece(originalPos_.first, originalPos_.second, movePiece);
	board_->displayPiece(movePos_.first, movePos_.second, stolen);
}