#pragma once


struct STextureData
{
	ID3D11Resource* m_texture;
	ID3D11ShaderResourceView* m_shaderResourceView;
	ID3D11SamplerState* m_textureSampler;

	STextureData();
	STextureData(ID3D11Resource* _p_texture, ID3D11ShaderResourceView* _p_shaderResourceView, ID3D11SamplerState* _p_textureSampler);
};

