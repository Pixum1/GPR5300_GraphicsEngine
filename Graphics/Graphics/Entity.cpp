#include "GraphicsPCH.h"
#include "Entity.h"
#include "Game.h"

CEntity::CEntity(XMFLOAT3 _pos)
{
	p_transform = new CTransform();
	p_transform->Position = _pos;
}

CEntity::~CEntity()
{
}

bool CEntity::Initialize()
{
	if (m_InValid)
		return false;

	p_transform->Init();

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(SVertexPosColor) * m_vertexCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ressourceData = { 0 };
	ressourceData.pSysMem = m_vertices;

	HRESULT hr = DXS.m_device->CreateBuffer(&bufferDesc, &ressourceData, &m_vertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(WORD) * m_indexCount;

	ressourceData.pSysMem = m_indices;

	hr = DXS.m_device->CreateBuffer(&bufferDesc, &ressourceData, &m_indexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void CEntity::Update(float _deltaTime)
{
	//p_transform->Update();
}

void CEntity::Render()
{
	p_transform->Update();
	//// Prepare Object to World Matrix
	//XMMATRIX scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	//XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
	//                                XMConvertToRadians(m_rotation.x), 
	//                                XMConvertToRadians(m_rotation.y), 
	//                                XMConvertToRadians(m_rotation.z));
	//XMMATRIX translation = XMMatrixTranslation(m_position. x, 
	//                    m_position.y, m_position.z);
	
	// Saufen, Rauchen, Taxifahren
	m_objectConstantBuffer.m_matrix = p_transform->WorldMatrix;

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

void CEntity::CleanUp()
{
	p_transform->DeInit();
}
