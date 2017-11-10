#pragma once
#include <Windows.h>

class Window 
{
public:
	Window(int width, int height);
	HWND GetHandle();

protected:


private:
	HWND m_handle;

};