#include "app.h"

#include <sstream>
#include <iomanip>

App::App() : m_Window(800, 300, "DirectX11Test") {}

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
}