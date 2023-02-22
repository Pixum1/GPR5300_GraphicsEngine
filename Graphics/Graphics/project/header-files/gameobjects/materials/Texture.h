#pragma once
#include "../../misc/GraphicsPCH.h"

enum ETextureType {
	Albedo = 0,
	Normalmap = 1,
};

class CTexture
{
public:
	CTexture(LPCWSTR _fileName, ETextureType _type)
	{
		fileName = _fileName;
		m_textureType = _type;
	};

	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext);
	virtual int Update();
	virtual int DeInit();

protected:
	ETextureType m_textureType;

	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	ID3D11Resource* p_texture = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11SamplerState* p_textureSampler = nullptr;

	LPCWSTR fileName;
};

