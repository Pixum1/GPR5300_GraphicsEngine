#pragma once
#include "../gameobjects/Entity.h"
#include <list>

class CContentManager
{
public:
	/// <summary>
	/// Calls Update of each entity, sets the skybox worldmatrix
	/// </summary>
	/// <param name="_deltaTime"></param>
	void Update(float _deltaTime);
	/// <summary>
	/// Calls Render in the mesh component of each entity
	/// </summary>
	void Render();

	/// <summary>
	/// Add an entity to the list if it is not already contained
	/// </summary>
	/// <param name="_entity">Entity to add</param>
	/// <returns></returns>
	bool AddEntity(CEntity* _entity);
	/// <summary>
	/// Remove an entity from the list
	/// </summary>
	/// <param name="_entity">Entity to remove</param>
	/// <returns></returns>
	bool RemoveEntity(CEntity* _entity);
	/// <summary>
	/// Checks if an entity exists in the list
	/// </summary>
	/// <param name="_entity">Entity to check</param>
	/// <returns></returns>
	bool ContainsEntity(CEntity* _entity);

	int CreateSkyBox();

private:
	/// <summary>
	/// Removes all entities that should be destroyed
	/// </summary>
	void CleanUp();

public:
	// Experimental - for testing purposes
	bool Rotate;
	bool Move;
	bool Resize;

private:
	std::list<CEntity*> m_entities;				// holds all entities
	std::list<CEntity*> m_entitiesToDelete;		// holds all entities that need to be destroyed

	CEntity* p_skybox;
};

