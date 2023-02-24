#include "../header-files/misc/GraphicsPCH.h"
#include "../header-files/Game.h"
#include "../header-files/gameobjects/components/Mesh.h"
#include "../header-files/gameobjects/components/Component.h"
#include "../header-files/misc/MathHelper.h"
#include "../header-files/gameobjects/materials/Material.h"
#include "../header-files/gameobjects/materials/Texture.h"

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam);

int Game::Initialize(HINSTANCE _hInstance)
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

	// Initialize directx input
	returnValue = inputManager.InitDirectInput(_hInstance);
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Could not create Direct Input", L"Error", MB_OK);
		return returnValue;
	}

	Start();

	isRunning = true;

	return 0;
}

int Game::Run()
{
	MSG msg = { 0 };

	// Calculate deltatime
	static DWORD prevTime = timeGetTime();
	static const float targetFrameRate = 30.0f;
	static const float maxTimeStep = 1.0f / targetFrameRate;
	static DWORD currentTime;
	float deltaTime;

	// Update loop while application is running
	while (isRunning && msg.message != WM_QUIT)
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

void Game::Finalize()
{
	SafeRelease(DXS.DxDevice);
	SafeRelease(DXS.DxContext);
	SafeRelease(DXS.SwapChain);
	SafeRelease(DXS.RenderTargetView);
	SafeRelease(DXS.DepthStencilBuffer);
	SafeRelease(DXS.DepthStencilView);
	SafeRelease(DXS.DepthStencilState);
	SafeRelease(DXS.CurrentRasterrizerState);

	IPM.DeInit();
}

void Game::SwitchRasterizerState()
{
	if (directXSettings.CurrentRasterrizerState == directXSettings.RasterrizerStateSolid)
		directXSettings.CurrentRasterrizerState = directXSettings.RasterrizerStateWireframe;
	else
		directXSettings.CurrentRasterrizerState = directXSettings.RasterrizerStateSolid;
}

int Game::InitApplication(HINSTANCE _hInstance)
{
	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = _hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
	wndClass.lpszClassName = windowSettings.WindowClassName;

	if (!RegisterClassEx(&wndClass))
	{
		return -2;
	}

	RECT windowRect = { 0,0, windowSettings.WindowWidth, windowSettings.WindowHeight };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	windowSettings.WindowHandle = CreateWindowA(windowSettings.WindowClassNameShort,
		windowSettings.WindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		_hInstance,
		nullptr);

	if (!windowSettings.WindowHandle)
	{
		return -3;
	}

	ShowWindow(windowSettings.WindowHandle, 10);
	UpdateWindow(windowSettings.WindowHandle);

	return 0;
}

int Game::InitDirectX()
{
#pragma region Create_Device_and_Swapchain
	RECT clientRect;
	GetClientRect(windowSettings.WindowHandle, &clientRect);

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
	swapChainDesc.OutputWindow = windowSettings.WindowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;

	unsigned int createDeviceFlags = 0;

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
		&directXSettings.SwapChain,
		&directXSettings.DxDevice,
		&featureLevel,
		&directXSettings.DxContext);

	if (FAILED(hr))
	{
		return -10;
	}
#pragma endregion


	// Create Backbuffer
	ID3D11Texture2D* backbuffer = {};
	hr = directXSettings.SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
	if (FAILED(hr))
	{
		return -11;
	}

	// Create Rendertargetview
	hr = directXSettings.DxDevice->CreateRenderTargetView(backbuffer, nullptr, &directXSettings.RenderTargetView);
	if (FAILED(hr))
	{
		return -12;
	}

	SafeRelease(backbuffer);

#pragma region Depth_stencil
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

	hr = directXSettings.DxDevice->CreateTexture2D(&depthStencilBufferDesc,
		nullptr,
		&directXSettings.DepthStencilBuffer);

	if (FAILED(hr))
	{
		return -13;
	}

	hr = directXSettings.DxDevice->CreateDepthStencilView(directXSettings.DepthStencilBuffer,
		nullptr,
		&directXSettings.DepthStencilView);

	if (FAILED(hr))
	{
		return -14;
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;		// Nahe Objekte nehmen, ferne wegwerfen
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	hr = directXSettings.DxDevice->CreateDepthStencilState(&depthStencilDesc, &directXSettings.DepthStencilState);
	if (FAILED(hr))
	{
		return -15;
	}
#pragma endregion

#pragma region Rasterizer
	D3D11_RASTERIZER_DESC rasterdesc;
	ZeroMemory(&rasterdesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterdesc.AntialiasedLineEnable = false;
	rasterdesc.FillMode = D3D11_FILL_SOLID;
	rasterdesc.CullMode = D3D11_CULL_NONE;
	rasterdesc.DepthBias = 0;
	rasterdesc.DepthBiasClamp = 0.0f;
	rasterdesc.DepthClipEnable = true;
	rasterdesc.FrontCounterClockwise = false;
	rasterdesc.MultisampleEnable = false;
	rasterdesc.ScissorEnable = false;
	rasterdesc.SlopeScaledDepthBias = 0.0f;

	hr = directXSettings.DxDevice->CreateRasterizerState(&rasterdesc, &directXSettings.RasterrizerStateSolid);
	if (FAILED(hr))
	{
		return -16;
	}

	rasterdesc.FillMode = D3D11_FILL_WIREFRAME;
	hr = directXSettings.DxDevice->CreateRasterizerState(&rasterdesc, &directXSettings.RasterrizerStateWireframe);
	if (FAILED(hr))
	{
		return -17;
	}

	directXSettings.CurrentRasterrizerState = directXSettings.RasterrizerStateSolid;

	directXSettings.ViewPort.Width = clientWidth;
	directXSettings.ViewPort.Height = clientHeight;
	directXSettings.ViewPort.TopLeftX = 0.0f;
	directXSettings.ViewPort.TopLeftY = 0.0f;
	directXSettings.ViewPort.MinDepth = 0.0f;
	directXSettings.ViewPort.MaxDepth = 1.0f;
#pragma endregion

	return 0;
}

int Game::InitConstantBuffers()
{
	D3D11_BUFFER_DESC constantBuffer = { 0 };
	constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBuffer.ByteWidth = sizeof(StandardConstantBuffer);
	constantBuffer.Usage = D3D11_USAGE_DEFAULT;

	// Create Application constant buffer
	HRESULT hr = directXSettings.DxDevice->CreateBuffer(&constantBuffer, nullptr, &directXSettings.ConstantBuffers[CB_APPLICATION]);
	FAILHR(-40);
	// Create Frame constant buffer
	hr = directXSettings.DxDevice->CreateBuffer(&constantBuffer, nullptr, &directXSettings.ConstantBuffers[CB_FRAME]);
	FAILHR(-41);
	// Create Object constant buffer
	hr = directXSettings.DxDevice->CreateBuffer(&constantBuffer, nullptr, &directXSettings.ConstantBuffers[CB_OBJECT]);
	FAILHR(-42);
	// Create Light constant buffer
	constantBuffer.ByteWidth = sizeof(LightConstantBuffer);
	hr = directXSettings.DxDevice->CreateBuffer(&constantBuffer, nullptr, &directXSettings.ConstantBuffers[CB_LIGHT]);
	FAILHR(-43);

	RECT clientRect;
	GetClientRect(windowSettings.WindowHandle, &clientRect);
	float clientHeight = clientRect.bottom - clientRect.top;
	float clientWidth = clientRect.right - clientRect.left;

	// Set Camera FOV and application buffer
	applicationConstantBuffer.Matrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(60), clientWidth / clientHeight, 0.1f, 100.0f);
	directXSettings.DxContext->UpdateSubresource(directXSettings.ConstantBuffers[CB_APPLICATION], 0, nullptr, &applicationConstantBuffer, 0, 0);

	return 0;
}

void Game::ClearBackBuffer(const float _clearColor[4], float _clearDepth, UINT8 _clearStencil)
{
	directXSettings.DxContext->ClearRenderTargetView(directXSettings.RenderTargetView, _clearColor);
	directXSettings.DxContext->ClearDepthStencilView(directXSettings.DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, _clearDepth, _clearStencil);
}

void Game::Render()
{
	// Hardware Check
	assert(directXSettings.DxDevice);
	assert(directXSettings.DxContext);

	// Backbuffer clear
	ClearBackBuffer(Colors::Navy, 1.0f, 0);

#pragma region Update Frame ConstantBuffer
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(CamRot.x),
		XMConvertToRadians(CamRot.y),
		XMConvertToRadians(CamRot.z));

	XMMATRIX position = XMMatrixTranslation(CamPos.x, CamPos.y, CamPos.z);

	frameConstantBuffer.Matrix = XMMatrixInverse(nullptr, XMMatrixMultiply(rotation, position));

	directXSettings.DxContext->UpdateSubresource(directXSettings.ConstantBuffers[CB_FRAME], 0, nullptr, &frameConstantBuffer, 0, 0);
#pragma endregion

	contentManager.Render();

	directXSettings.SwapChain->Present(1, 0);
}

