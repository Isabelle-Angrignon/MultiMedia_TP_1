//Isabelle Angrignon, Mathieu Dumoulin et Simon Bouchard
//16 septembre 2014
//Définitions classe Terrain
//


#include "StdAfx.h"

#include "Terrain.h"
#include "util.h"
#include "resource.h"
#include "MoteurWindows.h"

using namespace UtilitairesDX;


CTerrain::CTerrain(string nomfichier, CDispositifD3D11* pDispositif_)
{
	pDispositif = pDispositif_;  // Prendre en note le dispositif
	
	_tabSommet = new CSommet[DIMMENSIONX * DIMMENSIONY];
	_tabIndex = new int[(DIMMENSIONX - 1) * (DIMMENSIONY - 1) * 6];

	//mettre dans fichier .custom
	ifstream f;
	f.open(nomfichier, ios::in | ios_base::binary);

	f.read((char*)_tabSommet, DIMMENSIONX * DIMMENSIONY * sizeof(CSommet));
	f.read((char*)_tabIndex, (DIMMENSIONX - 1) * (DIMMENSIONY - 1) * 6 * sizeof(int));
	
	f.close();

	// Création du vertex buffer et copie des sommets
	ID3D11Device* pD3DDevice = pDispositif->GetD3DDevice();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	
	bd.ByteWidth = sizeof(CSommet) * CSommet::getNbrSommets();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _tabSommet;
	pVertexBuffer = NULL;

	DXEssayer(pD3DDevice->CreateBuffer(&bd, &InitData, &pVertexBuffer), DXE_CREATIONVERTEXBUFFER);

	// Création de l'index buffer et copie des indices
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * (DIMMENSIONX - 1) * (DIMMENSIONY - 1) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _tabIndex;
	pIndexBuffer = NULL;

	DXEssayer(pD3DDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer), DXE_CREATIONINDEXBUFFER);

	
	// Initialisation de l'effet
	InitEffet();
		
	matWorld = XMMatrixIdentity();
		
	

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


void CTerrain::Draw()
{
	// Obtenir le contexte
	ID3D11DeviceContext* pImmediateContext = pDispositif->GetImmediateContext();

	// Choisir la topologie des primitives
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Source des sommets
	UINT stride = sizeof(CSommet);
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	// Source des index
	pImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// input layout des sommets
	pImmediateContext->IASetInputLayout(pVertexLayout);

	// Initialiser et sélectionner les «constantes» de l'effet
	ShadersParams sp;
	XMMATRIX viewProj = CMoteurWindows::GetInstance().GetMatViewProj();

	sp.matWorldViewProj = XMMatrixTranspose(matWorld * viewProj);
	sp.matWorld = XMMatrixTranspose(matWorld);

	sp.vLumiere = XMVectorSet(0.0f, 0.0f, 150.0f, 1.0f);
	sp.vCamera = CMoteurWindows::GetInstance().camera.GetPosition();

	// Couleur
	sp.vAEcl = XMVectorSet(0.2f, 0.2f, 0.2f, 1.0f);
	sp.vAMat = sp.vDMat = XMVectorSet(0.6f, 0.45f, 0.4f, 1.0f);

	sp.vDEcl = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	

	pImmediateContext->UpdateSubresource(pConstantBuffer, 0, NULL, &sp, 0, 0);

	ID3DX11EffectConstantBuffer* pCB = pEffet->GetConstantBufferByName("param");  // Nous n'avons qu'un seul CBuffer
	pCB->SetConstantBuffer(pConstantBuffer);

   // Activation de la texture   /////////////////////////////////////////////////////
   ID3DX11EffectShaderResourceVariable* variableTexture;
   variableTexture = pEffet->GetVariableByName("textureEntree")->AsShaderResource();
   variableTexture->SetResource(pTextureD3D);

   // Le sampler state
   ID3DX11EffectSamplerVariable* variableSampler;
   variableSampler = pEffet->GetVariableByName("SampleState")->AsSampler();
   variableSampler->SetSampler(0, pSampleState);   /////////////////////////////////////

	// **** Rendu de l'objet	  
	pPasse->Apply(0, pImmediateContext);

	pImmediateContext->DrawIndexed(256*256*6, 0, 0);
}

void CTerrain::SetTexture(CTexture* pTexture)  ////////////////////////////////
{
   pTextureD3D = pTexture->GetD3DTexture();
}

void CTerrain::InitEffet()
{
	// Compilation et chargement du vertex shader
	ID3D11Device* pD3DDevice = pDispositif->GetD3DDevice();

	// Création d'un tampon pour les constantes du VS
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ShadersParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	pD3DDevice->CreateBuffer(&bd, NULL, &pConstantBuffer);

	// Pour l'effet
	ID3DBlob* pFXBlob = NULL;

	DXEssayer(D3DCompileFromFile(L"MiniPhong.fx", 0, 0, 0,
		"fx_5_0", 0, 0,
		&pFXBlob, NULL),
		DXE_ERREURCREATION_FX);

	D3DX11CreateEffectFromMemory(pFXBlob->GetBufferPointer(), pFXBlob->GetBufferSize(), 0, pD3DDevice, &pEffet);

	pFXBlob->Release();

	pTechnique = pEffet->GetTechniqueByIndex(0);
	pPasse = pTechnique->GetPassByIndex(0);

	// Créer l'organisation des sommets pour le VS de notre effet
	D3DX11_PASS_SHADER_DESC effectVSDesc;
	pPasse->GetVertexShaderDesc(&effectVSDesc);

	D3DX11_EFFECT_SHADER_DESC effectVSDesc2;
	effectVSDesc.pShaderVariable->GetShaderDesc(effectVSDesc.ShaderIndex, &effectVSDesc2);

	const void *vsCodePtr = effectVSDesc2.pBytecode;
	unsigned vsCodeLen = effectVSDesc2.BytecodeLength;

	pVertexLayout = NULL;
	DXEssayer(pD3DDevice->CreateInputLayout(CSommet::layout,
		CSommet::numElements,
		vsCodePtr,
		vsCodeLen,
		&pVertexLayout),
		DXE_CREATIONLAYOUT);

   // Initialisation des paramètres de sampling de la texture           /////////////////////////////////
   D3D11_SAMPLER_DESC samplerDesc;

   samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
   samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
   samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
   samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
   samplerDesc.MipLODBias = 0.0f;
   samplerDesc.MaxAnisotropy = 4;
   samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
   samplerDesc.BorderColor[0] = 0;
   samplerDesc.BorderColor[1] = 0;
   samplerDesc.BorderColor[2] = 0;
   samplerDesc.BorderColor[3] = 0;
   samplerDesc.MinLOD = 0;
   samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

   // Création de l'état de sampling
   pD3DDevice->CreateSamplerState(&samplerDesc, &pSampleState);      ///////////////////////////////////

}
