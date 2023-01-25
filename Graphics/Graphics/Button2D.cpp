#include "GraphicsPCH.h"
#include "Button2D.h"
#include "Game.h"
#include "Helper.h"

CButton2D::CButton2D(XMFLOAT2 _pos, LPCWSTR _fileName, BTNCALLBACK _callback) : CImage2D(_pos, _fileName)
{
	m_callback = _callback;
	p_transform->Scale.y = p_transform->Scale.y / 3;
}

CButton2D::~CButton2D()
{
}

void CButton2D::Update(float _deltaTime)
{
	if (PointInRect(p_transform->Position, p_transform->Scale, IPM.GetMousePos()))
	{
		if (IPM.GetMouseKeyDown(0))
		{
			m_wasClicked = true;
		}

		if (IPM.GetMouseKey(0) && m_wasClicked) // click
		{
			m_sourceRect.top = p_transform->Scale.y * 2;
			m_sourceRect.bottom = p_transform->Scale.y * 3;
		}
		else // hover
		{
			m_sourceRect.top = p_transform->Scale.y;
			m_sourceRect.bottom = p_transform->Scale.y * 2;
		}

		if (m_wasClicked && IPM.GetMouseKeyUp(0))
		{
			m_callback(this);
		}
	}
	else
	{
		if (m_wasClicked) // was clicked
		{
			m_sourceRect.top = p_transform->Scale.y * 2;
			m_sourceRect.bottom = p_transform->Scale.y * 3;
		}
		else // default
		{
			m_sourceRect.top = 0;
			m_sourceRect.bottom = p_transform->Scale.y;
		}
	}

	if (IPM.GetMouseKeyUp(0))
	{
		m_wasClicked = false;
	}
}
