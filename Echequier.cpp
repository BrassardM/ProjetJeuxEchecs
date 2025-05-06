#include "Echequier.h"
#include "Roi.h"
#include "Chevalier.h"
#include "Fou.h"
#include "Reine.h"
#include "Tour.h"
#include "TropDeRois.h"
#include "Pion.h"

using namespace gameObjects;

/**
* Module d'échéquier. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


Echequier::Echequier()
{
	for (int x{}; x < DIMENSION_ECHEQUIER; x++) {
		for (int y{}; y < DIMENSION_ECHEQUIER; y++) {
			Tile* newtile = new Tile(x, y);
			tiles_[x][y] = newtile;
		}
	}
	//default reset
	initDefaultBoard();
	logBoardState();
}

Echequier::~Echequier()
{
	for (int i{}; i < DIMENSION_ECHEQUIER; i++) {
		for (int j{}; j < DIMENSION_ECHEQUIER; j++) {
			delete tiles_[i][j]->piece();
			delete tiles_[i][j];
		}
	}
	for (auto&& n : boardStateLog_) {
		delete n;
	}
}

Echequier::Echequier(const Echequier& other) : pieceMoving_(other.pieceMoving_), movingPos_(other.movingPos_), validMovingPosList_(other.validMovingPosList_), isBlackTurn_(other.isBlackTurn_), blackPieces_(other.blackPieces_), whitePieces_(other.whitePieces_), blackKingPos_(other.blackKingPos_), whiteKingPos_(other.whiteKingPos_)
{
	for (int x{}; x < DIMENSION_ECHEQUIER; x++) {
		for (int y{}; y < DIMENSION_ECHEQUIER; y++) {
			Tile* newtile = new Tile(*(other.tiles_[x][y]));
			tiles_[x][y] = newtile;
			if (other.tiles_[x][y]->piece() != nullptr) {
				if (dynamic_cast<gameObjects::Roi*>(other.tiles_[x][y]->piece()) != NULL) {
					gameObjects::Roi* roitemp = new gameObjects::Roi(other.tiles_[x][y]->piece()->isBlack(), true);
					addPiece(x, y, roitemp);
				}
				else if (dynamic_cast<gameObjects::Chevalier*>(other.tiles_[x][y]->piece()) != NULL) {
					gameObjects::Chevalier* chevtemp = new gameObjects::Chevalier(other.tiles_[x][y]->piece()->isBlack());
					addPiece(x, y, chevtemp);
				}
				else if (dynamic_cast<gameObjects::Fou*>(other.tiles_[x][y]->piece()) != NULL) {
					gameObjects::Fou* foutemp = new gameObjects::Fou(other.tiles_[x][y]->piece()->isBlack());
					addPiece(x, y, foutemp);
				}
				//Ajouter tout les pieces quand elles vont être finies
			}
		}
	}
}

void gameObjects::Echequier::playSequence(const std::vector<std::tuple<int, int, int, int>>& sequence)
{
	resetAttributes(true);
	int blackPromBack = blackProm_;
	int whitePromBack = whiteProm_;
	for (auto&& n : sequence) {
		blackProm_ = get<2>(n);
		whiteProm_ = get<3>(n);
		updateBoard(std::get<0>(n), std::get<1>(n));
	}
	blackProm_ = blackPromBack;
	whiteProm_ = whitePromBack;
}

HistoriqueMouvements& gameObjects::Echequier::returnSequence()
{
	return logMoves_;
}

int gameObjects::Echequier::nPieces() const
{
	return (int)blackPieces_.size() + (int)whitePieces_.size();
}

bool gameObjects::Echequier::checkCheckmate() const
{
	return checkCheck(isBlackTurn_) && gameover_;
}

bool gameObjects::Echequier::checkStalemate() const
{
	return !checkCheck(isBlackTurn_) && gameover_;
}

bool gameObjects::Echequier::checkInCheck() const
{
	return checkCheck(isBlackTurn_);
}

bool gameObjects::Echequier::checkKingPos(int x, int y)
{
	return (std::pair<int,int>(x,y) == blackKingPos_ || std::pair<int, int>(x, y) == whiteKingPos_);
}

bool Echequier::getBlackTurn() const
{
	return isBlackTurn_;
}



void Echequier::resetAttributes(bool defaultreset)
{
	movingPos_ = {};
	pieceMoving_ = false;
	isBlackTurn_ = false;
	validMovingPosList_ = {};
	blackKingPos_ = {-1,-1};
	whiteKingPos_ = {-1,-1};
	nextEnPassant_ = { -1,-1 };
	blackPieces_ = {};
	whitePieces_ = {};
	gameover_ = false;
	sinceLastTaken_ = 0;
	logMoves_ = {};

	for (auto&& n : boardStateLog_) {
		delete n;
	}
	boardStateLog_ = {};

	for (int i{}; i < DIMENSION_ECHEQUIER; i++) {
		for (int j{}; j < DIMENSION_ECHEQUIER; j++) {
			if (tiles_[i][j]->piece() != nullptr) {
				gameObjects::Piece* todelete = tiles_[i][j]->piece();
				tiles_[i][j]->removePiece();
				delete todelete;
			}
			tiles_[i][j]->removeValid();
		}
	}
	if (defaultreset) {
		initDefaultBoard();
	}
	logBoardState();
}

void Echequier::updateBoard(int x, int y)
{
	if (!gameover_){
		if (pieceMoving_ == true) {
			if (tiles_[x][y]->isValidMove()) {
				if (tiles_[x][y]->piece() != nullptr) {
					sinceLastTaken_ = -1;
					gameObjects::Piece* todelete = tiles_[x][y]->piece();
					tiles_[x][y]->removePiece();
					if (todelete->isBlack()) {
						blackPieces_.erase(std::pair<int, int>(x, y));
					}
					else {
						whitePieces_.erase(std::pair<int, int>(x, y));
					}
					delete todelete; //DELETING PIECES
				}
				// en passant
				else if ((dynamic_cast<Pion*>(tiles_[movingPos_.first][movingPos_.second]->piece()) != NULL) && (abs(movingPos_.first - x) - abs(movingPos_.second - y) == 0)){
					sinceLastTaken_ = -1;
					gameObjects::Piece* todelete = tiles_[x- (1 - 2 * isBlackTurn_)][y]->piece();
					tiles_[x- (1 - 2 * isBlackTurn_)][y]->removePiece();
					if (todelete->isBlack()) {
						blackPieces_.erase(std::pair<int, int>(x- (1 - 2 * isBlackTurn_), y));
					}
					else {
						whitePieces_.erase(std::pair<int, int>(x- (1 - 2 * isBlackTurn_), y));
					}
					delete todelete; //DELETING PIECES
				}
				tiles_[x][y]->movePiece(tiles_[movingPos_.first][movingPos_.second]->piece());
				tiles_[movingPos_.first][movingPos_.second]->removePiece();
				if (tiles_[x][y]->piece()->isBlack()) {
					blackPieces_.erase(std::pair<int, int>(movingPos_.first, movingPos_.second));
					blackPieces_.insert(std::pair<int, int>(x, y));
					if (tiles_[x][y]->isRoi()) {
						blackKingPos_ = std::pair<int, int>{ x,y };
					}
				}
				else {
					whitePieces_.erase(std::pair<int, int>(movingPos_.first, movingPos_.second));
					whitePieces_.insert(std::pair<int, int>(x, y));
					if (tiles_[x][y]->isRoi()) {
						whiteKingPos_ = std::pair<int, int>{ x,y };
					}
				}

				//castling
				if ((movingPos_.second - y == -2) && dynamic_cast<Roi*>(tiles_[x][y]->piece()) != NULL) {
					tiles_[x][y - 1]->movePiece(tiles_[x][y + 1]->piece());
					tiles_[x][y + 1]->removePiece();
					if (isBlackTurn_) {
						blackPieces_.erase(std::pair<int, int>{x, y + 1});
						blackPieces_.insert(std::pair<int, int>{x, y - 1});
					}
					else {
						whitePieces_.erase(std::pair<int, int>{x, y + 1});
						whitePieces_.insert(std::pair<int, int>{x, y - 1});
					}
				}
				else if ((movingPos_.second - y == 2) && dynamic_cast<Roi*>(tiles_[x][y]->piece()) != NULL) {
					tiles_[x][y + 1]->movePiece(tiles_[x][y - 2]->piece());
					tiles_[x][y - 2]->removePiece();
					if (isBlackTurn_) {
						blackPieces_.erase(std::pair<int, int>{x, y - 2});
						blackPieces_.insert(std::pair<int, int>{x, y + 1});
					}
					else {
						whitePieces_.erase(std::pair<int, int>{x, y - 2});
						whitePieces_.insert(std::pair<int, int>{x, y + 1});
					}
				}
 
				//promoting
				if ((x == 7 || x == 0) && dynamic_cast<Pion*>(tiles_[x][y]->piece()) != NULL) {
					promote(x, y);
				}
				//next en passant
				if (dynamic_cast<Pion*>(tiles_[x][y]->piece()) != NULL && (abs(movingPos_.first - x) == 2)) {
					nextEnPassant_ = std::pair<int, int>{movingPos_.first + (1-2*isBlackTurn_),y};
				}
				else {
					nextEnPassant_ = std::pair<int, int>{ -1,-1 };
				}
				
				isBlackTurn_ = not(isBlackTurn_);
				tiles_[x][y]->piece()->playerMove();
				sinceLastTaken_++;
				logBoardState();
				checkGame();
				
				//pour faire les tests
				std::tuple<int, int, int, int> log = { movingPos_.first, movingPos_.second, blackProm_, whiteProm_};
				logMoves_ += log;
				std::tuple<int, int, int, int> log2 = { x, y, blackProm_, whiteProm_ };
				logMoves_ += log2;
			}

			for (auto&& n : validMovingPosList_) {
				tiles_[n.first][n.second]->removeValid();
			}
			pieceMoving_ = false;
		}
		else {
			if (tiles_[x][y]->piece() != nullptr) {
				if ((tiles_[x][y]->piece()->isBlack() == isBlackTurn_)) {
					std::vector<std::pair<int, int>> validBeforeCheck = checkValidMoves(x, y, isBlackTurn_, true);
					std::vector<std::pair<int, int>> newValidMoves;

					for (auto&& n : validBeforeCheck) {
						if (miseEnEchec(x, y, n) == false) {
							newValidMoves.push_back(n);
							tiles_[n.first][n.second]->addValid();
						}
					}
					if (!(newValidMoves.empty())) {
						pieceMoving_ = true;
						validMovingPosList_ = move(newValidMoves);
						movingPos_ = std::pair<int, int>(x, y);
					}
				}
			}
		}
	}
}

void Echequier::displayPiece(int x, int y, gameObjects::Piece* piece) {
	if (piece != nullptr) {
		tiles_[x][y]->movePiece(piece);
	}
}

void Echequier::addPiece(int x, int y, gameObjects::Piece* piece)
{
	if (tiles_[x][y]->piece() != nullptr) {
		gameObjects::Piece* todelete = tiles_[x][y]->piece();
		tiles_[x][y]->removePiece();
		if (todelete->isBlack()) {
			blackPieces_.erase(std::pair<int,int>{ x,y });
		}
		else {
			whitePieces_.erase(std::pair<int, int>{ x, y });
		}
		delete todelete;
	}
	if (piece != nullptr) {
		tiles_[x][y]->movePiece(piece);
		if (piece->isBlack()) {
			blackPieces_.insert(std::pair<int, int>{ x, y });
			if (tiles_[x][y]->isRoi()) {
				blackKingPos_ = std::pair<int, int>{ x,y };
			}
		}
		else {
			whitePieces_.insert(std::pair<int, int>{x, y});
			if (tiles_[x][y]->isRoi()) {
				whiteKingPos_ = std::pair<int, int>{ x,y };
			}
		}
	}
}

gameObjects::Piece* Echequier::stealPiece(int x, int y)
{
	gameObjects::Piece* outpiece = tiles_[x][y]->piece();
	tiles_[x][y]->removePiece();
	
	return outpiece;
}

bool Echequier::checkCheck(bool blackTurn) const
{
	bool found = false;
	if (blackTurn) {
		for (auto&& n : whitePieces_) {
			auto validMoves = checkValidMoves(n.first, n.second, false);
			for (auto m : validMoves) {
				if (m == blackKingPos_) {
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}
	else {
		for (auto&& n : blackPieces_) {
			auto validMoves = checkValidMoves(n.first, n.second, true);
			for (auto m : validMoves) {
				if (m == whiteKingPos_) {
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}
	return found;
}

bool Echequier::ismoving() const
{
	return pieceMoving_;
}

std::vector<std::pair<int, QString>> gameObjects::Echequier::operator*()
{
	std::vector<std::pair<int, QString>> outVect;
	for (int x{}; x < DIMENSION_ECHEQUIER; x++) {
		for (int y{}; y < DIMENSION_ECHEQUIER; y++) {
			outVect.push_back(std::pair<int, QString>{(x + y * DIMENSION_ECHEQUIER), ** tiles_[x][y]});
		}
	}
	return outVect;
}

bool gameObjects::Echequier::getState() const {
	return gameover_;
};

void gameObjects::Echequier::checkGame()
{
	gameover_ = true;

	if (blackKingPos_ != std::pair<int,int>{-1,-1} || whiteKingPos_ != std::pair<int, int>{-1, -1}) {
		if (!threeSameStates()) {
			if (!insufficientmaterial()) {
				if (sinceLastTaken_ < 100) { //50 move rule
					if (isBlackTurn_) {
						for (auto&& n : blackPieces_) {
							auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn_);
							for (auto&& m : validMoves) {
								gameover_ = gameover_ && miseEnEchec(n.first, n.second, m);
							}
						}
					}
					else {
						for (auto&& n : whitePieces_) {
							auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn_);
							for (auto&& m : validMoves) {
								gameover_ = gameover_ && miseEnEchec(n.first, n.second, m);
							}
						}
					}
				}
			}
		}
	}
}

void gameObjects::Echequier::logBoardState(bool sameTurn)
{
	std::set<std::tuple<int, int, QString>> setPieces;
	for (auto&& n : blackPieces_) {
		setPieces.insert(std::tuple<int, int, QString>{n.first, n.second, tiles_[n.first][n.second]->operator*() });
	}
	for (auto&& n : whitePieces_) {
		setPieces.insert(std::tuple<int, int, QString>{n.first, n.second, tiles_[n.first][n.second]->operator*() });
	}
	EtatEchequier* b;
	if (blackKingPos_ == std::pair<int,int>(-1,-1) || whiteKingPos_ == std::pair<int, int>(-1, -1)) {
		b = new EtatEchequier(setPieces, isBlackTurn_, false, false);
	}
	else {
		b = new EtatEchequier(setPieces, isBlackTurn_, !(tiles_[blackKingPos_.first][blackKingPos_.second]->piece()->getHasMoved()), !(tiles_[whiteKingPos_.first][whiteKingPos_.second]->piece()->getHasMoved()));
	}
	if (sameTurn) {
		boardStateLog_.pop_back();
		boardStateLog_.push_back(b);
	}
	else {
		boardStateLog_.push_back(b);
	}
}

void gameObjects::Echequier::changePromotionPiece(int x, bool isBlack)
{
	if (isBlack) {
		blackProm_ = x;
	}
	else {
		whiteProm_ = x;
	}
}

std::vector<std::pair<int, int>> Echequier::checkValidMoves(int x, int y, bool blackTurnLocal, bool canCastle) const
{
	std::vector<std::pair<int, int>> possValidMoves = (tiles_[x][y]->piece()->returnMoves());
	std::vector<std::pair<int, int>> newValidMoves;
	//movesStraight
	if (tiles_[x][y]->piece()->getStraight()) {
		bool hasLOS = true;
		for (auto&& n : possValidMoves) {
			if (abs(x - n.first) <= 1 && abs(y - n.second) <= 1) {
				hasLOS = true;
			}
			if (hasLOS) {
				if (tiles_[n.first][n.second]->piece() == nullptr) {
					newValidMoves.push_back(n);
				}
				else {
					if (tiles_[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
						newValidMoves.push_back(n);

					}
					hasLOS = false;
				}
			}
		}
	}
	//is pawn
	else if (dynamic_cast<Pion*>(tiles_[x][y]->piece()) != NULL) {
		for (auto&& n : possValidMoves) {
			if ((abs(n.first - x) - abs(n.second - y)) != 0) {
				if (tiles_[n.first][n.second]->piece() == nullptr) {
					newValidMoves.push_back(n);
				}
			}
			else {
				if (tiles_[n.first][n.second]->piece() != nullptr) {
					if (tiles_[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
						newValidMoves.push_back(n);
					}
				}
				else if (n == nextEnPassant_) {
					newValidMoves.push_back(n);
				}
			}
		}
	}
	//is king that can castle
	else if (canCastle && (dynamic_cast<Roi*>(tiles_[x][y]->piece()) != NULL) && (tiles_[x][y]->piece()->getHasMoved() == false)) {
		for (auto&& n : possValidMoves) {
			if ((n.second - y) == 2) {
				if ((y + 3) <= 7) {
					if ((dynamic_cast<Tour*>(tiles_[x][y + 3]->piece()) != NULL) && (tiles_[x][y + 3]->piece()->isBlack() == tiles_[x][y]->piece()->isBlack()) && tiles_[x][y + 3]->piece()->getHasMoved() == false && (tiles_[x][y + 1]->piece() == nullptr) && (tiles_[x][y + 2]->piece() == nullptr) && !checkCheck(isBlackTurn_)) {
						newValidMoves.push_back(n);
					}
				}
			}
			else if ((n.second - y) == -2) {
				if ((y - 4) >= 0) {
					if ((dynamic_cast<Tour*>(tiles_[x][y - 4]->piece()) != NULL) && (tiles_[x][y - 4]->piece()->isBlack() == tiles_[x][y]->piece()->isBlack()) && tiles_[x][y - 4]->piece()->getHasMoved() == false && (tiles_[x][y - 1]->piece() == nullptr) && (tiles_[x][y - 2]->piece() == nullptr) && (tiles_[x][y - 3]->piece() == nullptr) && !checkCheck(isBlackTurn_)) {
						newValidMoves.push_back(n);
					}
				}
			}
			else if (tiles_[n.first][n.second]->piece() == nullptr) {
				newValidMoves.push_back(n);
			}
			else {
				if (tiles_[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
					newValidMoves.push_back(n);
				}
			}
		}
	}
	//no need LOS
	else {
		for (auto&& n : possValidMoves) {
			if (tiles_[n.first][n.second]->piece() == nullptr) {
				newValidMoves.push_back(n);
			}
			else {
				if (tiles_[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
					newValidMoves.push_back(n);
				}
			}
		}
	}
	return newValidMoves;
}

bool gameObjects::Echequier::insufficientmaterial()
{
	int nP{};

	bool insufficientMatN = true;
	for (auto&& n : blackPieces_) {
		if (dynamic_cast<Reine*>(tiles_[n.first][n.second]->piece()) != NULL || dynamic_cast<Tour*>(tiles_[n.first][n.second]->piece()) != NULL || dynamic_cast<Pion*>(tiles_[n.first][n.second]->piece()) != NULL) {
			insufficientMatN = false;
			break;
		}
		else if (dynamic_cast<Fou*>(tiles_[n.first][n.second]->piece()) != NULL || dynamic_cast<Chevalier*>(tiles_[n.first][n.second]->piece()) != NULL) {
			nP++;
			if (nP > 1) {
				insufficientMatN = false;
			}
		}
	}

	bool insufficientMatB = true;
	nP = {};
	for (auto&& n : whitePieces_) {
		if (dynamic_cast<Reine*>(tiles_[n.first][n.second]->piece()) != NULL || dynamic_cast<Tour*>(tiles_[n.first][n.second]->piece()) != NULL || dynamic_cast<Pion*>(tiles_[n.first][n.second]->piece()) != NULL) {
			insufficientMatB = false;
			break;
		}
		else if (dynamic_cast<Fou*>(tiles_[n.first][n.second]->piece()) != NULL || dynamic_cast<Chevalier*>(tiles_[n.first][n.second]->piece()) != NULL) {
			nP++;
			if (nP > 1) {
				insufficientMatB = false;
				break;
			}
		}
	}
	return (insufficientMatN && insufficientMatB);
}

bool gameObjects::Echequier::threeSameStates()
{
	int equalsCounter = 0;
	EtatEchequier b = *(boardStateLog_.back());
	for (auto it = boardStateLog_.begin(); it != (boardStateLog_.end() - 1); it++) {
		EtatEchequier a = **it;
		if (a.operator==(b)) {
			equalsCounter++;
		}
	}
	return (equalsCounter > 1);
}

void Echequier::initDefaultBoard()
{
	//creation des pieces
	gameObjects::Roi* rb = new gameObjects::Roi(true);
	gameObjects::Roi* rw = new gameObjects::Roi(false);

	gameObjects::Fou* f1b = new gameObjects::Fou(true);
	gameObjects::Fou* f2b = new gameObjects::Fou(true);
	gameObjects::Fou* f1w = new gameObjects::Fou(false);
	gameObjects::Fou* f2w = new gameObjects::Fou(false);

	gameObjects::Chevalier* c1b = new gameObjects::Chevalier(true);
	gameObjects::Chevalier* c2b = new gameObjects::Chevalier(true);
	gameObjects::Chevalier* c1w = new gameObjects::Chevalier(false);
	gameObjects::Chevalier* c2w = new gameObjects::Chevalier(false);

	gameObjects::Reine* qb = new gameObjects::Reine(true);
	gameObjects::Reine* qw = new gameObjects::Reine(false);

	gameObjects::Tour* t1b = new gameObjects::Tour(true);
	gameObjects::Tour* t2b = new gameObjects::Tour(true);
	gameObjects::Tour* t1w = new gameObjects::Tour(false);
	gameObjects::Tour* t2w = new gameObjects::Tour(false);

	gameObjects::Pion* p1b = new gameObjects::Pion(true);
	gameObjects::Pion* p2b = new gameObjects::Pion(true);
	gameObjects::Pion* p3b = new gameObjects::Pion(true);
	gameObjects::Pion* p4b = new gameObjects::Pion(true);
	gameObjects::Pion* p5b = new gameObjects::Pion(true);
	gameObjects::Pion* p6b = new gameObjects::Pion(true);
	gameObjects::Pion* p7b = new gameObjects::Pion(true);
	gameObjects::Pion* p8b = new gameObjects::Pion(true);

	gameObjects::Pion* p1w = new gameObjects::Pion(false);
	gameObjects::Pion* p2w = new gameObjects::Pion(false);
	gameObjects::Pion* p3w = new gameObjects::Pion(false);
	gameObjects::Pion* p4w = new gameObjects::Pion(false);
	gameObjects::Pion* p5w = new gameObjects::Pion(false);
	gameObjects::Pion* p6w = new gameObjects::Pion(false);
	gameObjects::Pion* p7w = new gameObjects::Pion(false);
	gameObjects::Pion* p8w = new gameObjects::Pion(false);


	//placement des pieces
	addPiece(7, 4, rb);
	addPiece(0, 4, rw);

	addPiece(7, 5, f1b);
	addPiece(7, 2, f2b);
	addPiece(0, 5, f1w);
	addPiece(0, 2, f2w);

	addPiece(7, 6, c1b);
	addPiece(7, 1, c2b);
	addPiece(0, 6, c1w);
	addPiece(0, 1, c2w);

	addPiece(7, 3, qb);
	addPiece(0, 3, qw);

	addPiece(7, 7, t1b);
	addPiece(7, 0, t2b);
	addPiece(0, 7, t1w);
	addPiece(0, 0, t2w);

	addPiece(6, 7, p1b);
	addPiece(6, 6, p2b);
	addPiece(6, 5, p3b);
	addPiece(6, 4, p4b);
	addPiece(6, 3, p5b);
	addPiece(6, 2, p6b);
	addPiece(6, 1, p7b);
	addPiece(6, 0, p8b);
	addPiece(1, 7, p1w);
	addPiece(1, 6, p2w);
	addPiece(1, 5, p3w);
	addPiece(1, 4, p4w);
	addPiece(1, 3, p5w);
	addPiece(1, 2, p6w);
	addPiece(1, 1, p7w);
	addPiece(1, 0, p8w);
}

void gameObjects::Echequier::promote(int x, int y)
{
	gameObjects::Piece* todelete = tiles_[x][y]->piece();
	tiles_[x][y]->removePiece();
	delete todelete;
	if (isBlackTurn_) {
		if (blackProm_ == 0) {
			Reine* q = new Reine(isBlackTurn_);
			addPiece(x, y, q);
		}
		else if (blackProm_ == 1) {
			Fou* f = new Fou(isBlackTurn_);
			addPiece(x, y, f);
		}
		else if (blackProm_ == 2) {
			Tour* t = new Tour(isBlackTurn_);
			addPiece(x, y, t);
		}
		else {
			Chevalier* c = new Chevalier(isBlackTurn_);
			addPiece(x, y, c);
		}
	}
	else {
		if (whiteProm_ == 0) {
			Reine* q = new Reine(isBlackTurn_);
			addPiece(x, y, q);
		}
		else if (whiteProm_ == 1) {
			Fou* f = new Fou(isBlackTurn_);
			addPiece(x, y, f);
		}
		else if (whiteProm_ == 2) {
			Tour* t = new Tour(isBlackTurn_);
			addPiece(x, y, t);
		}
		else {
			Chevalier* c = new Chevalier(isBlackTurn_);
			addPiece(x, y, c);
		}
	}
}

bool gameObjects::Echequier::miseEnEchec(int x, int y, std::pair<int, int> validMove)
{
	Piece* current = stealPiece(x, y);
	std::pair<int, int> blackKingPosBackup = blackKingPos_;
	std::pair<int, int> whiteKingPosBackup = whiteKingPos_;
	if (dynamic_cast<Roi*>(current) != NULL) {
		if (isBlackTurn_) {
			blackKingPos_ = {validMove.first,validMove.second};
		}
		else {
			whiteKingPos_ = { validMove.first, validMove.second };
		}
	}
	Piece* replaced = nullptr;
	if (tiles_[validMove.first][validMove.second]->piece() != nullptr) {
		replaced = stealPiece(validMove.first, validMove.second);
		if (isBlackTurn_) {
			whitePieces_.erase({ validMove.first,validMove.second });
		}
		else {
			blackPieces_.erase({ validMove.first,validMove.second });
		}
	}
	displayPiece(validMove.first, validMove.second, current);
	bool miseEnEchec = checkCheck(isBlackTurn_);
	displayPiece(x, y, current);
	tiles_[validMove.first][validMove.second]->removePiece();
	if (replaced != nullptr) {
		if (isBlackTurn_) {
			whitePieces_.insert({ validMove.first,validMove.second });
		}
		else {
			blackPieces_.insert({ validMove.first,validMove.second });
		}
		displayPiece(validMove.first, validMove.second, replaced);
	}
	blackKingPos_ = blackKingPosBackup; 
	whiteKingPos_ = whiteKingPosBackup;
	return miseEnEchec;
}