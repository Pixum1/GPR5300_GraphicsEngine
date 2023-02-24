#pragma once
#include "../gameobjects/Entity.h"
#include <list>

class ContentManager
{
public:
	/// <summary>
	/// Calls Start of each entity
	/// </summary>
	/// <returns></returns>
	bool Start();
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
	bool AddEntity(Entity* _p_entity);
	/// <summary>
	/// Remove an entity from the list
	/// </summary>
	/// <param name="_entity">Entity to remove</param>
	/// <returns></returns>
	bool RemoveEntity(Entity* _p_entity);
	/// <summary>
	/// Checks if an entity exists in the list
	/// </summary>
	/// <param name="_entity">Entity to check</param>
	/// <returns></returns>
	bool ContainsEntity(Entity* _p_entity);

	int CreateSkyBox();

private:
	/// <summary>
	/// Removes all entities that should be destroyed and deinitializes them
	/// </summary>
	void CleanUp();

public:
	// Experimental - for testing purposes
	bool Rotate;
	bool Move;
	bool Resize;

private:
	std::list<Entity*> entities;				// holds all entities
	std::list<Entity*> entitiesToDelete;		// holds all entities that need to be destroyed

	Entity* p_skybox;
};

