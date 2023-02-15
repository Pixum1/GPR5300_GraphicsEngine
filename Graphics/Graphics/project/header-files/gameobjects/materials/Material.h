#pragma once
#include "../../misc/GraphicsPCH.h"
#include "../../Game.h"

class STextureData;
class CTexture;
class CCubemap;

class CMaterial
{
public:
	CMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext, LPCWSTR _pixelShaderName, LPCWSTR _vertexShaderName, LPCWSTR _fileName, bool _isCubemap)
	{
		p_dxdevice = _p_dxdevice;
		p_dxcontext = _p_dxcontext;

		pixelShaderName = _pixelShaderName;
		vertexShaderName = _vertexShaderName;

		fileName = _fileName;
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
protected:
	LPCWSTR fileName = L"..\\assets\\DefaultTexture.png";
	bool isCubemap;

	ID3D11Buffer* p_constantBuffer;

	CTexture* p_texture = nullptr;
	CCubemap* p_cubemap = nullptr;

	ID3D11InputLayout* p_inputLayout = nullptr;
	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;

	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;

	LPCWSTR pixelShaderName;
	LPCWSTR vertexShaderName;
};

