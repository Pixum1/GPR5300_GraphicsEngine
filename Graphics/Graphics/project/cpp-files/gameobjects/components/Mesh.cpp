#include "../../../header-files/misc/GraphicsPCH.h"
#include "../../../header-files/Game.h"
#include "../../../header-files/gameobjects/components/Mesh.h"
#include "../../../header-files/gameobjects/materials/Material.h"


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
	m_objectConstantBuffer.m_matrix = p_Entity->p_transform->WorldMatrix;

	DXS.m_deviceContext->UpdateSubresource(DXS.m_constantBuffers[CB_OBJECT],
		0, nullptr, &m_objectConstantBuffer, 0, 0);

	unsigned int offset = 0;
	unsigned int stride = sizeof(SVertexPosColor);

	if (p_material == nullptr) return;

	p_material->Render();

	// Input Assembler
	DXS.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DXS.m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	DXS.m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, offset);

	// Vertex Shader
	DXS.m_deviceContext->VSSetConstantBuffers(0, 3, DXS.m_constantBuffers);

	// Rasterizer
	DXS.m_deviceContext->RSSetState(DXS.m_currentRasterrizerState);
	DXS.m_deviceContext->RSSetViewports(1, &DXS.m_viewPort);

	// Pixel Shader
	DXS.m_deviceContext->PSSetConstantBuffers(0, 1, &DXS.m_constantBuffers[CB_LIGHT]);
	DXS.m_deviceContext->PSSetConstantBuffers(1, 1, &DXS.m_constantBuffers[CB_OBJECT]);

	// Output Merger
	DXS.m_deviceContext->OMSetRenderTargets(1, &DXS.m_renderTargetView, DXS.m_depthStencilView);
	DXS.m_deviceContext->OMSetDepthStencilState(DXS.m_depthStencilState, 0);

	// Objekt zeichnen
	DXS.m_deviceContext->DrawIndexed(m_indexCount, 0, 0);

}

void CMesh::SetMaterial(CMaterial* _mat)
{
	p_material = _mat;

	p_material->Init();
}