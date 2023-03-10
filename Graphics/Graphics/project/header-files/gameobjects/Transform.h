#pragma once
#include "../misc/GraphicsPCH.h"

class Transform
{
public:
	Transform()
	{
		Scale = { 1,1,1 };
		Rotation = { 0,0,0 };
		Position = { 0,0,0 };

		LocalUp = { 0,1,0 };
		LocalRight = { 1,0,0 };
		LocalForward = { 0,0,1 };

		TranslationMatrix = {};
		RotationMatrix = {};
		LocalScaleMatrix = {};

		localForward = {};
		localRight = {};
		localUp = {};

		WorldMatrix = { };
	}

	/// <summary>
	/// Update all values and the worldmatrix
	/// </summary>
	void Update();

public:
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

	XMFLOAT3 LocalUp;
	XMFLOAT3 LocalRight;
	XMFLOAT3 LocalForward;

	XMMATRIX TranslationMatrix;
	XMMATRIX RotationMatrix;
	XMMATRIX LocalScaleMatrix;

	XMMATRIX WorldMatrix;

private:
	XMVECTOR localUp;
	XMVECTOR localRight;
	XMVECTOR localForward;
};

