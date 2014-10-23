//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions classe Terrain
//

#include "Terrain.h"


CTerrain::CTerrain(string nomfichier)
{
	_tabSommet = new CSommet[DIMMENSIONX * DIMMENSIONY];
	_tabIndex = new int[(DIMMENSIONX - 1) * (DIMMENSIONY - 1) * 6];

	//mettre dans fichier .custom
	ifstream f;
	f.open(nomfichier, ios::in | ios_base::binary);

	f.read((char*)_tabSommet, DIMMENSIONX * DIMMENSIONY * sizeof(CSommet));
	f.read((char*)_tabIndex, (DIMMENSIONX - 1) * (DIMMENSIONY - 1) * 6 * sizeof(int));

	//pour test
	//int tab[100];
	//for (int i = 0; i < 100; i++)tab[i] = _tabIndex[i];
	
	f.close();
}


CTerrain::CTerrain()
{
	_tabSommet = new CSommet[DIMMENSIONX * DIMMENSIONY];
	_tabIndex = new int[(DIMMENSIONX-1) * (DIMMENSIONY-1) * 6];
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
			_tabSommet[y*DIMMENSIONY + x].setTextCoord(x, y);
			// Initialisation de l'index
			if (x < DIMMENSIONX - 1 && y < DIMMENSIONY - 1)
			{
				_tabIndex[k++] = y*DIMMENSIONX + x;
				_tabIndex[k++] = (y + 1) * DIMMENSIONX + (x + 1);
				_tabIndex[k++] = y*DIMMENSIONX + (x + 1);
				_tabIndex[k++] = y*DIMMENSIONX + x;
				_tabIndex[k++] = (y + 1)* DIMMENSIONX + x;
				_tabIndex[k++] = (y + 1)* DIMMENSIONX + (x + 1);
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
	delete[] _tabIndex;
}
// XMLODA

XMVECTOR CTerrain::ObtenirPosition(int x, int y)
{
	return XMLoadFloat3(&(_tabSommet[y*DIMMENSIONY + x].getPos()));
}


XMFLOAT3 CTerrain::CalculNormale(int x, int y)
{
	XMVECTOR n1;
	XMVECTOR n2;
	XMVECTOR n3;
	XMVECTOR n4;
	XMVECTOR v1;
	XMVECTOR v2;
	XMVECTOR v3;
	XMVECTOR v4;
	n1 = n2 = n3 = n4 = XMVectorSet(0, 0, 1, 0); // Le Z est le haut
	// v1 = p1 – p0, etc...
	if (y < DIMMENSIONY -1) v1 = ObtenirPosition(x, y + 1) - ObtenirPosition(x, y);
	if (x < DIMMENSIONX -1) v2 = ObtenirPosition(x + 1, y) - ObtenirPosition(x, y);
	if (y > 0) v3 = ObtenirPosition(x, y - 1) - ObtenirPosition(x, y);
	if (x > 0) v4 = ObtenirPosition(x - 1, y) - ObtenirPosition(x, y);
	// les produits vectoriels
	if (y < DIMMENSIONY-1  && x < DIMMENSIONX-1) n1 = XMVector3Cross(v2, v1);
	if (y > 0 && x < DIMMENSIONX-1) n2 = XMVector3Cross(v3, v2);
	if (y > 0 && x > 0) n3            = XMVector3Cross(v4, v3);
	if (y < DIMMENSIONY-1 && x > 0) n4 = XMVector3Cross(v1, v4);
	n1 = n1 + n2 + n3 + n4;
	n1 = XMVector3Normalize(n1);
	XMFLOAT3 resultat;
	XMStoreFloat3(&resultat, n1);
	return resultat;
}
