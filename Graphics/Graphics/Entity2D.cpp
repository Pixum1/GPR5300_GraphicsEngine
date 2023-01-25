#include "GraphicsPCH.h"
#include "Entity2D.h"
#include "Game.h"
#include "Component.h"
#include "Helper.h"

CEntity2D::CEntity2D(XMFLOAT2 _pos)
{
	p_transform = new CTransform2D();
	p_transform->Position = XMFLOAT2(_pos.x, _pos.y);
	p_transform->Rotation = 0;
	p_transform->Scale = XMFLOAT2(1, 1);
}

CEntity2D::~CEntity2D()
{
}

bool CEntity2D::Init()
{
	return true;
}

void CEntity2D::Update(float _deltaTime)
{
}

void CEntity2D::DeInit()
{

}
