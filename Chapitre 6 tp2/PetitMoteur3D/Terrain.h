//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Ent�te classe Terrain
//


#pragma once
#include "Sommet.h"
#include "Texture.h"
#include <string>
#include <fstream>

#include "d3dx11effect.h"
#include "Objet3D.h"
#include "DispositifD3D11.h"

using namespace std;
using namespace PM3D;

class CTerrain : public CObjet3D
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

	CTerrain(string nomfichier, CDispositifD3D11* pDispositif_);
	CTerrain();
	~CTerrain();
	void definitionHauteur(); // convertisseur qui fait sa ? 

	XMFLOAT3 CalculNormale(int x, int y);

	XMVECTOR ObtenirPosition(int x, int y);

	void Draw();

   void SetTexture(CTexture* pTexture);///////////////
	

protected:

	struct ShadersParams
	{
		XMMATRIX matWorldViewProj;	// la matrice totale 
		XMMATRIX matWorld;			// matrice de transformation dans le monde 
		XMVECTOR vLumiere; 			// la position de la source d'�clairage (Point)
		XMVECTOR vCamera; 			// la position de la cam�ra
		XMVECTOR vAEcl; 			// la valeur ambiante de l'�clairage
		XMVECTOR vAMat; 			// la valeur ambiante du mat�riau
		XMVECTOR vDEcl; 			// la valeur diffuse de l'�clairage 
		XMVECTOR vDMat; 			// la valeur diffuse du mat�riau 
	};

	void InitEffet();

	CDispositifD3D11* pDispositif;

	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;

	// D�finitions des valeurs d'animation
	ID3D11Buffer* pConstantBuffer;
	XMMATRIX matWorld;
	float rotation;

	// Pour les effets
	ID3DX11Effect* pEffet;
	ID3DX11EffectTechnique* pTechnique;
	ID3DX11EffectPass* pPasse;
	ID3D11InputLayout* pVertexLayout;
   ID3D11ShaderResourceView* pTextureD3D;
   ID3D11SamplerState* pSampleState;

};

