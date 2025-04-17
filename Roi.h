#pragma once
#include "Piece.h"
#include "tooManyKings.h"

namespace gameObjects {
	class Roi : public Piece {
	public:
		Roi(bool isBlack, bool isTemp = false);
		virtual ~Roi();
	private:
		inline static int nRois = 0;
		bool isTemp_ = false;
	};
}