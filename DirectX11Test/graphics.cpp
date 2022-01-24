#include "graphics.h"

#pragma comment(lib,"d3d11.lib")

Graphics::Graphics(HWND _WindowHandle, int _Width, int _Height)
{
	DXGI_SWAP_CHAIN_DESC SwapChainDescription = {};
	SwapChainDescription.BufferDesc.Width = _Width;
	SwapChainDescription.BufferDesc.Height = _Height;
	SwapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
	SwapChainDescription.BufferDesc.RefreshRate.Denominator = 0;
	SwapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDescription.SampleDesc.Count = 1;
	SwapChainDescription.SampleDesc.Quality = 0;
	SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDescription.BufferCount = 1;
	SwapChainDescription.OutputWindow = _WindowHandle;
	SwapChainDescription.Windowed = TRUE;
	SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDescription.Flags = 0;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&SwapChainDescription,
		&m_pSwapChain,
		&m_pDevice,
		nullptr,
		&m_pContext
	);
	// gain access to texture subresource in swap chain (back buffer)
	ID3D11Resource* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), 
							reinterpret_cast<void**>(&pBackBuffer));


	m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
	pBackBuffer->Release();


}

Graphics::~Graphics()
{
	if (m_pContext != nullptr)
	{
		m_pContext->Release();
	}
	if (m_pDevice != nullptr)
	{
		m_pContext->Release();
	}
	if (m_pSwapChain != nullptr)
	{
		m_pSwapChain->Release();
	}
	if (m_pRenderTargetView != nullptr)
	{
		m_pRenderTargetView->Release();
	}
}

void Graphics::EndFrame()
{
	m_pSwapChain->Present( 1u, 0u );
}
