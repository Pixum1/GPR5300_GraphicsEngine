#include "GraphicsPCH.h"
#include "Image2D.h"
#include "Game.h"

CImage2D::CImage2D(XMFLOAT2 _pos, LPCWSTR _fileName) : CEntity2D(_pos)
{
	m_textureData = ASM.LoadTexture(_fileName, WRAP, POINT);
	ID3D11Texture2D* tex2D = (ID3D11Texture2D*)m_textureData->m_texture;

	D3D11_TEXTURE2D_DESC tDesc;
	tex2D->GetDesc(&tDesc);

	p_transform->Scale.x = tDesc.Width;
	p_transform->Scale.y = tDesc.Height;

	m_sourceRect.left = 0;
	m_sourceRect.top = 0;
	m_sourceRect.right = p_transform->Scale.x;
	m_sourceRect.bottom = p_transform->Scale.y;
}

CImage2D::~CImage2D()
{
}

void CImage2D::Render()
{
	CTM.m_spriteBatch->Draw(m_textureData->m_shaderResourceView, 
		p_transform->Position,
		&m_sourceRect,
		Colors::White,
		XMConvertToRadians(p_transform->Rotation));
}
