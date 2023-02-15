#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/Game.h"
#include "../../header-files/manager/ContentManager.h"
#include "../../header-files/gameobjects/components/Mesh.h"
#include "../../header-files/gameobjects/materials/Material.h"

CContentManager::CContentManager()
{
}

CContentManager::~CContentManager()
{
}

void CContentManager::Init()
{
}

void CContentManager::Update(float _deltaTime)
{
	for (auto itr : m_entities)
	{
		itr->Update(_deltaTime);

		if (Rotate)
		{
			itr->Rotate(_deltaTime);
		}

		if (Move)
		{
			itr->Move(_deltaTime);
		}

		if (Resize)
		{
			itr->Resize(_deltaTime);
		}
	}

	CleanUp();
}

void CContentManager::Render()
{
	for (auto itr : m_entities)
	{
		if (itr->GetComponent<CMesh>() != nullptr)
		{
			itr->GetComponent<CMesh>()->Render();
		}
	}
}

bool CContentManager::AddEntity(CEntity* _entity)
{
	if (!_entity || ContainsEntity(_entity))
	{
		return false;
	}

	if (_entity->Init())
	{
		m_entities.push_back(_entity);
	}

	return false;
}

bool CContentManager::RemoveEntity(CEntity* _entity)
{
	if (!_entity || !ContainsEntity(_entity))
	{
		return false;
	}

	m_entitiesToDelete.push_back(_entity);
	return true;
}

bool CContentManager::ContainsEntity(CEntity* _entity)
{
	if (!_entity)
	{
		return false;
	}

	for (auto itr : m_entities)
	{
		if (itr == _entity)
		{
			return true;
		}
	}

	return false;
}

void CContentManager::CleanUp()
{
	for (auto itr : m_entitiesToDelete)
	{
		m_entities.remove(itr);
		itr->DeInit();
		delete(itr);
	}

	m_entitiesToDelete.clear();
}