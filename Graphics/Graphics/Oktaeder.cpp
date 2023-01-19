#include "GraphicsPCH.h"
#include "Oktaeder.h"

COktaeder::COktaeder(XMFLOAT4 _col, XMFLOAT3 _pos) : CEntity(_pos)
{
	m_vertexCount = 8 * 3;
	m_indexCount = 8 * 3;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(1, 1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, 1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(1, 1, -1), _col };

	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(1, 1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(1, 1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, 1, 1), _col };

	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(-1, 1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, 1, 1),	_col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(-1, 1, 1), _col };

	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(-1, 1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, 1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, 1, -1),	_col };

	//----

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(1, -1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(1, -1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, -1, -1), _col };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(1, -1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, -1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(1, -1, 1), _col };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(-1, -1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(-1, -1, 1), _col };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, 1),	_col };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(-1, -1, -1), _col };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, -1),	_col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, -1, -1), _col };

	for (i = 0; i < m_vertexCount; i++)
	{
		m_indices[i] = i;
	}
}

COktaeder::~COktaeder()
{

}

void COktaeder::Update(float _deltaTime)
{
	p_transform->Rotation.x += -35 * _deltaTime;
	p_transform->Rotation.y += 14 * _deltaTime;
}
