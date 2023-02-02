#include "../../header-files/gameobjects/Transform.h"

void CTransform::Init()
{
}

void CTransform::Update()
{
	TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);
	RotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(Rotation.x), XMConvertToRadians(Rotation.y), XMConvertToRadians(Rotation.z));
	LocalScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	localUp = XMVector3TransformCoord(XMVectorSet(0, 1, 0, 0), RotationMatrix);
	localRight = XMVector3TransformCoord(XMVectorSet(1, 0, 0, 0), RotationMatrix);
	localForward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), RotationMatrix);

	LocalUp = { XMVectorGetX(localUp), XMVectorGetY(localUp), XMVectorGetZ(localUp) };
	LocalRight = { XMVectorGetX(localRight), XMVectorGetY(localRight), XMVectorGetZ(localRight) };
	LocalForward = { XMVectorGetX(localForward), XMVectorGetY(localForward), XMVectorGetZ(localForward) };

	WorldMatrix = LocalScaleMatrix * RotationMatrix * TranslationMatrix;
}

void CTransform::DeInit()
{
}
