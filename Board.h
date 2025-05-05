#include "Tile.h"
#include "BoardState.h"
#include <utility>
#include <set>

#pragma once
namespace gameObjects {
	class Board{
	public:
		Board();
		~Board();
		Board(const Board& other);

		void displayPiece(int x, int y, gameObjects::Piece* piece);
		bool getBlackTurn() const;
		void resetAttributes(bool defaultreset);
		void updateBoard(int x, int y);
		void addPiece(int x, int y, gameObjects::Piece* piece);
		gameObjects::Piece* stealPiece(int x, int y);
		bool checkCheck(bool blackTurn) const;
		bool ismoving() const;
		std::vector<std::pair<int, QString>> operator*();
		bool getState() const;
		void checkGame();
		void logBoardState();
		void changePromotionPiece(int x, bool isBlack);

	private:
		std::vector<std::pair<int, int>> checkValidMoves(int x, int y, bool blackTurnLocal, bool canCastle = false) const;
		bool threeSameStates();
		void initDefaultBoard();
		void promote(int x, int y);
		bool miseEnEchec(int x, int y, std::pair<int, int> validMove);
		Tile* tiles[8][8];
		bool pieceMoving = false;
		std::pair<int,int> movingPos;
		std::vector<std::pair<int, int>> validMovingPosList;
		std::vector<BoardState*> boardStateLog = {};
		bool isBlackTurn = false;
		std::set<std::pair<int, int>> blackPieces;
		std::set<std::pair<int, int>> whitePieces;
		std::pair<int, int> blackKingPos;
		std::pair<int, int> whiteKingPos;
		bool gameover = false;
		int sincelasttaken = 0;
		std::pair<int, int> nextEnPassant = {-1,-1};
		
		int whiteProm = 0;
		int blackProm = 0;
	};
}