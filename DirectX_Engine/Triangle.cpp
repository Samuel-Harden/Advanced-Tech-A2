#include "Triangle.h"
#include <fstream>
#include <vector>

using namespace std;

struct Vertex
{
	float x, y;
	float r, g, b;
};


Triangle::Triangle(std::unique_ptr<Renderer>& _renderer)
{
	CreateMesh(_renderer);

	CreateShaders(_renderer);
}


Triangle::~Triangle()
{
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();

}


void Triangle::CreateMesh(std::unique_ptr<Renderer>& _renderer)
{
	// Define our Vertices...
	Vertex vertices[] = {
		{ -1, -1, 1, 0, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 1, -1, 0, 0, 1 }
	};

	// Create vertex buffer
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	_renderer->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
}


void Triangle::CreateShaders(std::unique_ptr<Renderer>& _renderer)
{
	// Create Shaders
	ifstream vsfile("triangleVertexShader.cso", ios::binary);
	ifstream psfile("trianglePixelShader.cso", ios::binary);

	vector<char> vsData = {istreambuf_iterator<char>(vsfile), istreambuf_iterator <char>()};
	vector<char> psData = { istreambuf_iterator<char>(psfile), istreambuf_iterator <char>() };

	_renderer->GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	_renderer->GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);

	// Create Input Layouts
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	_renderer->GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}


void Triangle::Draw(std::unique_ptr<Renderer>& _renderer)
{
	auto deviceContext = _renderer->GetDeviceContext();

	// Bind our triangle shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	// Bind our vertex buffer
	// OPTIMISATION
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw
	deviceContext->Draw(3, 0); // (No of Verts, and where to start)
}