#include "pianoCavernaIsola.h"
#include "noise\noise.h"
#include <cstdlib>
#include <ctime>

pianoCavernaIsola::pianoCavernaIsola(int lunghezza, int larghezza)
{
	this->larghezza = larghezza;
	this->lunghezza = lunghezza;
	noise::module::Perlin perlin;
	std::srand(time(nullptr));
	double random = (double)(rand() % 50) / 2;
	pavimento.reserve(lunghezza*larghezza);
	for (int i = 0; i < lunghezza; i++) {
		for (int k = 0; k < larghezza; k++) {
			double nx = random * 2 + 4 * (double)i / (double)lunghezza, ny = random * 3 + 4 * (double)k / (double)larghezza; //Valori casuali del piano
			double value = perlin.GetValue(nx, ny, random); //Perlin
			double dx = (double)abs(i - larghezza / 2) / (larghezza / 2); //Posizione relativa dal centro
			double dy = (double)abs(k - lunghezza / 2) / (lunghezza / 2); //Idem
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
}


pianoCavernaIsola::~pianoCavernaIsola()
{
}