#pragma once
#include <utility>
#include <vector>
#include <QString>

/**
* Ent�te pour le module repr�sentant une pi�ce d'�checs. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/

namespace gameObjects {
	class Piece
	{
	public:
		Piece();
		Piece(Piece& other);
		Piece(std::vector<std::pair<int, int>> movesPattern, bool movesStraight, bool isBlack, QString textI);
		void movePos(int x, int y);
		virtual void playerMove();
		bool isBlack();
		bool getStraight() const;
		virtual ~Piece();
		std::vector<std::pair<int, int>> returnMoves() const;
		const QString text;
		bool getHasMoved() const;
	protected:
		void removePossMoves(int i);
	private :
		std::pair<int, int> pos_ = {0,0};
		std::vector<std::pair<int, int>> movesPattern_;
		bool movesStraight_ = 0;
		const bool isBlack_;
		bool hasMoved_ = false;
	};
}