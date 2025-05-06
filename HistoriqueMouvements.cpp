#include "HistoriqueMouvements.h"
#include <tuple>

/**
* Module pour l'historique des mouvement de la partie. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


HistoriqueMouvements::HistoriqueMouvements()
{
	
}

HistoriqueMouvements::HistoriqueMouvements(HistoriqueMouvements& other): 
sequence_(other.sequence_)
{
}

void HistoriqueMouvements::operator+=(std::tuple<int, int, int, int> sequence)
{
	sequence_.push_back(sequence);
}

QString HistoriqueMouvements::operator*()
{
	QString out;
	out = "gameObjects::Board b;\nb.playSequence(std::vector<std::tuple<int,int,int,int>>{";
	int i{};
	for (auto&& n : sequence_) {
		out += (QString)"\n{" + QString::number(get<0>(n)) + (QString)", " + QString::number(get<1>(n)) + ", " + QString::number(get<2>(n)) + ", " + QString::number(get<3>(n)) + "}";
		if (i < ((int)sequence_.size() - 1)) {
			out += ", ";
		}
		i++;
	}
	out += "});";
	return out;
}
