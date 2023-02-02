#pragma once
#include "../../misc/GraphicsPCH.h"

class CEntity;

class CComponent
{
public:
	CComponent();
	CComponent(CEntity* _p_entity) 
	{
		p_Entity = _p_entity;
		isActive = true;
	}

	virtual bool Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_devicecontext) = 0;
	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual bool DeInit() = 0;

public:
	CEntity* p_Entity;
	bool isActive;
};

