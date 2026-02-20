#include "Debugger.h"
#include "DXRenderer.h"
#include "DXWindow.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	DXWindow _dxWind{ 800, 600, hInstance, nCmdShow };
	DXRenderer _dxRend{ _dxWind };

	MSG msg;

	Debugging::OpenConsole();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else 
		{
			

		}
	}

	return 0;
}
