#pragma once
#include <vector>

#include "../misc/VertexPosColor.h"
#include "../misc/ConstantBuffer.h"
#include "Transform.h"

class CComponent;

class CEntity
{
public:
	CEntity(XMFLOAT3 _pos = XMFLOAT3(0,0,0), XMFLOAT3 _rot = XMFLOAT3(0,0,0));
	virtual ~CEntity();

	virtual bool Init();					// Erzeugen, zb Texturen Laden
	virtual bool Start();
	virtual void Update(float _deltaTime);		// Jeden Frame zur Berechnung
	virtual void DeInit();

	static void* operator new(size_t _size)
	{
		return _aligned_malloc(_size, 16);
	}

	static void operator delete(void* _memory)
	{
		_aligned_free(_memory);
	}

	template<typename T>
	T* GetComponent();

	template<typename T>
	T* AddComponent();

	// Testing Methods
	void Move(float _deltaTime);
	void Rotate(float _deltaTime);
	void Resize(float _deltatime);

public:
	CTransform* p_transform;

	std::vector<CComponent*> AllComponents;

private:
	float dir = 1;
	float m_time = 0;
	XMFLOAT3 m_startPos;

protected:
	bool m_InValid = false;
};

template<typename T>
inline T* CEntity::GetComponent()
{
	for (CComponent* c : AllComponents)
	{
		if (T* component = dynamic_cast<T*>(c))
		{
			return component;
		}
	}
	return nullptr;
}

template<typename T>
inline T* CEntity::AddComponent()
{
	if (std::is_base_of<CComponent, T>::value)
	{
		T* c = new T(this);
		AllComponents.push_back(c);
		return c;
	}
	return nullptr;
}
