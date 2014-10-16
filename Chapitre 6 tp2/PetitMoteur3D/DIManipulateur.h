#pragma once
#include <dinput.h>
class CDIManipulateur
{
public:
	CDIManipulateur();
	~CDIManipulateur();
	bool Init(HINSTANCE hInstance, HWND hWnd);
	void StatutClavier();
	bool ToucheAppuyee(UINT touche);

protected:
	IDirectInput8* pDirectInput;
	IDirectInputDevice8* pClavier;
	IDirectInputDevice8* pSouris;
	IDirectInputDevice8* pJoystick;
	char tamponClavier[256];
	static bool bDejaInit;

};
