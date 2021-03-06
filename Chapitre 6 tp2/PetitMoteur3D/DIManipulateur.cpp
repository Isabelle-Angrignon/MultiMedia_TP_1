
#include "stdafx.h"
#include <dinput.h>
#include "DIManipulateur.h"
#include "util.h"
#include "resource.h"
using namespace UtilitairesDX;

bool CDIManipulateur::bDejaInit = false;
CDIManipulateur::CDIManipulateur()
{
	pDirectInput = NULL;
	pClavier = NULL;
	pSouris = NULL;
	pJoystick = NULL;
}


CDIManipulateur::~CDIManipulateur()
{
	if (pClavier)
	{
		pClavier->Unacquire();
		pClavier->Release();
		pClavier = NULL;
	}
	if (pSouris)
	{
		pSouris->Unacquire();
		pSouris->Release();
		pSouris = NULL;
	}
	if (pJoystick)
	{
		pJoystick->Unacquire();
		pJoystick->Release();
		pJoystick = NULL;
	}
	if (pDirectInput)
	{
		pDirectInput->Release();
		pClavier = NULL;
	}
}


bool CDIManipulateur::Init(HINSTANCE hInstance, HWND hWnd)
{
	// Un seul objet DirectInput est permis
	if (!bDejaInit)
	{
		// Objet DirectInput
		DXEssayer(DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&pDirectInput,
			NULL), ERREUR_CREATION_DIRECTINPUT);
		// Objet Clavier
		DXEssayer(pDirectInput->CreateDevice(GUID_SysKeyboard,
			&pClavier,
			NULL),
			ERREUR_CREATION_CLAVIER);
		DXEssayer(pClavier->SetDataFormat(&c_dfDIKeyboard),
			ERREUR_CREATION_FORMATCLAVIER);
		pClavier->SetCooperativeLevel(hWnd,
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		pClavier->Acquire();
		// Objet Souris
		// Objet Joystick
		bDejaInit = true;
	}
	return true;
}

void CDIManipulateur::StatutClavier()
{
	pClavier->GetDeviceState(sizeof(tamponClavier), (void*)& tamponClavier);
}

bool CDIManipulateur::ToucheAppuyee(UINT touche)
{
	return (tamponClavier[touche] & 0x80);
}