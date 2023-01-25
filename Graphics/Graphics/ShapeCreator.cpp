#include "GraphicsPCH.h"
#include "ShapeCreator.h"

void CShapeCreator::CreateCube(CMesh* _p_mesh, XMFLOAT4 _color)
{
	_p_mesh->m_vertexCount = 4 * 6;
	_p_mesh->m_indexCount = 6 * 6;

	_p_mesh->Vertices = new SVertexPosColor[_p_mesh->m_vertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->m_indexCount];

	int i = 0;
	// oben
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f),_color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), _color };

	// unten
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, -1.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), _color };

	// vorne
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f),_color };

	// rechts
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color };

	// hinten
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, 0.0f, 1.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), _color };

	// links
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(-1.0f, 0.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f),_color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), _color };


	i = 0;
	for (int j = 0; j < _p_mesh->m_vertexCount; j += 4)
	{
		_p_mesh->Indices[i++] = j;
		_p_mesh->Indices[i++] = j + 2;
		_p_mesh->Indices[i++] = j + 1;

		_p_mesh->Indices[i++] = j;
		_p_mesh->Indices[i++] = j + 3;
		_p_mesh->Indices[i++] = j + 2;
	}
}

void CShapeCreator::CreateOktaeder(CMesh* _p_mesh, XMFLOAT4 _color)
{
	_p_mesh->m_vertexCount = 8 * 3;
	_p_mesh->m_indexCount = 8 * 3;

	_p_mesh->Vertices = new SVertexPosColor[_p_mesh->m_vertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->m_indexCount];

	int i = 0;
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(1, 1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, 1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(1, 1, -1), _color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(1, 1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(1, 1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, 1, 1), _color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(-1, 1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, 1, 1),	_color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(-1, 1, 1), _color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(-1, 1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, 1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, 1, -1),	_color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(1, -1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(1, -1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, -1, -1), _color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(1, -1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, -1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(1, -1, 1), _color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(-1, -1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(-1, -1, 1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, 1),	_color };

	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(-1, -1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, -1),	_color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, -1, -1), _color };

	for (i = 0; i < _p_mesh->m_vertexCount; i++)
	{
		_p_mesh->Indices[i] = i;
	}
}

void CShapeCreator::CreateSphere(CMesh* _p_mesh, int _slices, int _heightSegments, XMFLOAT4 _color)
{
	if (_slices < 2 || _heightSegments < 3)
	{
		//m_InValid = true;
		return;
	}

	_p_mesh->m_vertexCount = _slices * _heightSegments + 2 + _heightSegments;
	_p_mesh->m_indexCount = _heightSegments * _slices * 6;

	_p_mesh->Vertices = new SVertexPosColor[_p_mesh->m_vertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->m_indexCount];

	ZeroMemory(_p_mesh->Vertices, _p_mesh->m_vertexCount * sizeof(SVertexPosColor));
	ZeroMemory(_p_mesh->Indices, _p_mesh->m_indexCount * sizeof(WORD));

	int i = 0;
	// polkappe oben
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(0, 0.5f, 0), _color, XMFLOAT2(0.5f, 0)};
	XMFLOAT3 pos;
	float yPos;
	float radius;
	for (float y = 0; y < _heightSegments; y++)
	{
		yPos = cos(((y + 1) / (_heightSegments + 1) * XM_PI));
		radius = sin(((y + 1) / (_heightSegments + 1) * XM_PI));
		for (float x = 0; x <= _slices; x++)
		{
			pos = XMFLOAT3(sin(x / _slices * XM_2PI) * 0.5f * radius, yPos * 0.5f, cos(x / _slices * XM_2PI) * 0.5f * radius);
			_p_mesh->Vertices[i++] = { pos, pos, _color, XMFLOAT2(1-(x / _slices), y / _heightSegments)};
		}
	}
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(0, -0.5f, 0), _color, XMFLOAT2(0.5f, 1) };

	i = 0;
	// polkappe oben
	for (int x = 0; x < _slices; x++)
	{
		_p_mesh->Indices[i++] = 0;
		_p_mesh->Indices[i++] = x + 1;

		//if (x != _slices - 1)
		{
			_p_mesh->Indices[i++] = x + 2;
		}
		/*else
		{
			_p_mesh->Indices[i++] = 1;
		}*/
	}

	// mitte
	for (int y = 0; y < _heightSegments - 1; y++)
	{
		for (int x = 0; x < _slices; x++)
		{
			//if (x < _slices - 1)
			{
				_p_mesh->Indices[i++] = x + 1 + y * (_slices + 1);
				_p_mesh->Indices[i++] = x + 1 + (_slices + 1) + y * (_slices + 1);
				_p_mesh->Indices[i++] = x + 2 + y * (_slices + 1);

				_p_mesh->Indices[i++] = x + 2 + y * (_slices + 1);
				_p_mesh->Indices[i++] = x + 1 + (_slices + 1) + y * (_slices + 1);
				_p_mesh->Indices[i++] = x + 2 + (_slices + 1) + y * (_slices + 1);
			}
			/*else
			{
				_p_mesh->Indices[i++] = x + 1 + y * _slices;
				_p_mesh->Indices[i++] = x + 1 + _slices + y * _slices;
				_p_mesh->Indices[i++] = x + 2 + (y - 1) * _slices;

				_p_mesh->Indices[i++] = x + 2 + (y - 1) * _slices;
				_p_mesh->Indices[i++] = x + 1 + _slices + y * _slices;
				_p_mesh->Indices[i++] = x + 2 + _slices + (y - 1) * _slices;
			}*/
		}
	}

	// polkappe unten
	for (int x = 0; x < _slices; x++)
	{
		//if (x < _slices - 1)
		{
			_p_mesh->Indices[i++] = _p_mesh->m_vertexCount - 1;
			_p_mesh->Indices[i++] = _p_mesh->m_vertexCount - 1 - (_slices + 1) + 1 + x;
			_p_mesh->Indices[i++] = _p_mesh->m_vertexCount - 1 - (_slices + 1) + x;
		}
		/*else
		{
			_p_mesh->Indices[i++] = _p_mesh->m_vertexCount - 1;
			_p_mesh->Indices[i++] = _p_mesh->m_vertexCount - 1 - _slices;
			_p_mesh->Indices[i++] = _p_mesh->m_vertexCount - 1 - _slices + x;
		}*/
	}
}

void CShapeCreator::CreatePlane(CMesh* _p_mesh, XMFLOAT4 _color)
{
	_p_mesh->m_vertexCount = 4;
	_p_mesh->m_indexCount = 6;

	_p_mesh->Vertices = new SVertexPosColor[_p_mesh->m_vertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->m_indexCount];

	int i = 0;
	// oben
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, -0.5f), XMFLOAT3(1, 1, -1),_color, XMFLOAT2(0,1) };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.0f, -0.5f), XMFLOAT3(1, 1, -1),_color, XMFLOAT2(1,1) };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.5f), XMFLOAT3(1, 1, -1),_color, XMFLOAT2(1,0) };
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.5f), XMFLOAT3(1, 1, -1),_color, XMFLOAT2(0,0) };

	i = 0;
	_p_mesh->Indices[i++] = 0;
	_p_mesh->Indices[i++] = 3;
	_p_mesh->Indices[i++] = 2;

	_p_mesh->Indices[i++] = 2;
	_p_mesh->Indices[i++] = 1;
	_p_mesh->Indices[i++] = 0;
}
