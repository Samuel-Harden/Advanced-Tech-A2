#include "Renderer.h"

Renderer::Renderer(std::unique_ptr<Window>& window)
{
	CreateDevice(window);
	CreateRenderTarget();
}

void Renderer::CreateDevice(std::unique_ptr<Window>& window)
{
	// swap chain (swap between front and
	// back buffer (Double Buffering))

	// Define Swap Chain
	DXGI_SWAP_CHAIN_DESC swap_chain_desc = { 0 };

	swap_chain_desc.BufferCount = 1; // Sets 1 BACKBUFFER
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = window->GetHandle();
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.Windowed = true; // Full Screen or Windowed

	// Create the Swap Chain device and device context
	auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0, nullptr, 0, D3D11_SDK_VERSION, &swap_chain_desc, &m_swapChain,
		&m_device, nullptr, &m_deviceContext);

	// Check for errors
	if (result != S_OK)
	{
		// Display error message
		MessageBox(nullptr, "Problem Creating DX11", "Error", MB_OK);

		// Force close
		exit(0);
	}
}


void Renderer::CreateRenderTarget()
{
	// Get the buffer from the swap chain
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &backBuffer);

	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);

	backBuffer->GetDesc(&m_backBufferDesc);
	backBuffer->Release();
}


void Renderer::BeginFrame()
{
	//Bind render target
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

	// Set Viewport
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, (float) m_backBufferDesc.Width, (float) m_backBufferDesc.Height);
	m_deviceContext->RSSetViewports(1, &viewport);

	// Set the Background Color
	float clearColor[] = { .25f, .5f, 1, 1 };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}


void Renderer::EndFrame()
{
	// Swap the Buffer
	m_swapChain->Present(0, 0);

	// (0, 0) works for both x86 & x64 Solution Platforms
	// (1, 0) only works on x64 Solution Platforms
}


ID3D11Device* Renderer::GetDevice()
{
	return m_device;
}


ID3D11DeviceContext* Renderer::GetDeviceContext()
{
	return m_deviceContext;
}