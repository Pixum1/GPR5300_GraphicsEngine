#pragma once
#include "GraphicsPCH.h"

class CTexture
{
public:
	CTexture(LPCWSTR _fileName)
	{
		fileName = _fileName;
	};

	int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext);
	int Update();
	int DeInit();

protected:
	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	ID3D11Resource* p_texture = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11SamplerState* p_textureSampler = nullptr;

	LPCWSTR fileName;
};

