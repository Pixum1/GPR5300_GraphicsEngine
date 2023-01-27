#include "GraphicsPCH.h"
#include "Game.h"
#include "ContentManager.h"
#include "Mesh.h"
#include "Material.h"

CContentManager::CContentManager()
{
}

CContentManager::~CContentManager()
{
}

void CContentManager::Init()
{
	m_spriteBatch = new SpriteBatch(DXS.m_deviceContext);
	m_spriteFont = new SpriteFont(DXS.m_device, L"Assets\\cambria.spritefont");
	m_cursor = new CCursor(L"Assets\\cursor.png");
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

	for (auto itr : m_entities2D)
	{
		itr->Update(_deltaTime);
	}
	m_cursor->Update(_deltaTime);

	CleanUp();
}

void CContentManager::Render()
{
	for (auto itr : m_entities)
	{
		if (itr->GetComponent<CMesh>() != nullptr)
		{
			if (itr->GetComponent<CMesh>()->p_material != nullptr)
				itr->GetComponent<CMesh>()->p_material->Render();
			
			itr->GetComponent<CMesh>()->Render();
		}
	}

	m_spriteBatch->Begin();
	for (auto itr : m_entities2D)
	{
		itr->Render();
	}
	m_cursor->Render();
	m_spriteBatch->End();
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

bool CContentManager::AddEntity(CEntity2D* _entity)
{
	if (!_entity || ContainsEntity(_entity))
	{
		return false;
	}

	if (_entity->Init())
	{
		m_entities2D.push_back(_entity);
	}

	return false;

	return false;
}

bool CContentManager::RemoveEntity(CEntity2D* _entity)
{
	if (!_entity || !ContainsEntity(_entity))
	{
		return false;
	}

	m_entities2DToDelete.push_back(_entity);
	return true;
}

bool CContentManager::ContainsEntity(CEntity2D* _entity)
{
	if (!_entity)
	{
		return false;
	}

	for (auto itr : m_entities2D)
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

	for (auto itr : m_entities2DToDelete)
	{
		m_entities2D.remove(itr);
		itr->DeInit();
		delete(itr);
	}

	m_entities2DToDelete.clear();

}
