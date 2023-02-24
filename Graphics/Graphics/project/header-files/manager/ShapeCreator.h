#pragma once
#include "../gameobjects/components/Mesh.h"

class ShapeCreator
{
public:
	void CreateCube(Mesh* _p_mesh, XMFLOAT4 _color = XMFLOAT4(1,1,1,1));
	void CreateOktaeder(Mesh* _p_mesh, XMFLOAT4 _color = XMFLOAT4(1, 1, 1, 1));
	void CreateSphere(Mesh* _p_mesh, int _slices, int _heightSegments, XMFLOAT4 _color = XMFLOAT4(1, 1, 1, 1));
	void CreatePlane(Mesh* _p_mesh, XMFLOAT4 _color = XMFLOAT4(1, 1, 1, 1));
};

