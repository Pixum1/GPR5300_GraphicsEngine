#pragma once
#include "Material.h"
class CSimpleMaterial : public CMaterial
{
public:
	CSimpleMaterial(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext) : CMaterial(_p_dxdevice, _p_dxcontext)
	{
		pixelShaderName = L"SimplePixelShader.cso";
		vertexShaderName = L"SimpleVertexShader.cso";

		Init();
	};

	// Inherited via CMaterial
	virtual int Init() override;
};