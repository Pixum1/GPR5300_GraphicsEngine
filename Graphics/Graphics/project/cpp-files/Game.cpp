#include "../header-files/misc/GraphicsPCH.h"
#include "../header-files/Game.h"
#include "../header-files/gameobjects/components/Mesh.h"
#include "../header-files/gameobjects/components/Component.h"
#include "../header-files/misc/MathHelper.h"
#include "../header-files/gameobjects/materials/Material.h"
#include "../header-files/gameobjects/materials/Texture.h"
#include "../header-files/gameobjects/materials/Cubemap.h"

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam);

CGame::CGame()
{
}

CGame::~CGame()
{
}

int CGame::Initialize(HINSTANCE _hInstance)
{
	if (!XMVerifyCPUSupport())
	{
		MessageBox(nullptr, L"Failed to load DirectXMathLibrary", L"Error", MB_OK);
		return -1;
	}

	// Windows Fenster erstellen
	int returnValue = InitApplication(_hInstance);
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Failed to create Window", L"Error", MB_OK);
		return returnValue;
	}

	// DirectX initialisieren
	returnValue = InitDirectX();
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Failed to initialize DirectX", L"Error", MB_OK);
		return returnValue;
	}

	// DirectX initialisieren
	returnValue = InitConstantBuffers();
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Failed to initialize Constant Buffers", L"Error", MB_OK);
		return returnValue;
	}

	CTM.Init();

	// Create all materials
	/*p_simpleMaterial = new CMaterial(L"SimplePixelShader.cso", L"SimpleVertexShader.cso");
	p_worldMapMaterial = new CMaterial(L"TexturedPixelShader.cso", L"TexturedVertexShader.cso");
	p_happyMaterial = new CMaterial(L"TexturedPixelShader.cso", L"TexturedVertexShader.cso");
	p_skyboxMaterial = new CMaterial(L"SkyboxPixelShader.cso", L"SkyboxVertexShader.cso");

	p_simpleMaterial->Init(m_directXSettings.m_device, m_directXSettings.m_deviceContext);
	p_worldMapMaterial->Init(m_directXSettings.m_device, m_directXSettings.m_deviceContext, L"..\\Assets\\WorldMap.jpeg");
	p_happyMaterial->Init(m_directXSettings.m_device, m_directXSettings.m_deviceContext, L"..\\Assets\\test.png");
	p_skyboxMaterial->Init(m_directXSettings.m_device, m_directXSettings.m_deviceContext, L"..\\Assets\\Skybox.dds", true);*/

	returnValue = m_inputManager.InitDirectInput(_hInstance);
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Could not create Direct Input", L"Error", MB_OK);
		return returnValue;
	}

	LoadLevel();

	m_isRunning = true;

	return 0;
}

int CGame::Run()
{
	MSG msg = { 0 };

	static DWORD prevTime = timeGetTime();
	static const float targetFrameRate = 30.0f;
	static const float maxTimeStep = 1.0f / targetFrameRate;
	static DWORD currentTime;
	float deltaTime;

	while (m_isRunning && msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			currentTime = timeGetTime();
			deltaTime = (currentTime - prevTime) * 0.001f;		// Angabe in Sekunden

			deltaTime = std::min<float>(deltaTime, maxTimeStep);
			prevTime = currentTime;

			Update(deltaTime);
			Render();
		}
	}

	return 0;
}

void CGame::Finalize()
{
}

void CGame::SwitchRasterizerState()
{
	if (m_directXSettings.m_currentRasterrizerState == m_directXSettings.m_rasterrizerStateSolid)
		m_directXSettings.m_currentRasterrizerState = m_directXSettings.m_rasterrizerStateWireframe;
	else
		m_directXSettings.m_currentRasterrizerState = m_directXSettings.m_rasterrizerStateSolid;
}

