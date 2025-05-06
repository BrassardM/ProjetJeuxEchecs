#include "ProjetJeuxEchecs.h"
#include "Roi.h"
#include "Chevalier.h"
#include "Fou.h"
#include "Pion.h"
#include "Tour.h"
#include "Reine.h"
#include <QMessageBox>
#include "MouvementTemporaire.h"

/**
* Module de l'interaction modèle-vue. Fait partie de la vue.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

using namespace gameObjects;

gameInterface::ProjetJeuxEchecs::ProjetJeuxEchecs(bool debugMode, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjetJeuxEchecsClass())
{
    Echequier* pboard = new Echequier;
    board = pboard;
    ui->setupUi(this);
    ui->turn->setText((QString)"Tour des blancs");
    for (int y{}; y < DIMENSION_ECHEQUIER; y++) {
        for (int x{}; x < DIMENSION_ECHEQUIER; x++){
            QPushButton* currbutton = findChild<QPushButton*>((QString)((char)(72-x)) + (QString)'_' + (QString)QString::number(y+1));
            pushButtonCoords[x][y] = currbutton;
            if (currbutton)
                connect(currbutton, &QPushButton::clicked, this, [&, x, y] { onClick(x, y); });
        }
    }
    connect(ui->gobacktodefault, &QPushButton::clicked, this, [&] { resetBoard(true); });
    connect(ui->emptyreset, &QPushButton::clicked, this, [&] { resetBoard(false); });
    connect(ui->testmove, &QPushButton::clicked, this, [&] { goBackToMain(); });
    connect(ui->addRoi, &QPushButton::clicked, this, [&] { addRoi(); });
    connect(ui->addFou, &QPushButton::clicked, this, [&] { addFou(); });
    connect(ui->addChev, &QPushButton::clicked, this, [&] { addChev(); });
    connect(ui->addReine, &QPushButton::clicked, this, [&] { addReine(); });
    connect(ui->addTour, &QPushButton::clicked, this, [&] { addTour(); });
    connect(ui->addPion, &QPushButton::clicked, this, [&] { addPion(); });
    connect(ui->adddel, &QPushButton::clicked, this, [&] { addDelete(); });
    connect(ui->reinit, &QPushButton::clicked, this, [&] { reinit(); });

    if (debugMode) {
        ui->debugReturnSeq->setEnabled(true);
        ui->debugReturnSeqVal->setEnabled(true);
        connect(ui->debugReturnSeq, &QPushButton::clicked, this, [&] { returnSeq(); });
    }
    else {
        ui->debugReturnSeq->hide();
        ui->debugReturnSeqVal->hide();
    }

    drawBoard();
}
void gameInterface::ProjetJeuxEchecs::onClick(int x, int y) {
    if (!(ui->creativeMode->isChecked())) {
        if (ui->testmove->isChecked() && isTempMoving) {
            tempmove(tempMovingPos, std::pair<int, int>(x, y));
            ui->testmove->setChecked(false);
            isTempMoving = false;
        }
        else if (ui->testmove->isChecked() && !isTempMoving) {
            tempMovingPos = std::pair<int,int>(x, y);
            drawBoard();
            isTempMoving = true;
        }
        else {
            board->updateBoard(x, y);
            drawBoard();
        }
    }
    else {
        if (((dynamic_cast<Pion*>(pieceSelection) == NULL) || (x != 0 && x != 7))&&((dynamic_cast<Roi*>(pieceSelection) == NULL)||(x == 0 || x == 7))) {
            ui->testmove->setChecked(false);
            board->addPiece(x, y, pieceSelection);
            drawBoard();
            pieceSelection = nullptr;
            ui->currentselection->setText("Effacer");
        }
    }
}

gameInterface::ProjetJeuxEchecs::~ProjetJeuxEchecs()
{
    delete board;
    delete pieceSelection;
    delete ui;
}

void gameInterface::ProjetJeuxEchecs::drawBoard() const
{
    for (auto&& n : board->operator*()) {
        pushButtonCoords[n.first % DIMENSION_ECHEQUIER][(n.first - n.first % DIMENSION_ECHEQUIER) / DIMENSION_ECHEQUIER]->setText(n.second);
    }
    QString turn;
    QString check = (QString)"Pas d'échec";
    if (board->getBlackTurn()) {
        turn = (QString)"Tour des noirs";
        if (board->checkCheck(board->getBlackTurn())) {
            if (board->getState()) {
                check = (QString)"Blanc Gagne";
            }
            else {
                check = (QString)"Noir en échec";
            }
        }
        else {
            if (board->getState()) {
                check = (QString)"Impasse";
            }
        }
    }
    else {
        turn = (QString)"Tour des blancs";
        if (board->checkCheck(board->getBlackTurn())) {
            if (board->getState()) {
                check = (QString)"Noir Gagne";
            }
            else {
                check = (QString)"Blanc en échec";
            }
        }
        else {
            if (board->getState()) {
                check = (QString)"Impasse";
            }
        }
    }
    ui->turn->setText(turn);
    ui->check->setText(check);
}

void gameInterface::ProjetJeuxEchecs::tempmove(std::pair<int,int> originalPos, std::pair<int,int> movePos) const
{
    MouvementTemporaire tm(originalPos,movePos,board);
    drawBoard();
}

void gameInterface::ProjetJeuxEchecs::cancelPieceSelection()
{
    if (pieceSelection != nullptr) {
        delete pieceSelection;
        ui->currentselection->setText((QString)"Effacer");
        pieceSelection = nullptr;
    }
}

void gameInterface::ProjetJeuxEchecs::resetBoard(bool defaultreset)
{
    board->resetAttributes(defaultreset);
    drawBoard();
}

void gameInterface::ProjetJeuxEchecs::goBackToMain()
{
    isTempMoving = false;
    drawBoard();
}

void gameInterface::ProjetJeuxEchecs::addRoi()
{
    cancelPieceSelection();
    try {
        if (ui->creativeMode->isChecked()) {
            gameObjects::Roi* roiajout = new gameObjects::Roi(ui->black->isChecked());
            pieceSelection = roiajout;
            QString text = (QString)"Roi";
            if (ui->black->isChecked()) {
                text = text + (QString)" Black";
            }
            ui->currentselection->setText(text);
            board->logBoardState(true);
        }
    }
    catch (errors::TropDeRois& e){
        QMessageBox messagebox;
        messagebox.critical(0, "Trop de Rois", e.what());
    }
}

void gameInterface::ProjetJeuxEchecs::addFou()
{
    if (ui->creativeMode->isChecked()) {
        gameObjects::Fou* fouajout = new gameObjects::Fou(ui->black->isChecked());
        pieceSelection = fouajout;
        QString text = (QString)"Fou";
        if (ui->black->isChecked()) {
            text = text + (QString)" Noir";
        }
        ui->currentselection->setText(text);
        board->logBoardState(true);
    }
    else {
        if (ui->black->isChecked()) {
            board->changePromotionPiece(1, ui->black->isChecked());
            ui->blackProm->setText("Fou");
        }
        else {
            board->changePromotionPiece(1, ui->black->isChecked());
            ui->whiteProm->setText("Fou");
        }
    }
}

void gameInterface::ProjetJeuxEchecs::addChev()
{
    if (ui->creativeMode->isChecked()) {
        gameObjects::Chevalier* Chevajout = new gameObjects::Chevalier(ui->black->isChecked());
        pieceSelection = Chevajout;
        QString text = (QString)"Chevalier";
        if (ui->black->isChecked()) {
            text = text + (QString)" Noir";
        }
        ui->currentselection->setText(text);
        board->logBoardState(true);
    }
    else {
        if (ui->black->isChecked()) {
            board->changePromotionPiece(3, ui->black->isChecked());
            ui->blackProm->setText("Chevalier");
        }
        else {
            board->changePromotionPiece(3, ui->black->isChecked());
            ui->whiteProm->setText("Chevalier");
        }
    }
}

void gameInterface::ProjetJeuxEchecs::addReine()
{
    if (ui->creativeMode->isChecked()) {
        gameObjects::Reine* Reinajout = new gameObjects::Reine(ui->black->isChecked());
        pieceSelection = Reinajout;
        QString text = (QString)"Reine";
        if (ui->black->isChecked()) {
            text = text + (QString)" Noir";
        }
        ui->currentselection->setText(text);
        board->logBoardState(true);
    }
    else {
        if (ui->black->isChecked()) {
            board->changePromotionPiece(0, ui->black->isChecked());
            ui->blackProm->setText("Reine");
        }
        else {
            board->changePromotionPiece(0, ui->black->isChecked());
            ui->whiteProm->setText("Reine");
        }
    }
}

void gameInterface::ProjetJeuxEchecs::addTour()
{
    if (ui->creativeMode->isChecked()) {
        gameObjects::Tour* Tourajout = new gameObjects::Tour(ui->black->isChecked());
        pieceSelection = Tourajout;
        QString text = (QString)"Tour";
        if (ui->black->isChecked()) {
            text = text + (QString)" Noir";
        }
        ui->currentselection->setText(text);
        board->logBoardState(true);
    }
    else {
        if (ui->black->isChecked()) {
            board->changePromotionPiece(2, ui->black->isChecked());
            ui->blackProm->setText("Tour");
        }
        else {
            board->changePromotionPiece(2, ui->black->isChecked());
            ui->whiteProm->setText("Tour");
        }
    }
}

void gameInterface::ProjetJeuxEchecs::addPion()
{
    if (ui->creativeMode->isChecked()) {
        gameObjects::Pion* Pionajout = new gameObjects::Pion(ui->black->isChecked());
        pieceSelection = Pionajout;
        QString text = (QString)"Pion";
        if (ui->black->isChecked()) {
            text = text + (QString)" Noir";
        }
        ui->currentselection->setText(text);
        board->logBoardState(true);
    }
}

void gameInterface::ProjetJeuxEchecs::addDelete()
{
    if (ui->creativeMode->isChecked()) {
        pieceSelection = nullptr;
        QString text = (QString)"Effacer";
        ui->currentselection->setText(text);
        board->logBoardState(true);
    }
}

void gameInterface::ProjetJeuxEchecs::reinit()
{
    drawBoard();
}

void gameInterface::ProjetJeuxEchecs::returnSeq()
{
    ui->debugReturnSeqVal->setPlainText(*(board->returnSequence()));
}
