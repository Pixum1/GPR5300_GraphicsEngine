#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/manager/InputManager.h"
#include "../../header-files/Game.h"

CInputManager::CInputManager()
{
}

CInputManager::~CInputManager()
{
}

int CInputManager::InitDirectInput(HINSTANCE _hInstance)
{
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_directInput, nullptr);
	FAILHR(-100);

	hr = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
	FAILHR(-101);

	hr = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
	FAILHR(-102);

	hr = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	FAILHR(-103);

	hr = m_keyboard->SetCooperativeLevel(WDS.m_WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	FAILHR(-104);

	hr = m_mouse->SetDataFormat(&c_dfDIMouse);
	FAILHR(-105);

	hr = m_mouse->SetCooperativeLevel(WDS.m_WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	FAILHR(-106);

	m_mousePos = XMFLOAT2(WDS.m_WindowWidth * 0.5f, WDS.m_WindowHeight * 0.5f);
	ZeroMemory(m_currentKeyboardState, sizeof(m_currentKeyboardState));
	ZeroMemory(&m_currentMouseSate, sizeof(m_currentMouseSate));

	ZeroMemory(m_lastKeyboardState, sizeof(m_lastKeyboardState));
	ZeroMemory(&m_lastMouseSate, sizeof(m_lastMouseSate));

	return 0;
}

void CInputManager::DetectInput()
{
	// Werte von letzten Frame sichern
	m_lastMouseSate = m_currentMouseSate;
	memcpy(m_lastKeyboardState, m_currentKeyboardState, sizeof(m_currentKeyboardState));

	// Holen der Daten aus der Hardware
	m_keyboard->Acquire();
	m_mouse->Acquire();

	m_keyboard->GetDeviceState(sizeof(m_currentKeyboardState), m_currentKeyboardState);
	m_mouse->GetDeviceState(sizeof(m_currentMouseSate), &m_currentMouseSate);

	m_mousePos = XMFLOAT2(m_mousePos.x + GetMouseMovement().x, m_mousePos.y + GetMouseMovement().y);

}

void CInputManager::CleanUp()
{
}

bool CInputManager::GetKey(int _keyID)
{
	return m_currentKeyboardState[_keyID] & 0x80;
}

bool CInputManager::GetKeyUp(int _keyID)
{
	return !(m_currentKeyboardState[_keyID] & 0x80) &&
		(m_lastKeyboardState[_keyID] & 0x80);

}

bool CInputManager::GetKeyDown(int _keyID)
{
	return (m_currentKeyboardState[_keyID] & 0x80) &&
		!(m_lastKeyboardState[_keyID] & 0x80);
}

XMFLOAT2 CInputManager::GetMouseMovement()
{
	return XMFLOAT2(m_currentMouseSate.lX, m_currentMouseSate.lY);
}

float CInputManager::GetMouseWheel()
{
	return m_currentMouseSate.lZ;
}

bool CInputManager::GetMouseKey(int _keyID)
{
	return m_currentMouseSate.rgbButtons[_keyID] & 0x80;
}

bool CInputManager::GetMouseKeyUp(int _keyID)
{
	return !(m_currentMouseSate.rgbButtons[_keyID] & 0x80) &&
		(m_lastMouseSate.rgbButtons[_keyID] & 0x80);
}

bool CInputManager::GetMouseKeyDown(int _keyID)
{
	return (m_currentMouseSate.rgbButtons[_keyID] & 0x80) &&
		!(m_lastMouseSate.rgbButtons[_keyID] & 0x80);
}