int CGame::InitApplication(HINSTANCE _hInstance)
{
	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = _hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
	wndClass.lpszClassName = m_windowSettings.m_WindowClassName;

	if (!RegisterClassEx(&wndClass))
	{
		return -2;
	}

	RECT windowRect = { 0,0, m_windowSettings.m_WindowWidth, m_windowSettings.m_WindowHeight };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	m_windowSettings.m_WindowHandle = CreateWindowA(m_windowSettings.m_WindowClassNameShort,
		m_windowSettings.m_WindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		_hInstance,
		nullptr);

	if (!m_windowSettings.m_WindowHandle)
	{
		return -3;
	}

	ShowWindow(m_windowSettings.m_WindowHandle, 10);
	UpdateWindow(m_windowSettings.m_WindowHandle);

	return 0;
}

int CGame::InitDirectX()
{
	RECT clientRect;
	GetClientRect(m_windowSettings.m_WindowHandle, &clientRect);

	unsigned long clientWidth = clientRect.right - clientRect.left;
	unsigned long clientHeight = clientRect.bottom - clientRect.top;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = clientWidth;
	swapChainDesc.BufferDesc.Height = clientHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_windowSettings.m_WindowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;

	unsigned int createDeviceFlags = 0;

#if _DEBUG
	createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_directXSettings.m_swapChain,
		&m_directXSettings.m_device,
		&featureLevel,
		&m_directXSettings.m_deviceContext);

	if (FAILED(hr))
	{
		return -10;
	}

	ID3D11Texture2D* backbuffer;
	hr = m_directXSettings.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
	if (FAILED(hr))
	{
		return -11;
	}

	hr = m_directXSettings.m_device->CreateRenderTargetView(backbuffer, nullptr, &m_directXSettings.m_renderTargetView);
	if (FAILED(hr))
	{
		return -12;
	}

	SafeRelease(backbuffer);

	D3D11_TEXTURE2D_DESC depthStencilBufferDesc = { 0 };
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;		// 24 bit Tiefe, 8 bit Stencil
	depthStencilBufferDesc.Height = clientHeight;
	depthStencilBufferDesc.Width = clientWidth;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	hr = m_directXSettings.m_device->CreateTexture2D(&depthStencilBufferDesc,
		nullptr,
		&m_directXSettings.m_depthStencilBuffer);

	if (FAILED(hr))
	{
		return -13;
	}

	hr = m_directXSettings.m_device->CreateDepthStencilView(m_directXSettings.m_depthStencilBuffer,
		nullptr,
		&m_directXSettings.m_depthStencilView);

	if (FAILED(hr))
	{
		return -14;
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;		// Nahe Objekte nehmen, ferne wegwerfen
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	hr = m_directXSettings.m_device->CreateDepthStencilState(&depthStencilDesc, &m_directXSettings.m_depthStencilState);
	if (FAILED(hr))
	{
		return -15;
	}

	// Rasterizer Macht Vektor zu Pixel
	D3D11_RASTERIZER_DESC rasterdesc;
	ZeroMemory(&rasterdesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterdesc.AntialiasedLineEnable = false;
	rasterdesc.FillMode = D3D11_FILL_SOLID;		// Komplette Dreiecke zeigen, rumspielen!
	rasterdesc.CullMode = D3D11_CULL_NONE;		// Rückseiten wegschneiden
	rasterdesc.DepthBias = 0;
	rasterdesc.DepthBiasClamp = 0.0f;
	rasterdesc.DepthClipEnable = true;
	rasterdesc.FrontCounterClockwise = false;		// Dreiecke im Uhrzeigersinn zeigen nach vorne
	rasterdesc.MultisampleEnable = false;
	rasterdesc.ScissorEnable = false;
	rasterdesc.SlopeScaledDepthBias = 0.0f;

	hr = m_directXSettings.m_device->CreateRasterizerState(&rasterdesc, &m_directXSettings.m_rasterrizerStateSolid);
	if (FAILED(hr))
	{
		return -16;
	}

	rasterdesc.FillMode = D3D11_FILL_WIREFRAME;
	hr = m_directXSettings.m_device->CreateRasterizerState(&rasterdesc, &m_directXSettings.m_rasterrizerStateWireframe);
	if (FAILED(hr))
	{
		return -17;
	}

	m_directXSettings.m_currentRasterrizerState = m_directXSettings.m_rasterrizerStateSolid;

	m_directXSettings.m_viewPort.Width = clientWidth;
	m_directXSettings.m_viewPort.Height = clientHeight;
	m_directXSettings.m_viewPort.TopLeftX = 0.0f;
	m_directXSettings.m_viewPort.TopLeftY = 0.0f;
	m_directXSettings.m_viewPort.MinDepth = 0.0f;
	m_directXSettings.m_viewPort.MaxDepth = 1.0f;

	return 0;
}

int CGame::InitConstantBuffers()
{
	D3D11_BUFFER_DESC constantBuffer = { 0 };
	constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBuffer.ByteWidth = sizeof(SStandardConstantBuffer);
	constantBuffer.Usage = D3D11_USAGE_DEFAULT;

	HRESULT hr = m_directXSettings.m_device->CreateBuffer(&constantBuffer, nullptr, &m_directXSettings.m_constantBuffers[CB_APPLICATION]);
	FAILHR(-40);
	hr = m_directXSettings.m_device->CreateBuffer(&constantBuffer, nullptr, &m_directXSettings.m_constantBuffers[CB_FRAME]);
	FAILHR(-41);
	hr = m_directXSettings.m_device->CreateBuffer(&constantBuffer, nullptr, &m_directXSettings.m_constantBuffers[CB_OBJECT]);
	FAILHR(-42);

	constantBuffer.ByteWidth = sizeof(SLightConstantBuffer);
	hr = m_directXSettings.m_device->CreateBuffer(&constantBuffer, nullptr, &m_directXSettings.m_constantBuffers[CB_LIGHT]);
	FAILHR(-43);

	RECT clientRect;
	GetClientRect(m_windowSettings.m_WindowHandle, &clientRect);
	float clientHeight = clientRect.bottom - clientRect.top;
	float clientWidth = clientRect.right - clientRect.left;


	m_applicationConstantBuffer.m_matrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(60), clientWidth / clientHeight, 0.1f, 100.0f);

	m_directXSettings.m_deviceContext->UpdateSubresource(m_directXSettings.m_constantBuffers[CB_APPLICATION], 0, nullptr, &m_applicationConstantBuffer, 0, 0);

	m_camPos = XMFLOAT3(0, 0, -5);

	//m_lightDirection = XMFLOAT3(0.2f, -1.0f, 0.2f);

	return 0;
}

