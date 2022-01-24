
#include "win_main.h"
#include "window.h"
#include "app.h"


int CALLBACK WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	INT CommandShow)
{
	try
	{
		return App{}.Execute();
	}
	catch (const Window::WindowException& Except)
	{
		MessageBox(nullptr, Except.what(), Except.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& Except)
	{
		MessageBox(nullptr, Except.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
}