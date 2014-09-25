//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions fonctions utilitaires
//

#include "Convertisseur.h"



//Lit un fichier raw et met les données dans un tableau de char qu'il retourne
char* LireFichierHeightmap(string fichier)
{
	char* tabByte = new char[/*257 * 257*/CTerrain::DIMMENSIONX * CTerrain::DIMMENSIONY];
	ifstream f;
	f.open(fichier, ios::in|ios_base::binary);
	f.read((char*)tabByte,257*257);
	f.close();

	return tabByte;
}

//Prend un tableau de char et la ref d'un objet terrain:
//Prend la valeur z de chaque élément du tableau de char et le met à sa place dans le sommet 
//approprié du terrain et calcule la normale
//on supprime le tableau de char car on n'en a plus besoin.
void ConstruireHauteursTerrain(char* tabByte, CTerrain &leTerrain)
{
	int M = 257;
	float z;	
	for (int y = 0; y < M; ++y)
	{		
		for (int x = 0; x < M; ++x)
		{			
			z = (unsigned char)tabByte[y*M + x];			
			leTerrain._tabSommet[y*M + x].setPosZ(z);
		}			
	}

	for (int y = 0; y < M; ++y)
	{
		for (int x = 0; x < M; ++x)
		{
			leTerrain._tabSommet[y*M+x].setNormal( leTerrain.CalculNormale(x, y)) ;
		}
	}


	delete tabByte;
}


//enregirstre l'objet dans un fichier 
void EnregistrerTout(CTerrain &leTerrain)
{
	string fichier = "converti.terrain";
	//mettre dans fichier .custom
	ofstream f;
	f.open(fichier, ios::out | ios_base::binary);

	f.write((char*)leTerrain._tabSommet, CSommet::getNbrSommets()*sizeof(CSommet));
	f.write((char*)leTerrain._tabIndex, (CTerrain::DIMMENSIONX-1) * (CTerrain::DIMMENSIONY-1) * 6 * sizeof(int));
	 
	f.close();
}

void LireTout()
{
	CSommet test[500];

	string fichier = "converti.terrain";
	//mettre dans fichier .custom
	ifstream f;
	f.open(fichier, ios::in | ios_base::binary);

	f.read((char*)test, 500*sizeof(CSommet));
	
	f.close();
}