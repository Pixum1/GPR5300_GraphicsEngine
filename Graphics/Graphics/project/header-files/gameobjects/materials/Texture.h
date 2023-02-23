#pragma once
#include "../../misc/GraphicsPCH.h"

/// <summary>
/// Definition for the texturetype, integer value determines samplerstate and texture in the shader
/// </summary>
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
	/// <summary>
	/// Creates the texture from the filename, shader resource view and sampler state
	/// </summary>
	/// <param name="_p_dxdevice"></param>
	/// <param name="_p_dxcontext"></param>
	/// <returns></returns>
	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext);
	/// <summary>
	/// Updates sampler state and shader resource view
	/// </summary>
	virtual int Update();
	/// <summary>
	/// Deinitializes the texture
	/// </summary>
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

