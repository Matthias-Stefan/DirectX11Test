
#include "win_main.h"
#include "window.h"
#include "data_structures.h"



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

		if (Window_.m_Keyboard.KeyIsPressed(VK_MENU))
		{
			MessageBoxA(nullptr, "Something Happon!",
				"The alt key was pressed", MB_OK | MB_ICONEXCLAMATION);
		}
	}

	if (Result == -1) return -1;

	return Message.wParam;
}