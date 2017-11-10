#pragma once
#include<memory>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"


class Application
{
public:
	Application(int _height, int _width);
	~Application();

	void Run();

protected:


private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Triangle> triangle;
};