void CGame::ClearBackBuffer(const float _clearColor[4], float _clearDepth, UINT8 _clearStencil)
{
	m_directXSettings.m_deviceContext->ClearRenderTargetView(m_directXSettings.m_renderTargetView, _clearColor);
	m_directXSettings.m_deviceContext->ClearDepthStencilView(m_directXSettings.m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, _clearDepth, _clearStencil);
}

void CGame::Render()
{
	// Hardware Check
	assert(m_directXSettings.m_device);
	assert(m_directXSettings.m_deviceContext);

	// Backbuffer clear
	ClearBackBuffer(Colors::Navy, 1.0f, 0);

#pragma region Update Frame ConstantBuffer
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(m_camRot.x),
		XMConvertToRadians(m_camRot.y),
		XMConvertToRadians(m_camRot.z));

	XMMATRIX position = XMMatrixTranslation(m_camPos.x, m_camPos.y, m_camPos.z);

	m_frameConstantBuffer.m_matrix = XMMatrixInverse(nullptr, XMMatrixMultiply(rotation, position));

	m_directXSettings.m_deviceContext->UpdateSubresource(m_directXSettings.m_constantBuffers[CB_FRAME], 0, nullptr, &m_frameConstantBuffer, 0, 0);
#pragma endregion


	m_contentManager.Render();

	m_directXSettings.m_swapChain->Present(1, 0);
}

