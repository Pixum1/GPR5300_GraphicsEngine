#pragma once
#include "../../misc/GraphicsPCH.h"
#include "../../gameobjects/materials/Texture.h"

class CCubemap : public CTexture
{
public:
	CCubemap(LPCWSTR _fileName, ETextureType _type) : CTexture(_fileName, _type)
	{
		fileName = _fileName;
	};

	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext) override;
	virtual int Update() override;
	virtual int DeInit() override;

protected:
	ETextureType m_textureType;

	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	ID3D11Texture2D* p_texture = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11SamplerState* p_textureSampler = nullptr;

	LPCWSTR fileName;
};

