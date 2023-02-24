#pragma once
#include "settings/WindowSettings.h"
#include "settings/DirectXSettings.h"
#include "misc/ConstantBuffer.h"
#include "gameobjects/Entity.h"
#include "manager/ContentManager.h"
#include "manager/InputManager.h"
#include "manager/ShapeCreator.h"

#define GetGame (Game::Get())
#define WDS (*(Game::Get()->GetWindowSettings()))
#define DXS (*(Game::Get()->GetDirectXSettings()))
#define CTM (*(Game::Get()->GetContentManager()))
#define IPM (*(Game::Get()->GetInputManager()))
#define SHC (*(Game::Get()->GetShapeCreator()))

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

class Game
{
public:
	static Game* Get()
	{
		static Game* instance = new Game();	// Diese Zeile wird nur beim ersten Mal ausgeführt
		return instance;						// Diese immer
	}
	
	// Variables
public:
	XMFLOAT3 CamPos;
	XMFLOAT3 CamRot;
	XMFLOAT3 LightDirection = XMFLOAT3(0.2f, -1.0f, 0.2f);
	XMFLOAT4 AmbientLight = XMFLOAT4(0.25f, 0.25f, 0.25f, 1);
private:
	WindowSettings windowSettings;
	DirectXSettings directXSettings;
	ContentManager contentManager;
	InputManager inputManager;
	ShapeCreator shapeCreator;

	StandardConstantBuffer applicationConstantBuffer;
	StandardConstantBuffer frameConstantBuffer;
	bool isRunning;

	float movementSpeed = 4;
	float rotationSpeed = 4;

	// Methods
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
	/// <summary>
	/// Switches the rasterizer state between Solid and Wireframe
	/// </summary>
	void SwitchRasterizerState();

#pragma region Get Instances
	inline WindowSettings* GetWindowSettings() { return &windowSettings; }
	inline DirectXSettings* GetDirectXSettings() { return &directXSettings; }
	inline ContentManager* GetContentManager() { return &contentManager; }
	inline InputManager* GetInputManager() { return &inputManager; }
	inline ShapeCreator* GetShapeCreator() { return &shapeCreator; }
#pragma endregion

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

