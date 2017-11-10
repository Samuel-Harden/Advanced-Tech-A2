#include <Windows.h>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Application.h"


int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount)
{
	Application app(800, 600);

	MSG msg = { 0 };

	while (true)
	{
		// Handles exiting the Program
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) 
				break;
		}

		app.Run();
	}

	return 0;
}