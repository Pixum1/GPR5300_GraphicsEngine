#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/gameobjects/Entity.h"
#include "../../header-files/Game.h"
#include "../../header-files/gameobjects/components/Component.h"
#include "../../header-files/misc/MathHelper.h"

Entity::Entity(XMFLOAT3 _pos)
{
	p_transform = new Transform();
	p_transform->Position = _pos;

	startPos = _pos;
}

bool Entity::Init()
{
	if (inValid)
		return false;

	for (Component* c : allComponents)
	{
		c->Init(DXS.DxDevice, DXS.DxContext);
	}

	return true;
}

bool Entity::Start()
{
	for (Component* c : allComponents)
	{
		c->Start();
	}

	return true;
}

void Entity::Update(float _deltaTime)
{
	p_transform->Update();

	for (Component* c : allComponents)
	{
		c->Update();
	}
}

void Entity::DeInit()
{
	for (Component* c : allComponents)
	{
		c->DeInit();
	}
}

#pragma region Experimental
void Entity::Move(float _deltaTime)
{
	time += _deltaTime;

	p_transform->Position.y = startPos.y + (0.5f * sin(time));
}

void Entity::Rotate(float _deltaTime)
{
	p_transform->Rotation.x += 20 * _deltaTime;
	p_transform->Rotation.y += 20 * _deltaTime;
	p_transform->Rotation.z += 20 * _deltaTime;
}

void Entity::Resize(float _deltatime)
{
	time += _deltatime;

	p_transform->Scale = XMFLOAT3(1, 1, 1) + XMFLOAT3(0.5f, 0.5f, 0.5f) * sin(time);
}
#pragma endregion

