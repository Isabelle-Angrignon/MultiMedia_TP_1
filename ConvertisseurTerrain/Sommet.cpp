//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions classe Sommet
//

#include "Sommet.h"

int CSommet::_nbrSommets = 0;
CSommet::CSommet()
{
	++_nbrSommets;
	coordTex.x = _pos.x;
	coordTex.y = _pos.y;
}

XMFLOAT3 CSommet::getNormal()
{
	return _normale;
}

XMFLOAT3 CSommet::getPos()
{
	return _pos;
}

int CSommet::getNbrSommets()
{
	return _nbrSommets;
}

void CSommet::setNormal(XMFLOAT3 normale)
{
	_normale = normale;
}

void CSommet::setPos(XMFLOAT3 pos)
{
	_pos = pos;
}

void CSommet::setPosZ(float z)
{
	_pos.z = z;
}


CSommet::~CSommet()
{
	--_nbrSommets;
}

void CSommet::setTextCoord(float x, float y)
{
	coordTex.x = x;
	coordTex.y = y;
}