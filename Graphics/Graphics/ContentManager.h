#pragma once
#include "Entity.h"
#include <list>

class CContentManager
{
public:
	CContentManager();
	~CContentManager();

	void Init();
	void Update(float _deltaTime);
	void Render();

	bool AddEntity(CEntity* _entity);
	bool RemoveEntity(CEntity* _entity);
	bool ContainsEntity(CEntity* _entity);

public:
	bool Rotate;
	bool Move;
	bool Resize;

	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

private:
	void CleanUp();

	std::list<CEntity*> m_entities;
	std::list<CEntity*> m_entitiesToDelete;
};

