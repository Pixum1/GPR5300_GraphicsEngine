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

	/// <summary>
	/// Assign DirectX device and context
	/// </summary>
	/// <param name="_p_dxdevice"></param>
	/// <param name="_p_dxcontext"></param>
	/// <returns></returns>
	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext) override;
	/// <summary>
	/// Creates the texture from the filename, shader resource view and sampler state
	/// </summary>
	/// <returns></returns>
	virtual int Start() override;
	/// <summary>
	/// Updates sampler state and shader resource view
	/// </summary>
	/// <returns></returns>
	virtual int Update() override;
	/// <summary>
	/// SafeReleases every directX component
	/// </summary>
	/// <returns></returns>
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

