#pragma once
#include <utility>
#include "Piece.h"

/**
* Ent�te pour le module d'un case sur l'�ch�quier. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/

namespace gameObjects {
	class Tile {
	public:
		Tile(int xpos, int ypos);
		Tile(const Tile& other);
		void movePiece(gameObjects::Piece* movePiece);
		void removePiece();
		gameObjects::Piece* piece();
		bool isRoi();
		
		//text modifier
		void addValid();
		void removeValid();

		//getValid
		bool isValidMove() const;

		QString operator*() const;
	private:
		const int xpos_;
		const int ypos_;
		QString currentText_; // a changer quand on change les images
		QString currentTextValid_; //a changer quand on change les images
		gameObjects::Piece* currPiece_;
		bool valid_ = false;
	};
}