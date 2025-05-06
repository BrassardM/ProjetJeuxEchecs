#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjetJeuxEchecs.h"
#include "Echequier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProjetJeuxEchecsClass; };
QT_END_NAMESPACE

/**
* Entête pour le module de l'interaction entre l'interface graphique et le modèle. Fait partie de la vue.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

namespace gameInterface {
    class ProjetJeuxEchecs : public QMainWindow
    {
        Q_OBJECT

    public:
        ProjetJeuxEchecs(bool debugMode = false, QWidget* parent = nullptr);
        ~ProjetJeuxEchecs();

    private:    
        void cancelPieceSelection();
        QPushButton* pushButtonCoords[8][8];
        Ui::ProjetJeuxEchecsClass* ui;
        gameObjects::Echequier* board;
        bool creativemode = false;
        gameObjects::Piece* pieceSelection = nullptr;
        void drawBoard() const;
        void tempmove(std::pair<int, int> originalPos, std::pair<int, int> movePos) const;
        bool isTempMoving = false;
        std::pair<int, int> tempMovingPos = { 0,0 };
    
    private slots:
        void onClick(int x, int y);
        void resetBoard(bool defaultreset);
        void goBackToMain();
        void addRoi();
        void addFou();
        void addChev();
        void addReine();
        void addTour();
        void addPion();
        void addDelete();
        void reinit();
        
        //pourlestests
        void returnSeq();
    };
}