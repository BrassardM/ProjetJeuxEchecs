#include "Piece.h"
#include <utility>
#include <set>
#pragma once
namespace gameObjects {
	class BoardState {
	public:
		BoardState(std::set<std::tuple<int, int, QString>> pieces, bool isBlack, bool blackCanCastle, bool whiteCanCastle);
		bool operator==(const BoardState& other);
	private:
		bool isBlack_;
		std::set<std::tuple<int, int, QString>> pieces_;
		bool blackCanCastle_;
		bool whiteCanCastle_;
	};
}