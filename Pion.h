#pragma once
#include "Piece.h"
namespace gameObjects {
	class Pion : public Piece {
	public:
		Pion(bool isBlack);
		void playerMove() override;
	};
}