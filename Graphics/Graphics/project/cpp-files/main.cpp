#include "../header-files/misc/GraphicsPCH.h"
#include "../header-files/Game.h"

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _prevHInstance, LPWSTR _cmdLineArgV, int _cmdLineArgC)
{
	UNREFERENCED_PARAMETER(_prevHInstance);
	UNREFERENCED_PARAMETER(_cmdLineArgV);
	UNREFERENCED_PARAMETER(_cmdLineArgC);

	int value = GetGame->Initialize(_hInstance);
	if (FAILED(value))
	{
		return value;
	}
	value = GetGame->Run();

	GetGame->Finalize();

	return value;
}