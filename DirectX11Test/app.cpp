#include "app.h"

#include <sstream>
#include <iomanip>

App::App() : m_Window(800, 800, "DirectX11Test") {}

int App::Execute()
{
	while (true)
	{
		if (const auto eCode = m_Window.ProcessMessages())
		{
			return *eCode;
		}
		HandleInput();
		ComputeFrame();

		Sleep(1);
	}
}

void App::HandleInput()
{

}

void App::ComputeFrame()
{
	const float Time = m_Timer.Peek();
	std::ostringstream StringStream;
	StringStream << "time elapsed: " << std::setprecision(1) << std::fixed << Time << "sec";
	m_Window.SetTitle(StringStream.str());

	const float c = cos(m_Timer.Peek()) / 2.0f + 0.5f;
	m_Window.GFX().ClearBuffer(c, c, 1.0f);
	m_Window.GFX().EndFrame();
}