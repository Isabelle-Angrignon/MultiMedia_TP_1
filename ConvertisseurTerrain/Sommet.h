//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Entête classe Sommet
//

#pragma once
#include <DirectXMath.h>
using namespace DirectX;
class CSommet
{
private:
	static int _nbrSommets;
	XMFLOAT3 _pos;
	XMFLOAT3 _normale;
public:

	static int getNbrSommets();
	XMFLOAT3 getPos();
	XMFLOAT3 getNormal();
	void setPos(XMFLOAT3 pos);
	void setNormal(XMFLOAT3 normal);
	void setPosZ(float z);

	CSommet();
	~CSommet();
};

