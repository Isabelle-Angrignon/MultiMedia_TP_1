

#pragma once

#include <vector>

using namespace DirectX;

class CCamera
{
public:

	void Init(const XMVECTOR& position_in,
		const XMVECTOR& direction_in,
		const XMVECTOR& up_in,
		XMMATRIX* pMatView_in,
		XMMATRIX* pMatProj_in,
		XMMATRIX* pMatViewProj_in);

	CCamera();

	CCamera(const XMVECTOR& position_in,
		const XMVECTOR& direction_in,
		const XMVECTOR& up_in,
		XMMATRIX* pMatView_in,
		XMMATRIX* pMatProj_in,
		XMMATRIX* pMatViewProj_in);
	~CCamera();

	void SetPosition(const XMVECTOR& position_in){ position = position_in; };
	XMVECTOR GetPosition(){ return position; };
	void SetDirection(const XMVECTOR& direction_in){ direction = direction_in; }
	void SetUp(const XMVECTOR& up_in){ up = up_in; }

	void Update();

	void Bouger(float tempsEcoule);

protected:
	// Les matrices
	XMMATRIX *pMatView;
	XMMATRIX *pMatProj;
	XMMATRIX *pMatViewProj;

	float orientationCamera;
	XMVECTOR directionOriginale;

	XMVECTOR position;
	XMVECTOR direction;
	XMVECTOR up;

	
};

