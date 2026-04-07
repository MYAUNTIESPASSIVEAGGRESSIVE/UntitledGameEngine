#pragma once
#include <DirectXMath.h>
namespace Kengine
{
	class Transform
	{
	public:

		DirectX::XMVECTOR position{ 0.0f, 0.0f, 0.0f };
		DirectX::XMVECTOR rotation{ 0.0f, 0.0f, 0.0f };
		DirectX::XMVECTOR scale{ 1.0f, 1.0f, 1.0f };

		DirectX::XMMATRIX GetWorldMatrix();

		void Translate(DirectX::XMVECTOR translation);
		void Rotate(DirectX::XMVECTOR inRotation);

		DirectX::XMVECTOR GetForward();
		DirectX::XMVECTOR GetRight();
		DirectX::XMVECTOR GetUp();
	};
}