int Game::Start()
{
	CamPos = XMFLOAT3(0, 1.5f, -5);

	CTM.CreateSkyBox();

#pragma region Grass_Cube_Normalmap
	Entity* CubeObject = new Entity(XMFLOAT3(0, 0, 0));
	SHC.CreateCube(CubeObject->AddComponent<Mesh>());
	CubeObject->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new Texture(L"..\\assets\\Grass.jpg", Albedo), new Texture(L"..\\assets\\GrassNormal.jpg", Normalmap)));

	CTM.AddEntity(CubeObject);			// !IMPORTANT! Add Entity to Content Manager
#pragma endregion

#pragma region Oktaeder
	Entity* OktaederObject = new Entity(XMFLOAT3(-1, 0, 0));
	SHC.CreateOktaeder(OktaederObject->AddComponent<Mesh>(), XMFLOAT4(0.79f, 0.57f, 0.66f, 1.0f));
	OktaederObject->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"SimplePixelShader.cso", L"SimpleVertexShader.cso", new Texture(L"..\\assets\\DefaultTexture.png", Albedo), nullptr));

	CTM.AddEntity(OktaederObject);		// !IMPORTANT! Add Entity to Content Manager
#pragma endregion

#pragma region Textured_Plane
	Entity* TexturedPlane = new Entity(XMFLOAT3(1, 0, 0));
	SHC.CreatePlane(TexturedPlane->AddComponent<Mesh>());
	TexturedPlane->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new Texture(L"..\\assets\\Leather.jpg", Albedo), new Texture(L"..\\assets\\LeatherNormal.jpg", Normalmap)));

	CTM.AddEntity(TexturedPlane);		// !IMPORTANT! Add Entity to Content Manager  

	TexturedPlane->p_transform->Rotation = XMFLOAT3(-45, 0, 0);
