#include "Tile.h"
#include "BoardState.h"
#include "LogMoves.h"
#include <utility>
#include <set>

#pragma once
namespace gameObjects {
	class Board{
	public:
		Board();
		~Board();
		Board(const Board& other);

		//pour les tests
		void playSequence(const std::vector<std::tuple<int, int,int,int>>& sequence);
		LogMoves& returnSequence(); // debug
		int nPieces() const; // test en passant
		bool checkCheckmate() const; // test checkmate & test promotion
		bool checkStalemate() const; // test promotion and all stalemate combinations
		bool checkInCheck() const; // test if in check
		bool checkKingPos(int x, int y); // test towering

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
		void logBoardState(bool sameTurn = false);
		void changePromotionPiece(int x, bool isBlack);

	private:
		std::vector<std::pair<int, int>> checkValidMoves(int x, int y, bool blackTurnLocal, bool canCastle = false) const;
		bool insufficientmaterial();
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

		//pour les tests
		LogMoves logMoves = {}; // only defaultreset (enough for all tests)
		
		int whiteProm = 0;
		int blackProm = 0;
	};
}