# pragma once

#include "Window.h"
#include <memory>
#include <d3d11.h>

class Renderer
{
public:
	Renderer(std::unique_ptr<Window>& window);

	void BeginFrame();
	void EndFrame();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

protected:


private:
	void CreateDevice(std::unique_ptr<Window>& window);
	void CreateRenderTarget();

	// Device stuff
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	// Render target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_backBufferDesc;

};