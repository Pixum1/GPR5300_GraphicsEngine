#include "../../header-files/misc/GraphicsPCH.h"
#include "../../header-files/Game.h"
#include "../../header-files/manager/ContentManager.h"
#include "../../header-files/gameobjects/components/Mesh.h"
#include "../../header-files/gameobjects/materials/Material.h"
#include "../../header-files/gameobjects/materials/Cubemap.h"

bool ContentManager::Start()
{
	for (auto itr : entities)
	{
		itr->Start();
	}

	return true;
}

void ContentManager::Update(float _deltaTime)
{
	// Update entities
	for (auto itr : entities)
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
		p_skybox->p_transform->TranslationMatrix = XMMatrixTranslation(XMVectorGetX(XMLoadFloat3(&GetGame->CamPos)), XMVectorGetY(XMLoadFloat3(&GetGame->CamPos)), XMVectorGetZ(XMLoadFloat3(&GetGame->CamPos)));
		p_skybox->p_transform->WorldMatrix = p_skybox->p_transform->LocalScaleMatrix * p_skybox->p_transform->RotationMatrix * p_skybox->p_transform->TranslationMatrix;
	}

	CleanUp();
}

void ContentManager::Render()
{
	// Render entities
	for (auto itr : entities)
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

bool ContentManager::AddEntity(Entity* _entity)
{
	if (!_entity || ContainsEntity(_entity))
	{
		return false;
	}

	// intialize entity and add if no errors occured
	if (_entity->Init())
	{
		entities.push_back(_entity);
	}

	return false;
}

bool ContentManager::RemoveEntity(Entity* _entity)
{
	if (!_entity || !ContainsEntity(_entity))
	{
		return false;
	}

	entitiesToDelete.push_back(_entity);
	return true;
}

bool ContentManager::ContainsEntity(Entity* _entity)
{
	if (!_entity)
	{
		return false;
	}

	for (auto itr : entities)
	{
		if (itr == _entity)
		{
			return true;
		}
	}

	return false;
}

int ContentManager::CreateSkyBox()
{
	p_skybox = new Entity(XMFLOAT3(0, 0, 0));
	SHC.CreateSphere(p_skybox->AddComponent<CMesh>(), 40, 40);
	p_skybox->GetComponent<CMesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"SkyboxPixelShader.cso", L"SkyboxVertexShader.cso", new Cubemap(L"..\\Assets\\Skybox.dds", Albedo), nullptr));

	p_skybox->Init();

	p_skybox->Start();

	return 0;
}

void ContentManager::CleanUp()
{
	for (auto itr : entitiesToDelete)
	{
		entities.remove(itr);
		itr->DeInit();
		delete(itr);
	}

	entitiesToDelete.clear();
}
