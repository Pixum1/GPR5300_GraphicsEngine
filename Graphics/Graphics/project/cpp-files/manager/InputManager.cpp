#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/manager/InputManager.h"
#include "../../header-files/Game.h"

int InputManager::InitDirectInput(HINSTANCE _hInstance)
{
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&directInput, nullptr);
	FAILHR(-100);

	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr);
	FAILHR(-101);

	hr = directInput->CreateDevice(GUID_SysMouse, &mouse, nullptr);
	FAILHR(-102);

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	FAILHR(-103);

	hr = keyboard->SetCooperativeLevel(WDS.WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	FAILHR(-104);

	hr = mouse->SetDataFormat(&c_dfDIMouse);
	FAILHR(-105);

	hr = mouse->SetCooperativeLevel(WDS.WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	FAILHR(-106);

	mousePos = XMFLOAT2(WDS.WindowWidth * 0.5f, WDS.WindowHeight * 0.5f);
	ZeroMemory(currentKeyboardState, sizeof(currentKeyboardState));
	ZeroMemory(&currentMouseSate, sizeof(currentMouseSate));

	ZeroMemory(lastKeyboardState, sizeof(lastKeyboardState));
	ZeroMemory(&lastMouseSate, sizeof(lastMouseSate));

	return 0;
}

void InputManager::DetectInput()
{
	// Werte von letzten Frame sichern
	lastMouseSate = currentMouseSate;
	memcpy(lastKeyboardState, currentKeyboardState, sizeof(currentKeyboardState));

	// Holen der Daten aus der Hardware
	keyboard->Acquire();
	mouse->Acquire();

	keyboard->GetDeviceState(sizeof(currentKeyboardState), currentKeyboardState);
	mouse->GetDeviceState(sizeof(currentMouseSate), &currentMouseSate);

	mousePos = XMFLOAT2(mousePos.x + GetMouseMovement().x, mousePos.y + GetMouseMovement().y);

}

void InputManager::DeInit()
{
	SafeRelease(mouse);
	SafeRelease(keyboard);
}

bool InputManager::GetKey(int _keyID)
{
	return currentKeyboardState[_keyID] & 0x80;
}

bool InputManager::GetKeyUp(int _keyID)
{
	return !(currentKeyboardState[_keyID] & 0x80) &&
		(lastKeyboardState[_keyID] & 0x80);

}

bool InputManager::GetKeyDown(int _keyID)
{
	return (currentKeyboardState[_keyID] & 0x80) &&
		!(lastKeyboardState[_keyID] & 0x80);
}

bool InputManager::GetMouseKey(int _keyID)
{
	return currentMouseSate.rgbButtons[_keyID] & 0x80;
}

bool InputManager::GetMouseKeyUp(int _keyID)
{
	return !(currentMouseSate.rgbButtons[_keyID] & 0x80) &&
		(lastMouseSate.rgbButtons[_keyID] & 0x80);
}

bool InputManager::GetMouseKeyDown(int _keyID)
{
	return (currentMouseSate.rgbButtons[_keyID] & 0x80) &&
		!(lastMouseSate.rgbButtons[_keyID] & 0x80);
}
