
#include "win_main.h"
#include "window.h"
#include "data_structures.h"

void TestQueue()
{
	Queue<int> queue = { 4 };
	queue.Push(2);
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);

	int ans = queue.Pop();

	int x = 5;
}


int CALLBACK WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	INT CommandShow)
{
	TestQueue();


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