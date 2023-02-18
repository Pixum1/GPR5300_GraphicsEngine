#pragma once
#include "../../misc/GraphicsPCH.h"
#include "../../Game.h"

class STextureData;
class CTexture;
class CCubemap;

class CMaterial
{
public:
	CMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext, LPCWSTR _pixelShaderName, LPCWSTR _vertexShaderName, LPCWSTR _albedoFileName, LPCWSTR _normalmapFileName, bool _isCubemap)
	{
		p_dxdevice = _p_dxdevice;
		p_dxcontext = _p_dxcontext;

		pixelShaderName = _pixelShaderName;
		vertexShaderName = _vertexShaderName;

		albedoFileName = _albedoFileName;
		normalMapFileName = _normalmapFileName;

		isCubemap = _isCubemap;

		Init();
	}

	virtual int Init();
	virtual void Render();
	virtual bool DeInit();

protected:
	virtual int CreateVertexShader();
	virtual int CreateInputLayout(ID3DBlob* _p_vertexBlob);
	virtual int CreatePixelShader();

	// Variables
public:
	float smoothness;

protected:
	LPCWSTR albedoFileName = L"..\\assets\\DefaultTexture.png";
	LPCWSTR normalMapFileName = nullptr;
	bool isCubemap;

	CTexture* p_albedo = nullptr;
	CTexture* p_normal = nullptr;
	CCubemap* p_cubemap = nullptr;

	ID3D11InputLayout* p_inputLayout = nullptr;

	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;

	ID3D11ShaderResourceView* p_shaderResourceView = nullptr;

	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	LPCWSTR pixelShaderName;
	LPCWSTR vertexShaderName;
};

