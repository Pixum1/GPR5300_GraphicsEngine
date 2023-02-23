#include "../../../header-files/misc/GraphicsPCH.h"
#include "../../../header-files/Game.h"
#include "../../../header-files/gameobjects/components/Mesh.h"
#include "../../../header-files/gameobjects/materials/Material.h"


bool CMesh::Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext)
{
	p_dxdevice = _p_dxdevice;
	p_dxcontext = _p_dxcontext;

	return 0;
}

bool CMesh::Start()
{
	if (p_Material != nullptr)
		p_Material->Start();

	// Create vertex buffer
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexData) * VertexCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ressourceData = { 0 };
	ressourceData.pSysMem = Vertices;

	HRESULT hr = DXS.DxDevice->CreateBuffer(&bufferDesc, &ressourceData, &vertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	// Create Index Buffer
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(WORD) * IndexCount;

	ressourceData.pSysMem = Indices;

	hr = DXS.DxDevice->CreateBuffer(&bufferDesc, &ressourceData, &indexBuffer);
	if (FAILED(hr))
	{
		return false;
	}
}

void CMesh::Update()
{

}

bool CMesh::DeInit()
{
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);

	return true;
}

void CMesh::Render()
{
	objectConstantBuffer.Matrix = p_Entity->p_transform->WorldMatrix;

	DXS.DxContext->UpdateSubresource(DXS.ConstantBuffers[CB_OBJECT],
		0, nullptr, &objectConstantBuffer, 0, 0);

	unsigned int offset = 0;
	unsigned int stride = sizeof(VertexData);

	if (p_Material == nullptr) return;

	p_Material->Render();

	// Input Assembler
	DXS.DxContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DXS.DxContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DXS.DxContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, offset);

	// Vertex Shader
	DXS.DxContext->VSSetConstantBuffers(0, 3, DXS.ConstantBuffers);

	// Rasterizer
	DXS.DxContext->RSSetState(DXS.CurrentRasterrizerState);
	DXS.DxContext->RSSetViewports(1, &DXS.ViewPort);

	// Pixel Shader
	DXS.DxContext->PSSetConstantBuffers(0, 1, &DXS.ConstantBuffers[CB_LIGHT]);
	DXS.DxContext->PSSetConstantBuffers(1, 1, &DXS.ConstantBuffers[CB_OBJECT]);

	// Output Merger
	DXS.DxContext->OMSetRenderTargets(1, &DXS.RenderTargetView, DXS.DepthStencilView);
	DXS.DxContext->OMSetDepthStencilState(DXS.DepthStencilState, 0);

	// Draw object
	DXS.DxContext->DrawIndexed(IndexCount, 0, 0);

}

void CMesh::SetMaterial(Material* _mat)
{
	p_Material = _mat;
	p_Material->Init();
}