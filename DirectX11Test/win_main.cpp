
#include "win_main.h"
#include "app.h"


int CALLBACK WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	INT CommandShow)
{
	App Application;

	return Application.Execute();
}