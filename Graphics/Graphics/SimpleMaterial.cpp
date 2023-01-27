#include "SimpleMaterial.h"

int CSimpleMaterial::Init()
{
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{
			"POSITION",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32B32_FLOAT,	// Float3
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexPosColor, Position),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		},
		{
			"NORMAL",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32B32_FLOAT,	// Float3
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexPosColor, Normal),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		},
		{
			"COLOR",						// Semantic - Identifikation im Shader
			0,								// Semantic index, falls es mehr als eins von diesem Typen vorhanden ist
			DXGI_FORMAT_R32G32B32A32_FLOAT,	// Float4
			0,								// Falls mehr als ein VertexShader vorhanden ist
			offsetof(SVertexPosColor, Color),
			D3D11_INPUT_PER_VERTEX_DATA,	// Werte einzeln für jeden Vertex nacheinander übergeben
			0
		}
	};
	int returnValue = CreateShader(vertexLayoutDesc, _countof(vertexLayoutDesc));

	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Could not create simple shader", L"Error", MB_OK);
	}

	return 0;
}
