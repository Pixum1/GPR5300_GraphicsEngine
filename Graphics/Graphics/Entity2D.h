#pragma once
#include "Transform2D.h"
#include <vector>

class CEntity2D
{
public:
	CEntity2D(XMFLOAT2 _pos);
	~CEntity2D();

	virtual bool Init();					// Erzeugen, zb Texturen Laden
	virtual void Update(float _deltaTime);		// Jeden Frame zur Berechnung
	virtual void Render() = 0;
	virtual void DeInit();

public:
	CTransform2D* p_transform;

};