#include "Piece.h"
#pragma once
namespace gameObjects {
	class Pion : public Piece {
	public:
		Pion(bool isBlack, bool aDejaBouger);
		bool getADejaBouger() const {}
	private:
		bool aDejaBouger_;
	};

}