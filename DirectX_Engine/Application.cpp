#include "Application.h"


Application::Application(int _height, int _width)
{
	window = std::make_unique<Window>(_height, _width);
	renderer = std::make_unique<Renderer>(window);
	triangle = std::make_unique<Triangle>(renderer);
}


Application::~Application()
{

}



void Application::Run()
{
	// Main Loop

	// Update

	// Draw
	renderer->BeginFrame();
	// Render everything
	triangle->Draw(renderer);

	renderer->EndFrame();
}