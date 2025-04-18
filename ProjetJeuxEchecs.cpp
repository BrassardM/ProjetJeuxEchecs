#include "ProjetJeuxEchecs.h"
#include "Roi.h"
#include "Chevalier.h"
#include "Fou.h"
#include <QMessageBox>
#include "TempMove.h"

gameInterface::ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjetJeuxEchecsClass())
{
    Board* pboard = new Board;
    board = pboard;
    ui->setupUi(this);
    ui->turn->setText((QString)"Tour des blancs");
    for (int y{}; y < 8; y++) {
        for (int x{}; x < 8; x++){
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
    connect(ui->adddel, &QPushButton::clicked, this, [&] { addDelete(); });
    connect(ui->reinit, &QPushButton::clicked, this, [&] { reinit(); });


    std::vector<std::pair<int, QString>> thingsToDraw = board->updateBoard();
    drawBoard(thingsToDraw);
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
            drawBoard(board->updateBoard());
            isTempMoving = true;
        }
        else {
            std::vector<std::pair<int, QString>> thingsToDraw = board->updateBoard(x, y);
            drawBoard(thingsToDraw);
        }
        ui->turn->setText(board->displayTurn());
        ui->check->setText(board->checkCheck());
    }
    else {
        ui->testmove->setChecked(false);
        drawBoard(board->addPiece(x,y,pieceSelection)); //also removes piece
        pieceSelection = nullptr;
        ui->currentselection->setText("Effacer");
    }
}

gameInterface::ProjetJeuxEchecs::~ProjetJeuxEchecs()
{
    delete board;
    delete pieceSelection;
    delete ui;
}

void gameInterface::ProjetJeuxEchecs::drawBoard(std::vector<std::pair<int, QString>> thingsToDraw) const
{
    for (auto&& n : thingsToDraw) {
        pushButtonCoords[n.first%8][(n.first - n.first % 8 )/ 8]->setText(n.second);
    }
}

void gameInterface::ProjetJeuxEchecs::tempmove(std::pair<int,int> originalPos, std::pair<int,int> movePos) const
{
    TempMove tm(originalPos,movePos,board);
    drawBoard(board->updateBoard());
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
    drawBoard(board->updateBoard());
    ui->turn->setText("Tour des blancs");
    ui->check->setText(board->checkCheck());
}

void gameInterface::ProjetJeuxEchecs::goBackToMain()
{
    isTempMoving = false;
    drawBoard(board->updateBoard());
    ui->check->setText(board->checkCheck());

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
        }
    }
    catch (errors::tooManyKings& e){
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
    }
}

void gameInterface::ProjetJeuxEchecs::addDelete()
{
    if (ui->creativeMode->isChecked()) {
        pieceSelection = nullptr;
        QString text = (QString)"Effacer";
        ui->currentselection->setText(text);
    }
}

void gameInterface::ProjetJeuxEchecs::reinit()
{
    drawBoard(board->updateBoard());
}
