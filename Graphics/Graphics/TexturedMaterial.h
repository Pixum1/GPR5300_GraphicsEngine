#pragma once
#include "Material.h"

class CTexturedMaterial : public CMaterial
{
public:
	CTexturedMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext) : CMaterial(_p_dxdevice, _p_dxcontext)
	{
		pixelShaderName = L"TexturedPixelShader.cso";
		vertexShaderName = L"TexturedVertexShader.cso";

		Init();
	};
	CTexturedMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext, LPCWSTR _fileName, D3D11_TEXTURE_ADDRESS_MODE _sampleMode, D3D11_FILTER _filter) 
		: CMaterial(_p_dxdevice, _p_dxcontext, _fileName, _sampleMode, _filter)
	{
		pixelShaderName = L"TexturedPixelShader.cso";
		vertexShaderName = L"TexturedVertexShader.cso";

		Init();

	}

	// Inherited via CMaterial
	virtual int Init() override;
};

