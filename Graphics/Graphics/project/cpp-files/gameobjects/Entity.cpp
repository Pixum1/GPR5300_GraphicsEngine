#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/gameobjects/Entity.h"
#include "../../header-files/Game.h"
#include "../../header-files/gameobjects/components/Component.h"
#include "../../header-files/misc/MathHelper.h"

CEntity::CEntity(XMFLOAT3 _pos, XMFLOAT3 _rot)
{
	p_transform = new CTransform();
	p_transform->Position = _pos;
	p_transform->Rotation = _rot;

	m_startPos = _pos;
}

CEntity::~CEntity()
{

}

bool CEntity::Init()
{
	if (m_InValid)
		return false;

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
	for (CComponent* c : AllComponents)
	{
		c->DeInit();
	}
}

void CEntity::Move(float _deltaTime)
{
	m_time += _deltaTime;

	p_transform->Position.y = m_startPos.y + (0.5f * sin(m_time));
}

void CEntity::Rotate(float _deltaTime)
{
	p_transform->Rotation.x += 20 * _deltaTime;
	p_transform->Rotation.y += 20 * _deltaTime;
	p_transform->Rotation.z += 20 * _deltaTime;
}

void CEntity::Resize(float _deltatime)
{
	m_time += _deltatime;

	p_transform->Scale = XMFLOAT3(1,1,1) + XMFLOAT3(0.5f, 0.5f, 0.5f) * sin(m_time);
}
