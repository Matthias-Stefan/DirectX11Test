#include "timer.h"

Timer::Timer()
{
	m_Last = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	const auto Old = m_Last;
	m_Last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> FrameTime = m_Last - Old;
	return FrameTime.count();
}

float Timer::Peek() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_Last).count();
}
