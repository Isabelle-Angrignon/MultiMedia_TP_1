//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Entête classe Terrain
//


#pragma once
#include "Sommet.h"
#include <string>
#include <fstream >

using namespace std;


class CTerrain
{
private:
	const float ECHELLE = 1.0f;
	
	int _nbrPolygone;
	
public:
	
	static const int DIMMENSIONX = 257;
	static const int DIMMENSIONY = 257;
	CSommet  *_tabSommet;
	int * _tabIndex;
	void setNbrPolygone(int nbrPolygone);
	int getNbrPolygone();

	CTerrain(string nomfichier);
	CTerrain();
	~CTerrain();
	void definitionHauteur(); // convertisseur qui fait sa ? 

	XMFLOAT3 CalculNormale(int x, int y);

	XMVECTOR ObtenirPosition(int x, int y);

};

