#pragma once
#include "../../misc/GraphicsPCH.h"

/// <summary>
/// Definition for the texturetype, integer value determines samplerstate and texture in the shader
/// </summary>
enum ETextureType {
	Albedo = 0,
	Normalmap = 1,
};

class Texture
{
public:
	Texture(LPCWSTR _fileName, ETextureType _type)
	{
		fileName = _fileName;
		textureType = _type;
	};
	/// <summary>
	/// Assigns DirectX device and context
	/// </summary>
	/// <param name="_p_dxdevice"></param>
	/// <param name="_p_dxcontext"></param>
	/// <returns></returns>
	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext);
	/// <summary>
	/// Creates the texture from the filename, shader resource view and sampler state
	/// </summary>
	/// <returns></returns>
	virtual int Start();
	/// <summary>
	/// Updates sampler state and shader resource view
	/// </summary>
	virtual int Update();
	/// <summary>
	/// SafeReleases every directX component
	/// </summary>
	/// <returns></returns>
	virtual int DeInit();

protected:
	ETextureType textureType;

	ID3D11Device* p_dxdevice = nullptr;
	ID3D11DeviceContext* p_dxcontext = nullptr;

	ID3D11Resource* p_texture = nullptr;
	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;
	ID3D11SamplerState* p_textureSampler = nullptr;

	LPCWSTR fileName;
};

