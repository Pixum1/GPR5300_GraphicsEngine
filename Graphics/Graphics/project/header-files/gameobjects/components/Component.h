#pragma once
#include "../../misc/GraphicsPCH.h"

class Entity;

class Component
{
public:
	Component(Entity* _p_entity) 
	{
		p_Entity = _p_entity;
		IsActive = true;
	}

	virtual bool Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext) = 0;
	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual bool DeInit() = 0;

public:
	Entity* p_Entity;
	bool IsActive;

protected:
	ID3D11Device* p_dxdevice = nullptr;
	ID3D11DeviceContext* p_dxcontext = nullptr;
};

