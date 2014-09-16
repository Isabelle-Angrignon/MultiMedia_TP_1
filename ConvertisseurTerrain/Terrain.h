//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Entête classe Terrain
//


#pragma once
#include "Sommet.h"
class CTerrain
{
private:
	const float ECHELLE = 1.0f;
	
	int * _tabIndex;
	int _nbrPolygone;
	
public:
	static const int DIMMENSIONX = 257;
	static const int DIMMENSIONY = 257;
	CSommet  _tabSommet;////////////////////////////////////////////enlevé étoile
	void setNbrPolygone(int nbrPolygone);
	int getNbrPolygone();
	CTerrain();
	~CTerrain();
	void definitionHauteur(); // convertisseur qui fait sa ? 

};

