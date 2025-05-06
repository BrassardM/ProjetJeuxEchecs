#include "Tile.h"
#include "EtatEchequier.h"
#include "HistoriqueMouvements.h"
#include <utility>
#include <set>

/**
* Entête pour le module de l'échéquier qui contier les pièces et gère les règles du jeu. Fait partie du modèle. 
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

#pragma once
namespace gameObjects {
	const int DIMENSION_ECHEQUIER = 8;
	class Echequier{
	public:
		Echequier();
		~Echequier();
		Echequier(const Echequier& other);

		//pour les tests
		void playSequence(const std::vector<std::tuple<int, int,int,int>>& sequence);
		HistoriqueMouvements& returnSequence(); // debug
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
		Tile* tiles_[DIMENSION_ECHEQUIER][DIMENSION_ECHEQUIER];
		bool pieceMoving_ = false;
		std::pair<int,int> movingPos_;
		std::vector<std::pair<int, int>> validMovingPosList_;
		std::vector<EtatEchequier*> boardStateLog_ = {};
		bool isBlackTurn_ = false;
		std::set<std::pair<int, int>> blackPieces_;
		std::set<std::pair<int, int>> whitePieces_;
		std::pair<int, int> blackKingPos_;
		std::pair<int, int> whiteKingPos_;
		bool gameover_ = false;
		int sinceLastTaken_ = 0;
		std::pair<int, int> nextEnPassant_ = {-1,-1};

		//pour les tests
		HistoriqueMouvements logMoves_ = {}; // only defaultreset (enough for all tests)
		
		int whiteProm_ = 0;
		int blackProm_ = 0;
	};
}