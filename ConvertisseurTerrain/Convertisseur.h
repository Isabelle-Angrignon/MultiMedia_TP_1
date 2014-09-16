//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Entête fonctions utilitaires
//

#pragma once

#include <string>
#include <fstream >
#include "Terrain.h"
using namespace std;


char* LireFichierHeightmap(string fichier);

void ConstruireHauteursTerrain(char* tabByte, CTerrain &leTerrain);

void CalculerNormales(CTerrain &leTerrain);
    
void EnregistrerTout(CTerrain &leTerrain);