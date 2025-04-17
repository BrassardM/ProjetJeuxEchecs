#pragma once
#include <utility>
#include <QPushButton>
#include "Piece.h"
#include <QObject>

namespace gameInterface {
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
		QString currentText; // a changer quand on change les images
		QString currentTextValid; //a changer quand on change les images
		gameObjects::Piece* currPiece;
		bool valid_ = false;
	};
}