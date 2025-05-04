#include "Board.h"
#pragma once

//RAII

namespace gameObjects {
	class TempMove {
	public:
		TempMove(std::pair<int, int> originalPos, std::pair<int, int> stealpos, Board* input);
		~TempMove();
	private :
		std::pair<int, int> originalPos_;
		std::pair<int, int> movePos_;
		gameObjects::Piece* stolen;
		Board* board_;
	};
}