#pragma endregion

#pragma region Glossy_Sphere
	Entity* SphereObject = new Entity(XMFLOAT3(-1, 1, 0));
	SHC.CreateSphere(SphereObject->AddComponent<Mesh>(), 40, 40, XMFLOAT4(1, 0, 0, 1));
	SphereObject->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new Texture(L"..\\assets\\DefaultTexture.png", Albedo), nullptr));

	CTM.AddEntity(SphereObject);		// !IMPORTANT! Add Entity to Content Manager
	SphereObject->GetComponent<Mesh>()->p_Material->Smoothness = 1;
#pragma endregion

#pragma region Matte_Sphere
	Entity* MatteSphereObject = new Entity(XMFLOAT3(0, 1, 0));
	SHC.CreateSphere(MatteSphereObject->AddComponent<Mesh>(), 40, 40, XMFLOAT4(1, 0, 0, 1));
	MatteSphereObject->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new Texture(L"..\\assets\\DefaultTexture.png", Albedo), nullptr));

	CTM.AddEntity(MatteSphereObject);		// !IMPORTANT! Add Entity to Content Manager
	MatteSphereObject->GetComponent<Mesh>()->p_Material->Smoothness = 0;
#pragma endregion

#pragma region Stone_Textured_Sphere
	Entity* NoNormalMapSphere = new Entity(XMFLOAT3(-1, 2, 0));
	SHC.CreateSphere(NoNormalMapSphere->AddComponent<Mesh>(), 40, 40);
	NoNormalMapSphere->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new Texture(L"..\\assets\\Stones.jpg", Albedo), nullptr));

	CTM.AddEntity(NoNormalMapSphere);		// !IMPORTANT! Add Entity to Content Manager  
#pragma endregion

