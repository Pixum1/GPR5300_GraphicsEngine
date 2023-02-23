#pragma once

struct SWindowSettings
{
	const long m_WindowWidth = 1280;
	const long m_WindowHeight = 720;

	LPCWSTR m_WindowClassName = L"DirectX Graphics Enginge";
	LPCSTR m_WindowClassNameShort = "DirectX Graphics Enginge";
	LPCSTR m_WindowName = "DirectX Graphics Enginge, Tobias Knauf";
	HWND m_WindowHandle = nullptr;

	const bool m_enableVSync = false;
};