#include "win_main.h"
#include "mouse.h"


std::optional<Mouse::Event> Mouse::Read()
{
	if (m_Buffer.size() > 0u)
	{
		Mouse::Event Event = m_Buffer.front();
		m_Buffer.pop();
		return Event;
	}
	return {};
}

void Mouse::Flush()
{
	m_Buffer = std::queue<Event>();
}

std::pair<int, int> Mouse::GetPos() const
{
	return { m_X, m_Y };
}

int Mouse::GetPosX() const
{
	return m_X;
}

int Mouse::GetPosY() const
{
	return m_Y;
}

bool Mouse::IsInWindow() const
{
	return m_IsInWindow;
}

bool Mouse::LeftIsPressed() const
{
	return m_LeftIsPressed;
}

bool Mouse::RightIsPressed() const
{
	return m_RightIsPressed;
}

std::optional<Mouse::RawDelta> Mouse::ReadRawDelta()
{
	return std::optional<RawDelta>();
}

void Mouse::EnableRaw()
{
	m_RawEnabled = true;
}

void Mouse::DisableRaw()
{
	m_RawEnabled = false;
}

bool Mouse::RawEnabled()
{
	return m_RawEnabled;
}


void Mouse::OnMouseMove(int _X, int _Y)
{
	m_X = _X;
	m_Y = _Y;

	m_Buffer.push(Mouse::Event(Mouse::Event::Type::MOVE, *this));
	TrimBuffer();
}

void Mouse::OnMouseLeave()
{
	m_IsInWindow = false;
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::LEAVE, *this));
	TrimBuffer();
}

void Mouse::OnMouseEnter()
{
	m_IsInWindow = true;
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::ENTER, *this));
	TrimBuffer();
}

void Mouse::OnRawDelta(int _DX, int _DY)
{
	m_RawDeltaBuffer.push({ _DX, _DY });
	TrimBuffer();
}

void Mouse::OnLeftPressed(int _X, int _Y)
{
	m_LeftIsPressed = true;
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::L_PRESS, *this));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int _X, int _Y)
{
	m_LeftIsPressed = false;
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::L_RELEASE, *this));
	TrimBuffer();
}

void Mouse::OnRightPressed(int _X, int _Y)
{
	m_RightIsPressed = true;
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::R_PRESS, *this));
	TrimBuffer();
}

void Mouse::OnRightReleased(int _X, int _Y)
{
	m_RightIsPressed = false;
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::R_RELEASE, *this));
	TrimBuffer();
}

void Mouse::OnWheelUp(int _X, int _Y)
{
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::WHEEL_UP, *this));
	TrimBuffer();
}

void Mouse::OnWheelDown(int _X, int _Y)
{
	m_Buffer.push(Mouse::Event(Mouse::Event::Type::WHEEL_DOWN, *this));
	TrimBuffer();
}

void Mouse::TrimBuffer()
{
	while (m_Buffer.size() > m_BufferSize)
	{
		m_Buffer.pop();
	}
}

void Mouse::TrimRawInputBuffer()
{
	while (m_RawDeltaBuffer.size() > m_BufferSize)
	{
		m_RawDeltaBuffer.pop();
	}
}

void Mouse::OnWheelDelta(int _X, int _Y, int _Delta)
{
	m_WheelDeltaCarry += _Delta;
	while (m_WheelDeltaCarry >= WHEEL_DELTA)
	{
		m_WheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(_X, _Y);
	}
	while (m_WheelDeltaCarry <= -WHEEL_DELTA)
	{
		m_WheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(_X, _Y);
	}
}