#pragma region Stone_Normalmap_Shere
	Entity* NormalMapSphere = new Entity(XMFLOAT3(0, 2, 0));
	SHC.CreateSphere(NormalMapSphere->AddComponent<Mesh>(), 40, 40);
	NormalMapSphere->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new Texture(L"..\\assets\\Stones.jpg", Albedo), new Texture(L"..\\assets\\StonesNormal.jpg", Normalmap)));

	CTM.AddEntity(NormalMapSphere);		// !IMPORTANT! Add Entity to Content Manager  
#pragma endregion

#pragma region Sand_Normalmap_Sphere
	Entity* SandNormalmapSphere = new Entity(XMFLOAT3(0, 3, 0));
	SHC.CreateSphere(SandNormalmapSphere->AddComponent<Mesh>(), 40, 40);
	SandNormalmapSphere->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"NormalmapPixelShader.cso", L"NormalmapVertexShader.cso", new Texture(L"..\\assets\\Sand.jpg", Albedo), new Texture(L"..\\assets\\SandNormal.jpg", Normalmap)));

	CTM.AddEntity(SandNormalmapSphere);		// !IMPORTANT! Add Entity to Content Manager  
#pragma endregion

#pragma region Sand_Textured_Sphere
	Entity* SandSphere = new Entity(XMFLOAT3(-1, 3, 0));
	SHC.CreateSphere(SandSphere->AddComponent<Mesh>(), 40, 40);
	SandSphere->GetComponent<Mesh>()->SetMaterial(new Material(DXS.DxDevice, DXS.DxContext,
		L"TexturedPixelShader.cso", L"TexturedVertexShader.cso", new Texture(L"..\\assets\\Sand.jpg", Albedo), nullptr));

	CTM.AddEntity(SandSphere);		// !IMPORTANT! Add Entity to Content Manager  
#pragma endregion

	CTM.Start();

	return 0;
}

void Game::Update(float _deltaTime)
{
	// Check for input
	inputManager.DetectInput();

	// Shutdown application
	if (inputManager.GetKeyDown(DIK_ESCAPE))
		isRunning = false;

#pragma region Camera_Movement

	movementSpeed = Clamp(movementSpeed + inputManager.GetMouseWheel() * 0.005, 1, 10);

	XMVECTOR f = { 0, 0, 1, 0 };
	XMVECTOR r = { 1, 0, 0, 0 };
	XMVECTOR u = { 0, 1, 1, 0 };

	XMMATRIX m = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(CamRot.x),
		XMConvertToRadians(CamRot.y),
		XMConvertToRadians(CamRot.z));

	f = XMVector3Transform(f, m);
	r = XMVector3Transform(r, m);
	u = XMVector3Transform(u, m);

	XMFLOAT3 forward = XMFLOAT3(f.m128_f32[0], f.m128_f32[1], f.m128_f32[2]);
	XMFLOAT3 right = XMFLOAT3(r.m128_f32[0], r.m128_f32[1], r.m128_f32[2]);
	XMFLOAT3 up = XMFLOAT3(u.m128_f32[0], u.m128_f32[1], u.m128_f32[2]);

	XMFLOAT3 camMovement = XMFLOAT3(0, 0, 0);

	if (inputManager.GetKey(DIK_W))
		camMovement = camMovement + forward;
	if (inputManager.GetKey(DIK_S))
		camMovement = camMovement - forward;
	if (inputManager.GetKey(DIK_A))
		camMovement = camMovement - right;
	if (inputManager.GetKey(DIK_D))
		camMovement = camMovement + right;
	if (inputManager.GetKey(DIK_LCONTROL))
		camMovement.y -= 1;
	if (inputManager.GetKey(DIK_SPACE))
		camMovement.y += 1;

	CamPos = CamPos + camMovement * _deltaTime * movementSpeed;

	if (inputManager.GetMouseKey(1))
	{
		XMFLOAT2 mouseDelta = inputManager.GetMouseMovement();
		CamRot.x += mouseDelta.y * _deltaTime * rotationSpeed;
		CamRot.y += mouseDelta.x * _deltaTime * rotationSpeed;
	}
#pragma endregion

#pragma region Experimental_Testing
	// Change rasterizerstate
	if (inputManager.GetKeyDown(DIK_1))
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
	contentManager.Update(_deltaTime);
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
