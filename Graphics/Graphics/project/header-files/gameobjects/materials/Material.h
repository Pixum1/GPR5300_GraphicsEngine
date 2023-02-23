#pragma once
#include "../../misc/GraphicsPCH.h"
#include "../../Game.h"

class STextureData;
class CTexture;
class CCubemap;

class CMaterial
{
public:
	CMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext, LPCWSTR _pixelShaderName, LPCWSTR _vertexShaderName, CTexture* _p_albedoTex, CTexture* _p_normalTex)
	{
		p_dxdevice = _p_dxdevice;
		p_dxcontext = _p_dxcontext;

		pixelShaderName = _pixelShaderName;
		vertexShaderName = _vertexShaderName;

		p_albedo = _p_albedoTex;
		p_normal = _p_normalTex;

		Init();
	}
	/// <summary>
	/// Inititalizes the Materials and creates pixel and vertex shader
	/// </summary>
	/// <returns></returns>
	virtual int Init();
	/// <summary>
	/// Updates the light constant buffer, sets vertex and pixel shader and updates the different materials
	/// </summary>
	virtual void Render();
	/// <summary>
	/// Deinitializes the material
	/// </summary>
	/// <returns></returns>
	virtual bool DeInit();

protected:
	/// <summary>
	/// Creates the vertex shader
	/// </summary>
	/// <returns></returns>
	virtual int CreateVertexShader();
	/// <summary>
	/// Creates the input layout that is important for sending data to the vertex shader
	/// </summary>
	/// <param name="_p_vertexBlob"></param>
	/// <returns></returns>
	virtual int CreateInputLayout(ID3DBlob* _p_vertexBlob);
	/// <summary>
	/// Creates the pixel shader
	/// </summary>
	/// <returns></returns>
	virtual int CreatePixelShader();

	// Variables
public:
	float smoothness;

protected:
	CTexture* p_albedo = nullptr;
	CTexture* p_normal = nullptr;

	ID3D11InputLayout* p_inputLayout = nullptr;
	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;

	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;

	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	LPCWSTR pixelShaderName;
	LPCWSTR vertexShaderName;
};

