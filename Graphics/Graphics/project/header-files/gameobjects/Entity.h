#pragma once
#include <vector>

#include "../misc/VertexData.h"
#include "../misc/ConstantBuffer.h"
#include "Transform.h"

class Component;

class Entity
{
public:
	Entity(XMFLOAT3 _pos = XMFLOAT3(0,0,0));

	/// <summary>
	/// Initializes the transform and all components
	/// </summary>
	/// <returns></returns>
	virtual bool Init();
	/// <summary>
	/// Calls Start() in all components
	/// </summary>
	/// <returns></returns>
	virtual bool Start();
	/// <summary>
	/// Calls Update() in all components
	/// </summary>
	/// <param name="_deltaTime"></param>
	virtual void Update(float _deltaTime);
	/// <summary>
	/// Calls DeInit() in all components
	/// </summary>
	virtual void DeInit();
	/// <summary>
	/// Get a specific component
	/// </summary>
	/// <typeparam name="T">Type of component</typeparam>
	/// <returns></returns>
	template<typename T>
	T* GetComponent();

	/// <summary>
	/// Add a specific component to the entity
	/// </summary>
	/// <typeparam name="T">Type of component</typeparam>
	/// <returns></returns>
	template<typename T>
	T* AddComponent();

	// Testing Methods - Called by ContentManager when specific button is pressed
	void Move(float _deltaTime);
	void Rotate(float _deltaTime);
	void Resize(float _deltatime);

public:
	Transform* p_transform;

private:
	float time = 0;						// Used for testing in Move()
	XMFLOAT3 startPos;				// Used for testing in Move()
	std::vector<Component*> allComponents;

protected:
	bool inValid = false;
};

template<typename T>
inline T* Entity::GetComponent()
{
	for (Component* c : allComponents)
	{
		if (T* component = dynamic_cast<T*>(c))
		{
			return component;
		}
	}
	return nullptr;
}

template<typename T>
inline T* Entity::AddComponent()
{
	if (std::is_base_of<Component, T>::value)
	{
		T* c = new T(this);
		allComponents.push_back(c);
		return c;
	}
	return nullptr;
}
