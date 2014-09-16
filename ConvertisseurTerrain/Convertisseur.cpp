//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions fonctions utilitaires
//

#include "Convertisseur.h"



//Lit un fichier raw et met les données dans un tableau de char qu'il retourne
char* LireFichierHeightmap(string fichier)
{
	char* tabByte = new char[257 * 257/*CTerrain.DIMMENSIONX * CTerrain.DIMMENSIONY*/];
	ifstream f;
	f.open(fichier, ios::in|ios_base::binary);
	f.read((char*)tabByte,257*257);
	return tabByte;
}

//Prend un tableau de char et la ref d'un objet terrain:
//Prend la valeur z de chaque élément du tableau de char et le met à sa place dans le sommet 
//approprié du terrain
//on supprime le tableau de char car on n'en a plus besoin.
void ConstruireHauteursTerrain(char* tabByte, CTerrain &leTerrain)
{
	int M = 257;
	float z;	
	for (int y = 0; y < M; ++y)
	{		
		for (int x = 0; x < M; ++x)
		{			
			z = tabByte[y*M + x];//récupérer le normale de la pos ????????????????????????????????????
			
			leTerrain._tabSommet[y*M + x].setPosZ(z);
		}			
	}
	
	delete tabByte;
}

void CalculerNormales(CTerrain &leTerrain)
{

}

//enregirstre l'objet dans un fichier 
void EnregistrerTout(CTerrain &leTerrain)
{
	//mettre dans fichier .custom
}