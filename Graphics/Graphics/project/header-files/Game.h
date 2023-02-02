#pragma once
#include "settings/WindowSettings.h"
#include "settings/DirectXSettings.h"
#include "misc/ConstantBuffer.h"
#include "gameobjects/Entity.h"
#include "manager/ContentManager.h"
#include "manager/InputManager.h"
#include "manager/ShapeCreator.h"

#define WDS (*(CGame::Get()->GetWindowSettings()))
#define DXS (*(CGame::Get()->GetDirectXSettings()))
#define CTM (*(CGame::Get()->GetContentManager()))
#define IPM (*(CGame::Get()->GetInputManager()))
#define SHC (*(CGame::Get()->GetShapeCreator()))

#define WRAP (D3D11_TEXTURE_ADDRESS_WRAP)
#define MIRROR (D3D11_TEXTURE_ADDRESS_MIRROR)
#define MIRROR_ONCE (D3D11_TEXTURE_ADDRESS_MIRROR_ONCE)
#define CLAMP (D3D11_TEXTURE_ADDRESS_CLAMP)
#define BORDER (D3D11_TEXTURE_ADDRESS_BORDER)

#define LINEAR (D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR)
#define POINT (D3D11_FILTER_MIN_MAG_MIP_POINT)

#define FAILHR(errorcode) if (FAILED(hr)) { return errorcode; }

class CGame
{
private:
	CGame();
public:
	~CGame();


public:
	static CGame* Get()
	{
		static CGame* instance = new CGame();	// Diese Zeile wird nur beim ersten Mal ausgef�hrt
		return instance;						// Diese immer
	}

	// Beschreibt wie der Speicher allokiert werden soll, hier wird daf�r gesorgt 
	// dass die adresse durch 16 teilbar ist (Notwendig sp�ter f�r Kommunikation mit der Grafikkarte)
	static void* operator new(size_t _size)
	{
		return _aligned_malloc(_size, 16);
	}

	static void operator delete(void* _memory)
	{
		_aligned_free(_memory);
	}

private:
	SWindowSettings m_windowSettings;
	SDirectXSettings m_directXSettings;
	CContentManager m_contentManager;
	CInputManager m_inputManager;
	CShapeCreator m_shapeCreator;

	XMFLOAT3 m_camPos;
	XMFLOAT3 m_camRot;

	SStandardConstantBuffer m_applicationConstantBuffer;
	SStandardConstantBuffer m_frameConstantBuffer;
	SLightConstantBuffer m_lightConstantBuffer;

	bool m_isRunning;

	CMaterial* p_simpleMaterial;
	CMaterial* p_worldMapMaterial;
	CMaterial* p_happyMaterial;
	CMaterial* p_skyboxMaterial;

public:
	int Initialize(HINSTANCE _hInstance);
	int Run();
	void Finalize();

	inline SWindowSettings* GetWindowSettings() { return &m_windowSettings; }
	inline SDirectXSettings* GetDirectXSettings() { return &m_directXSettings; }
	inline CContentManager* GetContentManager() { return &m_contentManager; }
	inline CInputManager* GetInputManager() { return &m_inputManager; }
	inline CShapeCreator* GetShapeCreator() { return &m_shapeCreator; }

	void SwitchRasterizerState();

	float movementSpeed = 4;
	float rotationSpeed = 4;

private:
	int InitApplication(HINSTANCE _hInstance);
	int InitDirectX();
	int InitConstantBuffers();
	int LoadLevel();

	/*int CreateSimpleShader();
	int CreateTexturedShader();*/

	void ClearBackBuffer(const float _clearColor[4], float _clearDepth, UINT8 _clearStencil);

	void Update(float _deltaTime);
	void Render();
};

