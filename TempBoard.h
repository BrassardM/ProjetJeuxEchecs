#include "Board.h"
#pragma once

//RAII

namespace gameInterface {
	class TempBoard {
	public:
		TempBoard(const Board& input);
		~TempBoard();
		Board* operator*();
	private :
		Board* board_;
	};
}