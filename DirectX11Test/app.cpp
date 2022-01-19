#include "app.h"

#include <sstream>
#include <iomanip>

App::App() : m_Window(800, 300, "DirectX11Test") {}

int App::Execute()
{
	MSG Message;
	BOOL Result;
	while ((Result = GetMessage(&Message, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);

		ComputeFrame();
	}

	if (Result == -1)
	{
		throw HWND_LAST_EXCEPT();
	}

	return Message.wParam;
}

void App::ComputeFrame()
{
	const float Time = m_Timer.Peek();
	std::ostringstream StringStream;
	StringStream << "time elapsed: " << std::setprecision(1) << std::fixed << Time << "sec";
	m_Window.SetTitle(StringStream.str());
}