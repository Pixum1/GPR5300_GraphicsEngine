#pragma once

#include "VertexPosColor.h"
#include "ConstantBuffer.h"
#include "Transform.h"

class CEntity
{
public:
	CEntity(XMFLOAT3 _pos);
	virtual ~CEntity();

	virtual bool Initialize();					// Erzeugen, zb Texturen Laden
	virtual void Update(float _deltaTime);		// Jeden Frame zur Berechnung
	virtual void Render();						// Jeden Frame zum Anzeigen
	virtual void CleanUp();

	static void* operator new(size_t _size)
	{
		return _aligned_malloc(_size, 16);
	}

	static void operator delete(void* _memory)
	{
		_aligned_free(_memory);
	}

public:
	CTransform* p_transform;

protected:
	SVertexPosColor* m_vertices;
	WORD* m_indices;

	int m_vertexCount;
	int m_indexCount;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	SStandardConstantBuffer m_objectConstantBuffer;
	bool m_InValid = false;
};

