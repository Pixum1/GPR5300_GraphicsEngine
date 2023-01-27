#include "Material.h"


int CMaterial::Init()
{
	return 0;
}

void CMaterial::Render()
{
	unsigned int offset = 0;
	unsigned int stride = sizeof(SVertexPosColor);

	// Vertex Shader
	p_dxcontext->VSSetShader(p_vertexShader, nullptr, 0);

	// Pixel Shader
	p_dxcontext->PSSetShader(p_pixelShader, nullptr, 0);

	if (m_usesTexture)
	{
		p_dxcontext->PSSetSamplers(0, 1, &p_textureData->m_textureSampler);
		p_dxcontext->PSSetShaderResources(0, 1, &p_textureData->m_shaderResourceView);
	}
}
bool CMaterial::DeInit()
{
	return false;
}

int CMaterial::CreateShader(D3D11_INPUT_ELEMENT_DESC _vertexShaderDesc[], UINT _numElements)
{
	ID3DBlob* shaderBlob;

	HRESULT hr = D3DReadFileToBlob(vertexShaderName, &shaderBlob);
	FAILHR(-50);

	hr = p_dxdevice->CreateVertexShader(shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(), nullptr, &p_vertexShader);
	FAILHR(-51);

	hr = p_dxdevice->CreateInputLayout(_vertexShaderDesc,
		_numElements,
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&p_inputLayout);
	FAILHR(-52);

	hr = D3DReadFileToBlob(pixelShaderName, &shaderBlob);
	FAILHR(-53);

	hr = p_dxdevice->CreatePixelShader(shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&p_pixelShader);
	
	FAILHR(-54);

	return 0;
}

int CMaterial::AddTexture(LPCWSTR _fileName, D3D11_TEXTURE_ADDRESS_MODE _sampleMode, D3D11_FILTER _filter)
{
	p_textureData = ASM.LoadTexture(_fileName, _sampleMode, _filter);
	m_usesTexture = true;

	return 0;
}
