#include "GraphicsPCH.h"
#include "Cursor.h"
#include "Game.h"
#include "Helper.h"


CCursor::CCursor(LPCWSTR _fileName) : CImage2D(XMFLOAT2(), _fileName)
{
	p_transform->Scale.x = p_transform->Scale.x / 2 - 10;

	m_sourceRect.left = 0;
	m_sourceRect.right = p_transform->Scale.x;
}

CCursor::~CCursor()
{
}

void CCursor::Update(float _deltatime)
{
	p_transform->Position = IPM.GetMousePos();

	if (IPM.GetMouseKey(0))
	{
		m_sourceRect.left = p_transform->Scale.x;
		m_sourceRect.right = p_transform->Scale.x * 2;
	}
	else
	{
		m_sourceRect.left = 0;
		m_sourceRect.right = p_transform->Scale.x;
	}
}
