#pragma once

struct WindowSettings
{
	const long WindowWidth = 1280;
	const long WindowHeight = 720;

	LPCWSTR WindowClassName = L"DirectX Graphics Enginge";
	LPCSTR WindowClassNameShort = "DirectX Graphics Enginge";
	LPCSTR WindowName = "DirectX Graphics Enginge, Tobias Knauf";
	HWND WindowHandle = nullptr;

	const bool EnableVSync = false;
};