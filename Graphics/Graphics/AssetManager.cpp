#include "GraphicsPCH.h"
#include "AssetManager.h"
#include "Game.h"

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
}

STextureData* CAssetManager::LoadTexture(LPCWSTR _fileName, D3D11_TEXTURE_ADDRESS_MODE _sampleMode, D3D11_FILTER _filter)
{
	if (_fileName == nullptr)
	{
		return nullptr;
	}

	// Falls der Eintrag nicht gefunden ist, erzeugen wir die Textur
	if (m_textures.find(_fileName) == m_textures.end())
	{
		ID3D11Resource* t;
		ID3D11ShaderResourceView* srv;
		ID3D11SamplerState* ts;

		HRESULT hr = CreateWICTextureFromFile(DXS.m_device, _fileName, &t, &srv);
		if (FAILED(hr))
		{
			MessageBox(nullptr, _fileName, L"Failed to load texture", MB_OK);
		}

		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
		desc.AddressU = _sampleMode;
		desc.AddressV = _sampleMode;
		desc.Filter = _filter; // Lineare Interpolation
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;

		DXS.m_device->CreateSamplerState(&desc, &ts);
		m_textures[_fileName] = new STextureData(t, srv, ts);
	}

	return m_textures[_fileName];
}
