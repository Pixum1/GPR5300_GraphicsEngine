#include "../../../header-files/gameobjects/materials/Material.h"
#include "../../../header-files/gameobjects/materials/Texture.h"
#include "../../../header-files/gameobjects/materials/Cubemap.h"

int CMaterial::Init()
{
	if (p_albedo != nullptr)
		p_albedo->Init(p_dxdevice, p_dxcontext);

	if (p_normal != nullptr)
		p_normal->Init(p_dxdevice, p_dxcontext);

	CreateVertexShader();
	CreatePixelShader();

	return 0;
}

void CMaterial::Render()
{
#pragma region Update Light Constant Buffer
	SLightConstantBuffer lightBuffer = {};

	lightBuffer.AmbientColor = GetGame->m_ambientLight;
	lightBuffer.DiffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1);
	lightBuffer.SpecularColor = XMFLOAT4(1.0f, 1.0f, 1.0f, smoothness);
	lightBuffer.CameraPos = GetGame->m_camPos;
	lightBuffer.LightDir = GetGame->m_lightDirection;

	p_dxcontext->UpdateSubresource(DXS.m_constantBuffers[CB_LIGHT], 0, nullptr, &lightBuffer, 0, 0);
#pragma endregion

	// Vertex Shader
	p_dxcontext->VSSetShader(p_vertexShader, nullptr, 0);
	// Pixel Shader
	p_dxcontext->PSSetShader(p_pixelShader, nullptr, 0);

	p_dxcontext->IASetInputLayout(p_inputLayout);

	if (p_albedo != nullptr)
		p_albedo->Update();

	if (p_normal != nullptr)
		p_normal->Update();
}
bool CMaterial::DeInit()
{
	return false;
}


int CMaterial::CreateInputLayout(ID3DBlob* _p_vertexBlob)
{
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{
			"POSITION",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32B32_FLOAT,	// Float3
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexData, Position),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		},
		{
			"NORMAL",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32B32_FLOAT,	// Float3
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexData, Normal),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		},
		{
			"COLOR",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32B32A32_FLOAT,	// Float4
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexData, Color),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		},
		{
			"TEXCOORD",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32_FLOAT,		// Float2
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexData, UV),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		}
	};

	HRESULT hr = p_dxdevice->CreateInputLayout(vertexLayoutDesc,
		_countof(vertexLayoutDesc),
		_p_vertexBlob->GetBufferPointer(),
		_p_vertexBlob->GetBufferSize(),
		&p_inputLayout);
	FAILHR(-52);

	return 0;
}

int CMaterial::CreateVertexShader()
{
	ID3DBlob* shaderBlob;

	HRESULT hr = D3DReadFileToBlob(vertexShaderName, &shaderBlob);
	FAILHR(-50);

	hr = p_dxdevice->CreateVertexShader(shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(), nullptr, &p_vertexShader);
	FAILHR(-51);

	CreateInputLayout(shaderBlob);

	return 0;
}
int CMaterial::CreatePixelShader()
{
	ID3DBlob* shaderBlob;

	HRESULT hr = D3DReadFileToBlob(pixelShaderName, &shaderBlob);
	FAILHR(-53);

	hr = p_dxdevice->CreatePixelShader(shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&p_pixelShader);

	FAILHR(-54);

	return 0;
}
