#include "GraphicsPCH.h"
#include "Entity.h"
#include "Game.h"
#include "Component.h"

CEntity::CEntity(XMFLOAT3 _pos, XMFLOAT3 _rot)
{
	p_transform = new CTransform();
	p_transform->Position = _pos;
	p_transform->Rotation = _rot;
}

CEntity::~CEntity()
{

}

bool CEntity::Init()
{
	if (m_InValid)
		return false;

	p_transform->Init();

	for (CComponent* c : AllComponents)
	{
		c->Init(DXS.m_device, DXS.m_deviceContext);
	}

	return true;

}

bool CEntity::Start()
{
	for (CComponent* c : AllComponents)
	{
		c->Start();
	}

	return true;
}

void CEntity::Update(float _deltaTime)
{
	p_transform->Update();

	for (CComponent* c : AllComponents)
	{
		c->Update();
	}
}

void CEntity::DeInit()
{
	p_transform->DeInit();

	for (CComponent* c : AllComponents)
	{
		c->DeInit();
	}
}

void CEntity::Move(float _deltaTime)
{
	if (p_transform->Position.y >= 3 && dir == 1)
		dir = -1;
	else if (p_transform->Position.y <= -3 && dir == -1)
		dir = 1;

	if (dir == 1)
		p_transform->Position.y += 1 * _deltaTime;
	else if (dir == -1)
		p_transform->Position.y -= 1 * _deltaTime;
}

void CEntity::Rotate(float _deltaTime)
{
	p_transform->Rotation.x += 20 * _deltaTime;
	p_transform->Rotation.y += 20 * _deltaTime;
	p_transform->Rotation.z += 20 * _deltaTime;
}
