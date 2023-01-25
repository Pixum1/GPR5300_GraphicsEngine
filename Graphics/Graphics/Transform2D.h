#pragma once
#include "GraphicsPCH.h"

class CTransform2D
{
public:
	CTransform2D()
	{
		Scale = { 1, 1};
		Rotation = 0;
		Position = { 0, 0};
	}

	void Init();
	void Update();
	void DeInit();

public:
	XMFLOAT2 Position;
	float Rotation;
	XMFLOAT2 Scale;
};

