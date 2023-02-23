#pragma once
#include "GraphicsPCH.h"

struct StandardConstantBuffer
{
	XMMATRIX Matrix;
};

struct LightConstantBuffer
{
	XMFLOAT4 AmbientColor;

	XMFLOAT4 DiffuseColor;
	XMFLOAT4 SpecularColor;
	
	XMFLOAT3 LightDir;
	float LightDirPadding;

	XMFLOAT3 CameraPos;
	float CameraPosPadding;
};