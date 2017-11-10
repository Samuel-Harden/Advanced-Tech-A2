#include "Application.h"


Application::Application(int _height, int _width)
{
	window   = std::make_unique<Window>(_height, _width);
	renderer = std::make_unique<Renderer>(window);
	triangle = std::make_unique<Triangle>(renderer);
}


Application::~Application()
{

}



void Application::Run()
{
	// Update
	Update();

	// Draw
	Draw();
}


void Application::Update()
{

}


void Application::Draw()
{
	renderer->BeginFrame();

	// Render everything here!
	triangle->Draw(renderer);

	renderer->EndFrame();
}