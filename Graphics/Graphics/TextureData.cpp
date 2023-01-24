#include "GraphicsPCH.h"
#include "TextureData.h"

STextureData::STextureData()
{
}

STextureData::STextureData(ID3D11Resource* _p_texture, ID3D11ShaderResourceView* _p_shaderResourceView, ID3D11SamplerState* _p_textureSampler)
{
	m_texture = _p_texture;
	m_shaderResourceView = _p_shaderResourceView;
	m_textureSampler = _p_textureSampler;
}
