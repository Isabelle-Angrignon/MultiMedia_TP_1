//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Entête fonctions utilitaires
//

#pragma once

#include <string>
#include <fstream >
#include "Terrain.h"
using namespace std;

const float ECHELLE_Z = 0.04f;

char* LireFichierHeightmap(string fichier);

void ConstruireHauteursTerrain(char* tabByte, CTerrain &leTerrain);
    
void EnregistrerTout(CTerrain &leTerrain);

void LireTout();
void LireTout(string fichier);