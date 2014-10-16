//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions classe Sommet
//

#include "stdafx.h"
#include "Sommet.h"
#include "Texture.h"


int CSommet::_nbrSommets = 0;

// Definir l'organisation de notre sommet
D3D11_INPUT_ELEMENT_DESC CSommet::layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
   { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }///////////////
};

UINT CSommet::numElements = ARRAYSIZE(CSommet::layout);

CSommet::CSommet()
{
	++_nbrSommets;
   coordTex.x = _pos.x;/////////////////////
   coordTex.y = _pos.y;
}

CSommet::CSommet(XMFLOAT3 _position, XMFLOAT3 _normal, XMFLOAT2 _coordTex)
{
   setPos(_position);
   setNormal(_normal);
   coordTex = _coordTex;
   coordTex.x = _pos.x;
   coordTex.y = _pos.y;/////////////////////
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
