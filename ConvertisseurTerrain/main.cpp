//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Convertisseur de terrain
//Prend un fichier heightmap.raw et le converti en fichier binaire (extension de notre choix)
//qui permet ultérieurement de calculer les sommets, normales et index...

#include "Convertisseur.h"

using namespace std;




int main() {

	//Déclarer un objet Terrain
	CTerrain leTerrain;
	char* tabByte;
	string fichier = "NotreTerrain.raw";

	tabByte = LireFichierHeightmap(fichier);

	ConstruireHauteursTerrain(tabByte, leTerrain);

	EnregistrerTout(leTerrain); 

	LireTout();
	
	return 0;
}