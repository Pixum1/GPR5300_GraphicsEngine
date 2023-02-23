#pragma once
#include "settings/WindowSettings.h"
#include "settings/DirectXSettings.h"
#include "misc/ConstantBuffer.h"
#include "gameobjects/Entity.h"
#include "manager/ContentManager.h"
#include "manager/InputManager.h"
#include "manager/ShapeCreator.h"

#define GetGame (CGame::Get())
#define WDS (*(CGame::Get()->GetWindowSettings()))
#define DXS (*(CGame::Get()->GetDirectXSettings()))
#define CTM (*(CGame::Get()->GetContentManager()))
#define IPM (*(CGame::Get()->GetInputManager()))
#define SHC (*(CGame::Get()->GetShapeCreator()))

#pragma region Defines_for_Texture_initializing_-_not_used_anymore
//#define WRAP (D3D11_TEXTURE_ADDRESS_WRAP)
//#define MIRROR (D3D11_TEXTURE_ADDRESS_MIRROR)
//#define MIRROR_ONCE (D3D11_TEXTURE_ADDRESS_MIRROR_ONCE)
//#define CLAMP (D3D11_TEXTURE_ADDRESS_CLAMP)
//#define BORDER (D3D11_TEXTURE_ADDRESS_BORDER)
//
//#define LINEAR (D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR)
//#define POINT (D3D11_FILTER_MIN_MAG_MIP_POINT)  
#pragma endregion

#define FAILHR(errorcode) if (FAILED(hr)) { return errorcode; }

class CGame
{
public:
	static CGame* Get()
	{
		static CGame* instance = new CGame();	// Diese Zeile wird nur beim ersten Mal ausgeführt
		return instance;						// Diese immer
	}

private:
	SWindowSettings m_windowSettings;
	SDirectXSettings m_directXSettings;
	CContentManager m_contentManager;
	CInputManager m_inputManager;
	CShapeCreator m_shapeCreator;

	SStandardConstantBuffer m_applicationConstantBuffer;
	SStandardConstantBuffer m_frameConstantBuffer;
	bool m_isRunning;

public:
	XMFLOAT3 m_camPos;
	XMFLOAT3 m_camRot;
	XMFLOAT3 m_lightDirection = XMFLOAT3(0.2f, -1.0f, 0.2f);
	XMFLOAT4 m_ambientLight = XMFLOAT4(0.25f, 0.25f, 0.25f, 1);

public:
	/// <summary>
	/// Initializes everything and calls Start
	/// </summary>
	/// <param name="_hInstance"></param>
	/// <returns></returns>
	int Initialize(HINSTANCE _hInstance);
	/// <summary>
	/// Calls Update & Render and calculates the deltaTime
	/// </summary>
	/// <returns></returns>
	int Run();
	/// <summary>
	/// Deinitializes all DirectX related stuff
	/// </summary>
	void Finalize();

#pragma region Get Instances
	inline SWindowSettings* GetWindowSettings() { return &m_windowSettings; }
	inline SDirectXSettings* GetDirectXSettings() { return &m_directXSettings; }
	inline CContentManager* GetContentManager() { return &m_contentManager; }
	inline CInputManager* GetInputManager() { return &m_inputManager; }
	inline CShapeCreator* GetShapeCreator() { return &m_shapeCreator; }
#pragma endregion

	/// <summary>
	/// Switches the rasterizer state between Solid and Wireframe
	/// </summary>
	void SwitchRasterizerState();

	float movementSpeed = 4;
	float rotationSpeed = 4;

private:
	/// <summary>
	/// Opens and initializes a new Windows window
	/// </summary>
	/// <param name="_hInstance"></param>
	/// <returns></returns>
	int InitApplication(HINSTANCE _hInstance);
	/// <summary>
	/// Initializes and creates DirectX components
	/// </summary>
	/// <returns></returns>
	int InitDirectX();
	/// <summary>
	/// Creates Frame, Object and Light constantbuffers and initializes them
	/// </summary>
	/// <returns></returns>
	int InitConstantBuffers();
	/// <summary>
	/// Called after everything has been initialized
	/// </summary>
	/// <returns></returns>
	int Start();
	/// <summary>
	/// Called every frame
	/// </summary>
	/// <param name="_deltaTime"></param>
	void Update(float _deltaTime);
	/// <summary>
	/// Called every frame after Update(), updates Frame constant buffer and renders all entities
	/// </summary>
	void Render();

	void ClearBackBuffer(const float _clearColor[4], float _clearDepth, UINT8 _clearStencil);
};

