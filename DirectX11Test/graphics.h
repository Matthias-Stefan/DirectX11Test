#pragma once

#include "win_main.h"
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND _WindowHandle, int _Width, int _Height);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	void EndFrame();
	void ClearBuffer(float _Red, float _Green, float _Blue)
	{
		const float color[] = { _Red, _Green, _Blue, 1.0f };
		m_pContext->ClearRenderTargetView(m_pRenderTargetView, color);
	}
private:
	ID3D11Device* m_pDevice = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
};

