#include "pianoCavernaIsola.h"
#include "noise\noise.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
pianoCavernaIsola::pianoCavernaIsola(int larghezza, int lunghezza)
{
	this->larghezza = larghezza;
	this->lunghezza = lunghezza;
	noise::module::Perlin perlin;
	std::srand((unsigned int)time(nullptr));
	double random = (double)(rand() % 50) / 2;
	pavimento.reserve(lunghezza*larghezza);
	for (int i = 0; i < lunghezza; i++) {
		for (int k = 0; k < larghezza; k++) {
			double nx = random * 2 + 4 * (double)i / (double)lunghezza, ny = random * 3 + 4 * (double)k / (double)larghezza; //Valori casuali del piano
			double value = perlin.GetValue(nx, ny, random); //Perlin
			double dx = (double)abs(i - lunghezza / 2) / (lunghezza / 2); //Posizione relativa dal centro
			double dy = (double)abs(k - larghezza / 2) / (larghezza / 2); //Idem
			double d = sqrt(pow(dx, 2) + pow(dy, 2)) / sqrt(2); //Distanza relativa dal centro
			double valueAfter = value + 0.8 - 10 * pow(d, 7); //Trasfroma la poltiglia di caselle in qualcosa che sembra un isola
			if (valueAfter > 0.4) {
				pavimento.push_back(Casella(true));
			}
			else {
				pavimento.push_back(Casella(false));
			}
		}
		
	}
	cood placeProtagonista(0,0);
	int counter=0;
	std::shared_ptr<Entita> prot = entityFactory();
	std::vector<cood> caselleOk;
do {
		
		placeProtagonista.first = rand() % larghezza;
		placeProtagonista.second = rand() % lunghezza;
		caselleOk = floodFill(placeProtagonista);
		counter++;
	} while ((caselleOk.empty()) ^ counter == 1000); //OPTIMIZE
	if (counter == 1000)
		std::cout << "D'oh" << std::endl;
	else
		placeEntita(prot, placeProtagonista);
	spargiLoot(caselleOk);
	caselleOk.erase(std::remove(caselleOk.begin(), caselleOk.end(), getPositionOfPlayer()), caselleOk.end());
	placeEntita(entityFactory(1),caselleOk[rand()%caselleOk.size()]);
	auto smh = caselleOk[rand() % caselleOk.size()];
	pavimento.at(posizione(smh)).setEvento(1);
}


pianoCavernaIsola::~pianoCavernaIsola()
{
	
}

bool pianoCavernaIsola::spargiLoot(std::vector<cood> posizioniValide) {
	for (int i = (lunghezza + larghezza) / 4; i >= 0; i--) {
		auto oggettoInserito = objectFactory(rand()%5);
		pavimento.at(posizione(posizioniValide[rand() % posizioniValide.size()])).addOggetto(oggettoInserito);
	}
	return true;
}
