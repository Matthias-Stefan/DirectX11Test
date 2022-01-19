#pragma once

#include "window.h"
#include "timer.h"

class App
{
public:
	App();
	
	int Execute();
private:
	void ComputeFrame();
private:
	WND m_Window;
	Timer m_Timer;
};

