#pragma once
#include "Renderer.h"
#include<memory>

class Triangle
{
public:
	Triangle(std::unique_ptr<Renderer>& _renderer);
	~Triangle();
	void Draw(std::unique_ptr<Renderer>& _renderer);


protected:


private:
	void CreateMesh(std::unique_ptr<Renderer>& _renderer);
	void CreateShaders(std::unique_ptr<Renderer>& _renderer);

	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;

};