#pragma once
#include "VertexPosColor.h"
#include "ConstantBuffer.h"
#include "Component.h"
#include "TextureData.h"

class CMesh : public CComponent
{
public:
	CMesh(CEntity* _p_entity) : CComponent(_p_entity) {
		// additional initialization
		m_usesTexture = false;
	}
	// Inherited via CComponent
	virtual bool Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_devicecontext) override;
	virtual bool Start() override;
	virtual void Update() override;
	virtual bool DeInit() override;

	void Render();
	//void SetMaterial();
	int AddTexture(LPCWSTR _fileName);

public:
	SVertexPosColor* Vertices;
	WORD* Indices;
	int m_vertexCount;
	int m_indexCount;

protected:
	//Material* p_material;
	bool m_usesTexture;
	STextureData m_textureData;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	SStandardConstantBuffer m_objectConstantBuffer;
};

