#pragma once

// System Includes
#include <Windows.h>

// DirectX
#include <d3d11.h>
#include <D3DX11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

// STL includes
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <istream>

// Mathe
#include <algorithm>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

#include <WICTextureLoader.h>

using namespace DirectX;

template<typename T>
inline void SafeRelease(T& _ptr)
{
	if (_ptr != nullptr)
	{
		_ptr->Release();
		_ptr = nullptr;
	}
}