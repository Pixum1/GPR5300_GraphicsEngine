#pragma once

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class CInputManager
{
public:
	/// <summary>
	/// Initializes direct input for mouse and keyboard
	/// </summary>
	/// <param name="_hInstance"></param>
	/// <returns></returns>
	int InitDirectInput(HINSTANCE _hInstance);
	/// <summary>
	/// Compares values from the last frame to detect an input
	/// </summary>
	void DetectInput();
	/// <summary>
	/// Deinitializes the input manager
	/// </summary>
	void DeInit();

	/// <summary>
	/// True while a key is pressed
	/// </summary>
	/// <param name="_keyID"></param>
	/// <returns></returns>
	bool GetKey(int _keyID);
	bool GetKeyUp(int _keyID);
	bool GetKeyDown(int _keyID);

	inline XMFLOAT2 GetMousePos() { return  m_mousePos; }
	XMFLOAT2 GetMouseMovement();
	float GetMouseWheel();

	bool GetMouseKey(int _keyID);
	bool GetMouseKeyUp(int _keyID);
	bool GetMouseKeyDown(int _keyID);

private:
	IDirectInputDevice8* m_mouse;
	IDirectInputDevice8* m_keyboard;

	LPDIRECTINPUT8 m_directInput;

	DIMOUSESTATE m_currentMouseSate;
	DIMOUSESTATE m_lastMouseSate;

	BYTE m_currentKeyboardState[256];
	BYTE m_lastKeyboardState[256];

	XMFLOAT2 m_mousePos;
};

