#include "ProjetJeuxEchecs.h"
#include "Roi.h"
#include "Chevalier.h"
#include "Fou.h"
#include <QMessageBox>
#include "Tempboard.h"

gameInterface::ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjetJeuxEchecsClass())
{
    ui->setupUi(this);
    ui->turn->setText((QString)"White's Turn");
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


    std::vector<std::pair<int, QString>> thingsToDraw = board.updateBoard();
    drawBoard(thingsToDraw);
}
void gameInterface::ProjetJeuxEchecs::onClick(int x, int y) {
    if (!(ui->creativeMode->isChecked())) {
        if (ui->testmove->isChecked() && board.ismoving() == true) {
            drawBoard(board.updateBoard());
            tempmove(x,y);
        }
        else {
            std::vector<std::pair<int, QString>> thingsToDraw = board.updateBoard(x, y);
            drawBoard(thingsToDraw);
        }
        ui->turn->setText(board.displayTurn());
        ui->check->setText(board.checkCheck());
    }
    else {
        ui->testmove->setChecked(false);
        drawBoard(board.addPiece(x,y,pieceSelection)); //also removes piece
        pieceSelection = nullptr;
        ui->currentselection->setText("Current Selection");
    }
}

gameInterface::ProjetJeuxEchecs::~ProjetJeuxEchecs()
{
    delete pieceSelection;
    delete ui;
}

void gameInterface::ProjetJeuxEchecs::drawBoard(std::vector<std::pair<int, QString>> thingsToDraw) const
{
    for (auto&& n : thingsToDraw) {
        pushButtonCoords[n.first%8][(n.first - n.first % 8 )/ 8]->setText(n.second);
    }
}

void gameInterface::ProjetJeuxEchecs::tempmove(int x, int y) const
{
    TempBoard tempboard(board);
    std::vector<std::pair<int, QString>> thingsToDraw = (*tempboard)->updateBoard(x, y);
    drawBoard(thingsToDraw);
}

void gameInterface::ProjetJeuxEchecs::cancelPieceSelection()
{
    if (pieceSelection != nullptr) {
        delete pieceSelection;
        ui->currentselection->setText((QString)"Current Selection");
        pieceSelection = nullptr;
    }
}

void gameInterface::ProjetJeuxEchecs::resetBoard(bool defaultreset)
{
    board.resetAttributes(defaultreset);
    drawBoard(board.updateBoard());
    ui->check->setText(board.checkCheck());
}

void gameInterface::ProjetJeuxEchecs::goBackToMain()
{
    drawBoard(board.updateBoard());
    ui->check->setText(board.checkCheck());

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
    catch (tooManyKings& e){
        QMessageBox messagebox;
        messagebox.critical(0, "Cannot add more than 2 kings!", e.what());
    }
}

void gameInterface::ProjetJeuxEchecs::addFou()
{
    if (ui->creativeMode->isChecked()) {
        gameObjects::Fou* fouajout = new gameObjects::Fou(ui->black->isChecked());
        pieceSelection = fouajout;
        QString text = (QString)"Fou";
        if (ui->black->isChecked()) {
            text = text + (QString)" Black";
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
            text = text + (QString)" Black";
        }
        ui->currentselection->setText(text);
    }
}

void gameInterface::ProjetJeuxEchecs::addDelete()
{
    if (ui->creativeMode->isChecked()) {
        pieceSelection = nullptr;
        QString text = (QString)"Current Selection";
        ui->currentselection->setText(text);
    }
}
