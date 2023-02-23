#pragma once
#include "../../misc/VertexData.h"
#include "../../misc/ConstantBuffer.h"
#include "Component.h"

class CMaterial;

class CMesh : public CComponent
{
public:
	CMesh(CEntity* _p_entity) : CComponent(_p_entity) 
	{
	}
	/// <summary>
	/// Assigns DirectX device and context
	/// </summary>
	/// <param name="_p_device"></param>
	/// <param name="_p_devicecontext"></param>
	/// <returns></returns>
	virtual bool Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext) override;
	/// <summary>
	/// Creates vertex and index buffer, calls Start in Material
	/// </summary>
	/// <returns></returns>
	virtual bool Start() override;
	virtual void Update() override;
	/// <summary>
	/// SafeReleases every directX component
	/// </summary>
	/// <returns></returns>
	virtual bool DeInit() override;

	/// <summary>
	/// Updates the shader
	/// </summary>
	void Render();
	void SetMaterial(CMaterial* _mat);

public:
	SVertexData* Vertices;		// Contains Position, Color, UV and normals
	WORD* Indices;
	int m_vertexCount;
	int m_indexCount;
	CMaterial* p_material;

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	SStandardConstantBuffer m_objectConstantBuffer;
};

