
#include "win_main.h"
#include "window.h"


int CALLBACK WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	INT CommandShow)
{
	Window Window_(800, 300, "DirectX11Test");

	MSG Message;
	BOOL Result;
	while ((Result = GetMessage(&Message, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	if (Result == -1) return -1;

	return Message.wParam;
}