int CGame::LoadLevel()
{
	// Skybox
	p_skybox = new CEntity(XMFLOAT3(0, 0, 0));
	SHC.CreateSphere(p_skybox->AddComponent<CMesh>(), 40, 40);
	p_skybox->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"SkyboxPixelShader.cso", L"SkyboxVertexShader.cso", new CCubemap(L"..\\Assets\\Skybox.dds", Albedo), nullptr));

	CTM.AddEntity(p_skybox);

	// Cube
	CEntity* CubeObject = new CEntity(XMFLOAT3(0, 0, 0));
	SHC.CreateCube(CubeObject->AddComponent<CMesh>());
	CubeObject->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new CTexture(L"..\\assets\\Grass.jpg", Albedo), new CTexture(L"..\\assets\\GrassNormal.jpg", Normalmap)));

	CTM.AddEntity(CubeObject);			// !IMPORTANT! Add Entity to Content Manager

	// Oktaeder
	CEntity* OktaederObject = new CEntity(XMFLOAT3(-2, 0, 0));
	SHC.CreateOktaeder(OktaederObject->AddComponent<CMesh>(), XMFLOAT4(0.79f, 0.57f, 0.66f, 1.0f));
	OktaederObject->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"SimplePixelShader.cso", L"SimpleVertexShader.cso", new CTexture(L"..\\assets\\DefaultTexture.png", Albedo), nullptr));

	CTM.AddEntity(OktaederObject);		// !IMPORTANT! Add Entity to Content Manager

	// Sphere
	CEntity* SphereObject = new CEntity(XMFLOAT3(2, 0, 0));
	SHC.CreateSphere(SphereObject->AddComponent<CMesh>(), 40, 40, XMFLOAT4(1, 0, 0, 1));
	SphereObject->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new CTexture(L"..\\assets\\DefaultTexture.png", Albedo), nullptr));

	CTM.AddEntity(SphereObject);		// !IMPORTANT! Add Entity to Content Manager
	SphereObject->GetComponent<CMesh>()->p_material->smoothness = 1;

	// Sphere
	CEntity* MatteSphereObject = new CEntity(XMFLOAT3(4, 0, 0));
	SHC.CreateSphere(MatteSphereObject->AddComponent<CMesh>(), 40, 40, XMFLOAT4(1, 0, 0, 1));
	MatteSphereObject->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new CTexture(L"..\\assets\\DefaultTexture.png", Albedo), nullptr));

	CTM.AddEntity(MatteSphereObject);		// !IMPORTANT! Add Entity to Content Manager
	MatteSphereObject->GetComponent<CMesh>()->p_material->smoothness = 0;

	// Sphere - Normalmap
	CEntity* NormalMapSphere = new CEntity(XMFLOAT3(0, 2, 0));
	SHC.CreateSphere(NormalMapSphere->AddComponent<CMesh>(), 40, 40);
	NormalMapSphere->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new CTexture(L"..\\assets\\Stones.jpg", Albedo), new CTexture(L"..\\assets\\StonesNormal.jpg", Normalmap)));

	CTM.AddEntity(NormalMapSphere);		// !IMPORTANT! Add Entity to Content Manager

	// Sphere - Normalmap
	CEntity* NoNormalMapSphere = new CEntity(XMFLOAT3(-1, 2, 0));
	SHC.CreateSphere(NoNormalMapSphere->AddComponent<CMesh>(), 40, 40);
	NoNormalMapSphere->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new CTexture(L"..\\assets\\Stones.jpg", Albedo), nullptr));

	CTM.AddEntity(NoNormalMapSphere);		// !IMPORTANT! Add Entity to Content Manager

	// Sphere - Normalmap
	CEntity* WoodNormalMapSphere = new CEntity(XMFLOAT3(2, 2, 0));
	SHC.CreateSphere(WoodNormalMapSphere->AddComponent<CMesh>(), 40, 40);
	WoodNormalMapSphere->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new CTexture(L"..\\assets\\Wood.jpg", Albedo), new CTexture(L"..\\assets\\WoodNormal.jpg", Normalmap)));

	CTM.AddEntity(WoodNormalMapSphere);		// !IMPORTANT! Add Entity to Content Manager

	// Plane
	CEntity* TexturedPlane = new CEntity(XMFLOAT3(0, -2, 0));
	SHC.CreatePlane(TexturedPlane->AddComponent<CMesh>());
	TexturedPlane->GetComponent<CMesh>()->SetMaterial(new CMaterial(DXS.m_device, DXS.m_deviceContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new CTexture(L"..\\assets\\test.png", Albedo), nullptr));

	CTM.AddEntity(TexturedPlane);		// !IMPORTANT! Add Entity to Content Manager



	return 0;
}

