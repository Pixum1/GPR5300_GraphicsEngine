#pragma once
#include "GraphicsPCH.h"
#include "Game.h"

class STextureData;
class CTexture;
class CCubemap;

class CMaterial
{
public:
	CMaterial(LPCWSTR _pixelShaderName, LPCWSTR _vertexShaderName) 
	{
		pixelShaderName = _pixelShaderName;
		vertexShaderName = _vertexShaderName;
	}

	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext);
	virtual int Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext, LPCWSTR _fileName, bool _isCubemap = false);
	virtual void Render();
	virtual bool DeInit();

protected:
	virtual int CreateVertexShader();
	virtual int CreateInputLayout(ID3DBlob* _p_vertexBlob);
	virtual int CreatePixelShader();

	// Variables
protected:
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

