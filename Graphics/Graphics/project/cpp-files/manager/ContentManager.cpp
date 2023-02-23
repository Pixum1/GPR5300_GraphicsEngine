#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/Game.h"
#include "../../header-files/manager/ContentManager.h"
#include "../../header-files/gameobjects/components/Mesh.h"
#include "../../header-files/gameobjects/materials/Material.h"
#include "../../header-files/gameobjects/materials/Cubemap.h"

bool CContentManager::Start()
{
	for (auto itr : m_entities)
	{
		itr->Start();
	}

	return true;
}

void CContentManager::Update(float _deltaTime)
{
	// Update entities
	for (auto itr : m_entities)
	{
		itr->Update(_deltaTime);

		if (Rotate)
			itr->Rotate(_deltaTime);

		if (Move)
			itr->Move(_deltaTime);

		if (Resize)
			itr->Resize(_deltaTime);
	}

	// Update Skybox
	if (p_skybox != nullptr)
	{
		p_skybox->Update(_deltaTime);
		p_skybox->p_transform->TranslationMatrix = XMMatrixTranslation(XMVectorGetX(XMLoadFloat3(&GetGame->m_camPos)), XMVectorGetY(XMLoadFloat3(&GetGame->m_camPos)), XMVectorGetZ(XMLoadFloat3(&GetGame->m_camPos)));
		p_skybox->p_transform->WorldMatrix = p_skybox->p_transform->LocalScaleMatrix * p_skybox->p_transform->RotationMatrix * p_skybox->p_transform->TranslationMatrix;
	}

	CleanUp();
}

void CContentManager::Render()
{
	// Render entities
	for (auto itr : m_entities)
	{
		if (itr->GetComponent<CMesh>() != nullptr)
		{
			itr->GetComponent<CMesh>()->Render();
		}
	}

	// Render skybox
	if (p_skybox != nullptr)
		p_skybox->GetComponent<CMesh>()->Render();
}

bool CContentManager::AddEntity(CEntity* _entity)
{
	if (!_entity || ContainsEntity(_entity))
	{
		return false;
	}

	// intialize entity and add if no errors occured
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

int CContentManager::CreateSkyBox()
{
	p_skybox = new CEntity(XMFLOAT3(0, 0, 0));
	SHC.CreateSphere(p_skybox->AddComponent<CMesh>(), 40, 40);
	p_skybox->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"SkyboxPixelShader.cso", L"SkyboxVertexShader.cso", new CCubemap(L"..\\Assets\\Skybox.dds", Albedo), nullptr));

	p_skybox->Init();

	p_skybox->Start();

	return 0;
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
