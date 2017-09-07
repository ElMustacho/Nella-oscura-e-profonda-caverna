#pragma once
#include "pianoCavernaIsola.h"
class pianoCavernaIsolaGrafica :
	public pianoCavernaIsola
{
public:
	pianoCavernaIsolaGrafica(int larghezza, int lunghezza);
	void stampaPianoSuFinestra();
	~pianoCavernaIsolaGrafica();
};

