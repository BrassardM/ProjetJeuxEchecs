#include "Tile.h"
#include <utility>
#include <set>

#pragma once
namespace gameInterface {
	class Board{
	public:
		Board();
		~Board();
		Board(const Board& other);

		void displayPiece(int x, int y, gameObjects::Piece* piece);
		QString displayTurn() const;
		void resetAttributes(bool defaultreset);
		std::vector<std::pair<int,QString>> updateBoard(int x, int y);
		std::vector<std::pair<int, QString>> updateBoard();
		std::vector<std::pair<int, QString>> addPiece(int x, int y, gameObjects::Piece* piece);
		gameObjects::Piece* stealPiece(int x, int y);
		QString checkCheck() const;
		bool ismoving() const;
	private:
		std::vector<std::pair<int, int>> checkValidMoves(int x, int y, bool blackTurnLocal) const;
		void initDefaultBoard();
		Tile* tiles[8][8];
		bool pieceMoving = false;
		std::pair<int,int> movingPos;
		std::vector<std::pair<int, int>> validMovingPosList;
		bool isBlackTurn = false;
		std::set<std::pair<int, int>> blackPieces;
		std::set<std::pair<int, int>> whitePieces;
		std::pair<int, int> blackKingPos;
		std::pair<int, int> whiteKingPos;
	};
}