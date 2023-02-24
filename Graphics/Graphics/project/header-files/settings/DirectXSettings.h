#pragma once

enum EConstantBufferType
{
	CB_APPLICATION,
	CB_FRAME,
	CB_OBJECT,
	CB_LIGHT,

	NumConstantBuffers
};

struct DirectXSettings
{
	ID3D11Device* DxDevice = nullptr;
	ID3D11DeviceContext* DxContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11RenderTargetView* RenderTargetView = nullptr;

	// Depth Stencil
	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;
	ID3D11DepthStencilState* DepthStencilState = nullptr;
	ID3D11RasterizerState* RasterrizerStateSolid = nullptr;
	ID3D11RasterizerState* RasterrizerStateWireframe = nullptr;

	ID3D11RasterizerState* CurrentRasterrizerState = nullptr;

	D3D11_VIEWPORT ViewPort;
	ID3D11Buffer* ConstantBuffers[NumConstantBuffers];
};
