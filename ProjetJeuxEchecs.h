#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjetJeuxEchecs.h"
#include "Board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProjetJeuxEchecsClass; };
QT_END_NAMESPACE

namespace gameInterface {
    class ProjetJeuxEchecs : public QMainWindow
    {
        Q_OBJECT

    public:
        ProjetJeuxEchecs(QWidget* parent = nullptr);
        ~ProjetJeuxEchecs();

    private:    
        void cancelPieceSelection();
        QPushButton* pushButtonCoords[8][8];
        Ui::ProjetJeuxEchecsClass* ui;
        Board board;
        bool creativemode = false;
        gameObjects::Piece* pieceSelection = nullptr;
        void drawBoard(std::vector<std::pair<int, QString>> thingsToDraw) const;
        void tempmove(int x, int y) const;
    
    private slots:
        void onClick(int x, int y);
        void resetBoard(bool defaultreset);
        void goBackToMain();
        void addRoi();
        void addFou();
        void addChev();
        void addDelete();
    };
}