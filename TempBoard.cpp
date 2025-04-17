#include "TempBoard.h"

gameInterface::TempBoard::TempBoard(const Board& input)
{
	board_ = new gameInterface::Board(input);
}

gameInterface::TempBoard::~TempBoard()
{
	delete board_;
}

gameInterface::Board* gameInterface::TempBoard::operator*()
{
	return board_;
}