void CGame::Update(float _deltaTime)
{
	// Check for input
	m_inputManager.DetectInput();

	// Shutdown application
	if (m_inputManager.GetKeyDown(DIK_ESCAPE))
		m_isRunning = false;

#pragma region Camera_Movement

	movementSpeed = Clamp(movementSpeed + m_inputManager.GetMouseWheel() * 0.005, 1, 10);

	XMVECTOR f = { 0, 0, 1, 0 };
	XMVECTOR r = { 1, 0, 0, 0 };
	XMVECTOR u = { 0, 1, 1, 0 };

	XMMATRIX m = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(m_camRot.x),
		XMConvertToRadians(m_camRot.y),
		XMConvertToRadians(m_camRot.z));

	f = XMVector3Transform(f, m);
	r = XMVector3Transform(r, m);
	u = XMVector3Transform(u, m);

	XMFLOAT3 forward = XMFLOAT3(f.m128_f32[0], f.m128_f32[1], f.m128_f32[2]);
	XMFLOAT3 right = XMFLOAT3(r.m128_f32[0], r.m128_f32[1], r.m128_f32[2]);
	XMFLOAT3 up = XMFLOAT3(u.m128_f32[0], u.m128_f32[1], u.m128_f32[2]);

	XMFLOAT3 camMovement = XMFLOAT3(0, 0, 0);

	if (m_inputManager.GetKey(DIK_W))
		camMovement = camMovement + forward;
	if (m_inputManager.GetKey(DIK_S))
		camMovement = camMovement - forward;
	if (m_inputManager.GetKey(DIK_A))
		camMovement = camMovement - right;
	if (m_inputManager.GetKey(DIK_D))
		camMovement = camMovement + right;
	if (m_inputManager.GetKey(DIK_LCONTROL))
		camMovement.y -= 1;
	if (m_inputManager.GetKey(DIK_SPACE))
		camMovement.y += 1;

	m_camPos = m_camPos + camMovement * _deltaTime * movementSpeed;

	if (m_inputManager.GetMouseKey(1))
	{
		XMFLOAT2 mouseDelta = m_inputManager.GetMouseMovement();
		m_camRot.x += mouseDelta.y * _deltaTime * rotationSpeed;
		m_camRot.y += mouseDelta.x * _deltaTime * rotationSpeed;
	}
#pragma endregion

#pragma region Experimental_Testing
	// Change rasterizerstate
	if (m_inputManager.GetKeyDown(DIK_1))
		SwitchRasterizerState();

	// Rotate all objects
	if (IPM.GetKey(DIK_2))
		CTM.Rotate = true;
	else if (IPM.GetKeyUp(DIK_2))
		CTM.Rotate = false;

	//Move all objects up and down
	if (IPM.GetKey(DIK_3))
		CTM.Move = true;
	else if (IPM.GetKeyUp(DIK_3))
		CTM.Move = false;

	// Resize all objects
	if (IPM.GetKey(DIK_4))
		CTM.Resize = true;
	else if (IPM.GetKeyUp(DIK_4))
		CTM.Resize = false;


#pragma endregion

	// Update entities
	m_contentManager.Update(_deltaTime);

	p_skybox->p_transform->TranslationMatrix = XMMatrixTranslation(XMVectorGetX(XMLoadFloat3(&m_camPos)), XMVectorGetY(XMLoadFloat3(&m_camPos)), XMVectorGetZ(XMLoadFloat3(&m_camPos)));
	p_skybox->p_transform->WorldMatrix = p_skybox->p_transform->LocalScaleMatrix * p_skybox->p_transform->RotationMatrix * p_skybox->p_transform->TranslationMatrix;
}

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (_message)
	{
	case WM_PAINT:
		hdc = BeginPaint(_hwnd, &ps);
		EndPaint(_hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hwnd, _message, _wparam, _lparam);
	}
	return 0;
}
