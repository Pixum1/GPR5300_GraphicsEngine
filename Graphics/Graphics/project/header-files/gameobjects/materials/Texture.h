#pragma once
#include "../../misc/GraphicsPCH.h"

class CTexture
{
public:
	CTexture(LPCWSTR _fileName, bool _isNormalMap)
	{
		fileName = _fileName;
		m_isNormalmap = _isNormalMap;
	};

	int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext);
	int Update();
	int DeInit();


public:
	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;

protected:
	bool m_isNormalmap;

	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	ID3D11Resource* p_texture = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11SamplerState* p_textureSampler = nullptr;

	LPCWSTR fileName;
};

