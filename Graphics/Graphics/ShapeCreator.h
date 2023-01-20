#pragma once
#include "Mesh.h"

class CShapeCreator
{
public:
	void CreateCube(CMesh* _p_mesh, XMFLOAT4 _color = XMFLOAT4(1,1,1,1));
	void CreateOktaeder(CMesh* _p_mesh, XMFLOAT4 _color = XMFLOAT4(1, 1, 1, 1));
	void CreateSphere(CMesh* _p_mesh, int _slices, int _heightSegments, XMFLOAT4 _color = XMFLOAT4(1, 1, 1, 1));
};

