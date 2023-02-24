#pragma once

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputManager
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
	/// <summary>
	/// True when a key is released
	/// </summary>
	/// <param name="_keyID"></param>
	/// <returns></returns>
	bool GetKeyUp(int _keyID);
	/// <summary>
	/// True when a key is pressed
	/// </summary>
	/// <param name="_keyID"></param>
	/// <returns></returns>
	bool GetKeyDown(int _keyID);

	inline XMFLOAT2 GetMousePosition() { return mousePos; }
	inline XMFLOAT2 GetMouseMovement() { return XMFLOAT2(currentMouseSate.lX, currentMouseSate.lY); }
	inline float GetMouseWheel() { return currentMouseSate.lZ; }

	/// <summary>
	/// True while a mousekey is pressed
	/// </summary>
	/// <param name="_keyID"></param>
	/// <returns></returns>
	bool GetMouseKey(int _keyID);
	/// <summary>
	/// True when a mousekey is released
	/// </summary>
	/// <param name="_keyID"></param>
	/// <returns></returns>
	bool GetMouseKeyUp(int _keyID);
	/// <summary>
	/// True when a mousekey is pressed
	/// </summary>
	/// <param name="_keyID"></param>
	/// <returns></returns>
	bool GetMouseKeyDown(int _keyID);

private:
	IDirectInputDevice8* mouse;
	IDirectInputDevice8* keyboard;

	LPDIRECTINPUT8 directInput;

	DIMOUSESTATE currentMouseSate;
	DIMOUSESTATE lastMouseSate;

	BYTE currentKeyboardState[256];
	BYTE lastKeyboardState[256];

	XMFLOAT2 mousePos;
};

