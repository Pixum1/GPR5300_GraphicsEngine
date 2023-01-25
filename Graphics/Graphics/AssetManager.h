#pragma once
#include "TextureData.h"
#include <map>

class CAssetManager
{
public:
	CAssetManager();
	~CAssetManager();

	STextureData* LoadTexture(LPCWSTR _fileName, D3D11_TEXTURE_ADDRESS_MODE _sampleMode, D3D11_FILTER _filter);

private:
	std::map<LPCWSTR, STextureData*> m_textures;
};

