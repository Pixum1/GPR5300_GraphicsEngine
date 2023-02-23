#pragma once

enum CB_Type
{
	CB_APPLICATION,
	CB_FRAME,
	CB_OBJECT,
	CB_LIGHT,

	NumConstantBuffers
};

struct SDirectXSettings
{
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;

	ID3D11RenderTargetView* m_renderTargetView = nullptr;

	// Depth Stencil
	ID3D11Texture2D* m_depthStencilBuffer = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11RasterizerState* m_rasterrizerStateSolid = nullptr;
	ID3D11RasterizerState* m_rasterrizerStateWireframe = nullptr;

	ID3D11RasterizerState* m_currentRasterrizerState = nullptr;

	D3D11_VIEWPORT m_viewPort;
	ID3D11Buffer* m_constantBuffers[NumConstantBuffers];
};
