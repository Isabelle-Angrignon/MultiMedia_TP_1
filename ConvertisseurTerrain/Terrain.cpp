//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions classe Terrain
//

#include "Terrain.h"


CTerrain::CTerrain()
{
	_tabSommet = new CSommet[DIMMENSIONX * DIMMENSIONY];
	_tabIndex = new int[DIMMENSIONX * DIMMENSIONY * 6];
	XMFLOAT3 t;
	XMFLOAT3 n;
	t.z = 0.0f;
	n.x = 0;
	n.y = 0;
	n.z = 1;
	int k = 0;
	for (int y = 0; y < DIMMENSIONY; ++y)
	{
		t.y = y * ECHELLE;
		for (int x = 0; x < DIMMENSIONX; ++x)
		{
			t.x = x * ECHELLE;
			_tabSommet[y*DIMMENSIONY + x].setPos(t);
			_tabSommet[y*DIMMENSIONY + x].setNormal(n);
			// Initialisation de l'index
			if (x < DIMMENSIONX - 1 && y < DIMMENSIONY - 1)
			{
				_tabIndex[k++] = y*DIMMENSIONX + 1;
				_tabIndex[k++] = (y + 1)*DIMMENSIONX + x;
				_tabIndex[k++] = (y + 1)*DIMMENSIONX + x + 1;
				_tabIndex[k++] = y*DIMMENSIONX + x;
				_tabIndex[k++] = (y + 1)*DIMMENSIONX + x + 1;
				_tabIndex[k++] = y*DIMMENSIONX + x + 1;
			}
		}
	}
}

void CTerrain::setNbrPolygone(int nbrPolygone)
{
	_nbrPolygone = nbrPolygone;
}

int CTerrain::getNbrPolygone()
{
	return _nbrPolygone;
}

CTerrain::~CTerrain()
{
	delete[] _tabSommet;
}
