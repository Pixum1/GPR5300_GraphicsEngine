#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/manager/ShapeCreator.h"

void ShapeCreator::CreateCube(CMesh* _p_mesh, XMFLOAT4 _color)
{
	_p_mesh->VertexCount = 4 * 6;
	_p_mesh->IndexCount = 6 * 6;

	_p_mesh->Vertices = new VertexData[_p_mesh->VertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->IndexCount];

	int i = 0;
	// up
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f),_color, XMFLOAT2(0.5f, 0)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), _color, XMFLOAT2(1, 0)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), _color, XMFLOAT2(0.5f, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), _color, XMFLOAT2(1, 0.5f)};

	// down
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), _color, XMFLOAT2(0.5f, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), _color, XMFLOAT2(1, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, -1.0f, 0.0f), _color, XMFLOAT2(0.5f, 1)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), _color, XMFLOAT2(1, 1)};

	// front
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), _color, XMFLOAT2(0, 0.25f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), _color, XMFLOAT2(0.25f, 0.25f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), _color, XMFLOAT2(0, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f),_color, XMFLOAT2(0.25f, 0.5f)};

	// right
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0.25f, 0)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0.5f, 0)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0.25f, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0.5f, 0.5f)};

	// back
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), _color, XMFLOAT2(0, 0)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, 0.0f, 1.0f), _color, XMFLOAT2(0.25f, 0)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), _color, XMFLOAT2(0, 0.25f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), _color, XMFLOAT2(0.25f, 0.25f)};

	// left
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(-1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0.5f, 0.5f)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f),_color, XMFLOAT2(0, 1)};
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), _color, XMFLOAT2(0.5f, 1)};


	i = 0;
	for (int j = 0; j < _p_mesh->VertexCount; j += 4)
	{
		_p_mesh->Indices[i++] = j;
		_p_mesh->Indices[i++] = j + 2;
		_p_mesh->Indices[i++] = j + 1;

		_p_mesh->Indices[i++] = j;
		_p_mesh->Indices[i++] = j + 3;
		_p_mesh->Indices[i++] = j + 2;
	}
}

void ShapeCreator::CreateOktaeder(CMesh* _p_mesh, XMFLOAT4 _color)
{
	_p_mesh->VertexCount = 8 * 3;
	_p_mesh->IndexCount = 8 * 3;

	_p_mesh->Vertices = new VertexData[_p_mesh->VertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->IndexCount];

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
	_p_mesh->Vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, -1), _color };
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, -1, -1), _color };

	for (i = 0; i < _p_mesh->VertexCount; i++)
	{
		_p_mesh->Indices[i] = i;
	}
}

void ShapeCreator::CreateSphere(CMesh* _p_mesh, int _slices, int _heightSegments, XMFLOAT4 _color)
{
	if (_slices < 2 || _heightSegments < 3)
		return;

	_p_mesh->VertexCount = _slices * _heightSegments + 2 + _heightSegments;
	_p_mesh->IndexCount = _heightSegments * _slices * 6;

	_p_mesh->Vertices = new VertexData[_p_mesh->VertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->IndexCount];

	ZeroMemory(_p_mesh->Vertices, _p_mesh->VertexCount * sizeof(VertexData));
	ZeroMemory(_p_mesh->Indices, _p_mesh->IndexCount * sizeof(WORD));

	int i = 0;
	// upper half
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(0, 0.5f, 0), _color, XMFLOAT2(0.5f, 0) };
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
			_p_mesh->Vertices[i++] = { pos, pos, _color, XMFLOAT2(1 - (x / _slices), y / _heightSegments) };
		}
	}
	_p_mesh->Vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(0, -0.5f, 0), _color, XMFLOAT2(0.5f, 1) };

	i = 0;

	for (int x = 0; x < _slices; x++)
	{
		_p_mesh->Indices[i++] = 0;
		_p_mesh->Indices[i++] = x + 1;

		_p_mesh->Indices[i++] = x + 2;
	}

	// middle
	for (int y = 0; y < _heightSegments - 1; y++)
	{
		for (int x = 0; x < _slices; x++)
		{
			_p_mesh->Indices[i++] = x + 1 + y * (_slices + 1);
			_p_mesh->Indices[i++] = x + 1 + (_slices + 1) + y * (_slices + 1);
			_p_mesh->Indices[i++] = x + 2 + y * (_slices + 1);

			_p_mesh->Indices[i++] = x + 2 + y * (_slices + 1);
			_p_mesh->Indices[i++] = x + 1 + (_slices + 1) + y * (_slices + 1);
			_p_mesh->Indices[i++] = x + 2 + (_slices + 1) + y * (_slices + 1);
		}
	}

	// lower half
	for (int x = 0; x < _slices; x++)
	{
		_p_mesh->Indices[i++] = _p_mesh->VertexCount - 1;
		_p_mesh->Indices[i++] = _p_mesh->VertexCount - 1 - (_slices + 1) + 1 + x;
		_p_mesh->Indices[i++] = _p_mesh->VertexCount - 1 - (_slices + 1) + x;
	}
}

void ShapeCreator::CreatePlane(CMesh* _p_mesh, XMFLOAT4 _color)
{
	_p_mesh->VertexCount = 4;
	_p_mesh->IndexCount = 6;

	_p_mesh->Vertices = new VertexData[_p_mesh->VertexCount];
	_p_mesh->Indices = new WORD[_p_mesh->IndexCount];

	int i = 0;
	// up
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
