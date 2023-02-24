#include "../../header-files/gameobjects/Transform.h"

void Transform::Update()
{
	// Update Matrices
	TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);
	RotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(Rotation.x), XMConvertToRadians(Rotation.y), XMConvertToRadians(Rotation.z));
	LocalScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	// Update Local directions
	localUp = XMVector3TransformCoord(XMVectorSet(0, 1, 0, 0), RotationMatrix);
	localRight = XMVector3TransformCoord(XMVectorSet(1, 0, 0, 0), RotationMatrix);
	localForward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), RotationMatrix);

	LocalUp = { XMVectorGetX(localUp), XMVectorGetY(localUp), XMVectorGetZ(localUp) };
	LocalRight = { XMVectorGetX(localRight), XMVectorGetY(localRight), XMVectorGetZ(localRight) };
	LocalForward = { XMVectorGetX(localForward), XMVectorGetY(localForward), XMVectorGetZ(localForward) };

	// Update World matrix
	WorldMatrix = LocalScaleMatrix * RotationMatrix * TranslationMatrix;
}

