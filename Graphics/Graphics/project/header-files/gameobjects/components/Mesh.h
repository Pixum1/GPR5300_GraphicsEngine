#pragma once
#include "../../misc/VertexData.h"
#include "../../misc/ConstantBuffer.h"
#include "Component.h"

class Material;

class Mesh : public Component
{
public:
	Mesh(Entity* _p_entity) : Component(_p_entity) {}
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
	void SetMaterial(Material* _p_mat);

public:
	VertexData* Vertices = nullptr;		// Contains Position, Color, UV and normals
	WORD* Indices = nullptr;
	int VertexCount;
	int IndexCount;
	Material* p_Material = nullptr;

private:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	StandardConstantBuffer objectConstantBuffer;
};

