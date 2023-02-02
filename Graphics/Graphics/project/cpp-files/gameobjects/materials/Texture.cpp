#include "../../../header-files/gameobjects/materials/Texture.h"
#include "../../../header-files/Game.h"

int CTexture::Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext)
{
	p_dxdevice = _p_dxdevice;
	p_dxcontext = _p_dxcontext;


	HRESULT hr = CreateWICTextureFromFile(p_dxdevice, fileName, &p_texture, &p_shaderResourceView);
	if (FAILED(hr))
	{
		MessageBox(nullptr, fileName, L"Failed to load texture", MB_OK);
		return -100;
	}

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		// Lineare Interpolation
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = p_dxdevice->CreateSamplerState(&samplerDesc, &p_textureSampler);
	if (FAILED(hr))
	{
		MessageBox(nullptr, fileName, L"Failed to create sampler state", MB_OK);
		return -101;
	}

    return 0;
}

int CTexture::Update()
{
	p_dxcontext->PSSetSamplers(0, 1, &p_textureSampler);
	p_dxcontext->PSSetShaderResources(0, 1, &p_shaderResourceView);

    return 0;
}

int CTexture::DeInit()
{
    return 0;
}
