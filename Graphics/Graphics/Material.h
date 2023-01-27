#pragma once
#include "GraphicsPCH.h"
#include "Game.h"

class STextureData;

class CMaterial
{
public:
	CMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext)
	{
		p_dxdevice = _p_dxdevice;
		p_dxcontext = _p_dxcontext;
	}
	CMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext, LPCWSTR _fileName, D3D11_TEXTURE_ADDRESS_MODE _sampleMode, D3D11_FILTER _filter)
	{
		p_dxdevice = _p_dxdevice;
		p_dxcontext = _p_dxcontext;

		AddTexture(_fileName, _sampleMode, _filter);
	}

	// Inherited via CComponent
	virtual int Init();
	virtual void Render();
	virtual bool DeInit();

public:
	STextureData* p_texture;
	ID3D11InputLayout* p_inputLayout = nullptr;
	ID3D11VertexShader* p_vertexShader = nullptr;
	ID3D11PixelShader* p_pixelShader = nullptr;

public:
	int AddTexture(LPCWSTR _fileName, D3D11_TEXTURE_ADDRESS_MODE _sampleMode, D3D11_FILTER _filter);

protected:
	virtual int CreateShader(D3D11_INPUT_ELEMENT_DESC _vertexShaderDesc[], UINT _numElements);

	// Variables
protected:
	bool m_usesTexture;
	ID3D11Device* p_dxdevice;
	ID3D11DeviceContext* p_dxcontext;
	STextureData* p_textureData;
	LPCWSTR pixelShaderName;
	LPCWSTR vertexShaderName;
};

