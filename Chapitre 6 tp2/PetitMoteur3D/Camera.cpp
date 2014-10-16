#include "stdafx.h"

#include "Camera.h"
#include "MoteurWindows.h"


CCamera::CCamera()
{

}

CCamera::CCamera(const XMVECTOR& position_in,
	const XMVECTOR& direction_in,
	const XMVECTOR& up_in,
	XMMATRIX* pMatView_in,
	XMMATRIX* pMatProj_in,
	XMMATRIX* pMatViewProj_in)
{
	Init(position_in, direction_in, up_in, pMatView_in, pMatProj_in, pMatViewProj_in);
}

CCamera::~CCamera()
{
}

void CCamera::Init(const XMVECTOR& position_in,
	const XMVECTOR& direction_in,
	const XMVECTOR& up_in,
	XMMATRIX* pMatView_in,
	XMMATRIX* pMatProj_in,
	XMMATRIX* pMatViewProj_in)
{
	pMatView = pMatView_in;
	pMatProj = pMatProj_in;
	pMatViewProj = pMatViewProj_in;
	SetPosition(position_in);
	SetDirection(direction_in);
	SetUp(up_in);
	directionOriginale = direction;
	orientationCamera = 0;   // 0,1,0   sinon  atan(y/x);
}


void CCamera::Update()
{
	// Matrice de la vision
	*pMatView = XMMatrixLookToRH(position,
		direction,
		up);

	// Recalculer matViewProj
	*pMatViewProj = (*pMatView) * (*pMatProj);
}

void CCamera::Bouger(float tempsEcoule)
{
	// Pour les mouvements, nous utilisons le gestionnaire de saisie
	CMoteurWindows& rMoteur = CMoteurWindows::GetInstance();
	CDIManipulateur& rGestionnaireDeSaisie = rMoteur.GetGestionnaireDeSaisie();


	// Vérifier l'état de la touche gauche
	if (rGestionnaireDeSaisie.ToucheAppuyee(DIK_LEFT))
	{
		// orientationCamera += qq chose;
		// direction = directionOriginale * matricerotationZ( orientationCamera)
		orientationCamera += ( 2.0f * XM_PI / 10.0f ) * tempsEcoule;

		direction = XMVector4Transform(directionOriginale , XMMatrixRotationZ(orientationCamera));

	}

	// Vérifier l'état de la touche droite
	if (rGestionnaireDeSaisie.ToucheAppuyee(DIK_RIGHT))
	{
		orientationCamera -= (2.0f * XM_PI / 10.0f) * tempsEcoule;

		direction = XMVector4Transform(directionOriginale, XMMatrixRotationZ(orientationCamera));

	}

	// Vérifier l'état de la touche gauche
	if (rGestionnaireDeSaisie.ToucheAppuyee(DIK_UP))
	{
		position = position + direction * 5.0f /*vitesse*/ * tempsEcoule;

	}
	// Vérifier l'état de la touche droite
	if (rGestionnaireDeSaisie.ToucheAppuyee(DIK_DOWN))
	{
		position = position - direction * 5.0f /*vitesse*/ * tempsEcoule;

	}

	Update();



}