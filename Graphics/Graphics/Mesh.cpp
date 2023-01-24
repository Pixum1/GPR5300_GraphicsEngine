#include "GraphicsPCH.h"
#include "Game.h"
#include "Mesh.h"

bool CMesh::Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_devicecontext)
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(SVertexPosColor) * m_vertexCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ressourceData = { 0 };
	ressourceData.pSysMem = Vertices;

	HRESULT hr = DXS.m_device->CreateBuffer(&bufferDesc, &ressourceData, &m_vertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(WORD) * m_indexCount;

	ressourceData.pSysMem = Indices;

	hr = DXS.m_device->CreateBuffer(&bufferDesc, &ressourceData, &m_indexBuffer);
	if (FAILED(hr))
	{
		return false;
	}
}

bool CMesh::Start()
{
	return true;
}

void CMesh::Update()
{

}

bool CMesh::DeInit()
{
	return true;

}

void CMesh::Render()
{
	if (m_usesTexture)
	{
		m_objectConstantBuffer.m_matrix = p_Entity->p_transform->WorldMatrix;

		DXS.m_deviceContext->UpdateSubresource(DXS.m_constantBuffers[CB_OBJECT],
			0, nullptr, &m_objectConstantBuffer, 0, 0);

		unsigned int offset = 0;
		unsigned int stride = sizeof(SVertexPosColor);

		// Input Assembler
		DXS.m_deviceContext->IASetInputLayout(DXS.m_texturedInputLayout);
		DXS.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DXS.m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		DXS.m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, offset);

		// Vertex Shader
		DXS.m_deviceContext->VSSetConstantBuffers(0, 3, DXS.m_constantBuffers);
		DXS.m_deviceContext->VSSetShader(DXS.m_texturedVertexShader, nullptr, 0);

		// Rasterizer
		DXS.m_deviceContext->RSSetState(DXS.m_currentRasterrizerState);
		DXS.m_deviceContext->RSSetViewports(1, &DXS.m_viewPort);

		// Pixel Shader
		DXS.m_deviceContext->PSSetConstantBuffers(0, 1, &DXS.m_constantBuffers[CB_LIGHT]);
		DXS.m_deviceContext->PSSetShader(DXS.m_texturedPixelShader, nullptr, 0);
		DXS.m_deviceContext->PSSetSamplers(0, 1, &m_textureData.m_textureSampler);
		DXS.m_deviceContext->PSSetShaderResources(0, 1, &m_textureData.m_shaderResourceView);

		// Output Merger
		DXS.m_deviceContext->OMSetRenderTargets(1, &DXS.m_renderTargetView, DXS.m_depthStencilView);
		DXS.m_deviceContext->OMSetDepthStencilState(DXS.m_depthStencilState, 1);

		// Objekt zeichnen
		DXS.m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
	}
	else
	{
		m_objectConstantBuffer.m_matrix = p_Entity->p_transform->WorldMatrix;

		DXS.m_deviceContext->UpdateSubresource(DXS.m_constantBuffers[CB_OBJECT],
			0, nullptr, &m_objectConstantBuffer, 0, 0);

		unsigned int offset = 0;
		unsigned int stride = sizeof(SVertexPosColor);

		// Input Assembler
		DXS.m_deviceContext->IASetInputLayout(DXS.m_simpleInputLayout);
		DXS.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DXS.m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		DXS.m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, offset);

		// Vertex Shader
		DXS.m_deviceContext->VSSetConstantBuffers(0, 3, DXS.m_constantBuffers);
		DXS.m_deviceContext->VSSetShader(DXS.m_simpleVertexShader, nullptr, 0);

		// Rasterizer
		DXS.m_deviceContext->RSSetState(DXS.m_currentRasterrizerState);
		DXS.m_deviceContext->RSSetViewports(1, &DXS.m_viewPort);

		// Pixel Shader
		DXS.m_deviceContext->PSSetConstantBuffers(0, 1, &DXS.m_constantBuffers[CB_LIGHT]);
		DXS.m_deviceContext->PSSetShader(DXS.m_simplePixelShader, nullptr, 0);

		// Output Merger
		DXS.m_deviceContext->OMSetRenderTargets(1, &DXS.m_renderTargetView, DXS.m_depthStencilView);
		DXS.m_deviceContext->OMSetDepthStencilState(DXS.m_depthStencilState, 1);

		// Objekt zeichnen
		DXS.m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
	}
}

int CMesh::AddTexture(LPCWSTR _fileName)
{
	HRESULT hr = CreateWICTextureFromFile(DXS.m_device, _fileName, &m_textureData.m_texture, &m_textureData.m_shaderResourceView);
	if (FAILED(hr))
	{
		MessageBox(nullptr, _fileName, L"Error", MB_OK);
	}

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // Lineare Interpolation
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	DXS.m_device->CreateSamplerState(&desc, &m_textureData.m_textureSampler);

	m_usesTexture = true;
	return 0;
}
