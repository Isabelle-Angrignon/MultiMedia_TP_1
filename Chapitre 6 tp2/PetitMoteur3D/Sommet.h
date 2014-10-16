//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Entête classe Sommet
//

#pragma once

using namespace DirectX;

class CSommet
{
private:
	static int _nbrSommets;
	XMFLOAT3 _pos;
	XMFLOAT3 _normale;


public:

	static D3D11_INPUT_ELEMENT_DESC layout[];
	static UINT numElements;
	static int getNbrSommets();
	XMFLOAT3 getPos();
	XMFLOAT3 getNormal();
	void setPos(XMFLOAT3 pos);
	void setNormal(XMFLOAT3 normal);
	void setPosZ(float z);

	CSommet();
   CSommet(XMFLOAT3 _position, XMFLOAT3 _normal, XMFLOAT2 _coordTex = XMFLOAT2(0, 0));/////////////
	~CSommet();
protected:
   XMFLOAT2 coordTex;////////////////
};

