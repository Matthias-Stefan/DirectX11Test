#include "keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char _KeyCode) const
{
	return m_KeyStates[_KeyCode];
}

std::optional<Keyboard::Event> Keyboard::ReadKey()
{
	if (m_KeyBuffer.size() > 0u)
	{
		Keyboard::Event Event = m_KeyBuffer.front();
		m_KeyBuffer.pop();
		return Event;
	}
	return {};
}

bool Keyboard::KeyIsEmpty() const
{
	return m_KeyBuffer.empty();
}

void Keyboard::FlushKey()
{
	m_KeyBuffer = std::queue<Event>();
}

std::optional<char> Keyboard::ReadChar()
{
	if (m_CharBuffer.size() > 0u)
	{
		unsigned char CharCode = m_CharBuffer.front();
		m_CharBuffer.pop();
		return CharCode;
	}
	return {};
}

bool Keyboard::CharIsEmpty() const
{
	return m_CharBuffer.empty();
}

void Keyboard::FlushChar()
{
	m_CharBuffer = std::queue<char>();
}

void Keyboard::Flush()
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutorepeat()
{
	m_AutorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat()
{
	m_AutorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const
{
	return m_AutorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char _Keycode)
{
	m_KeyStates[_Keycode] = true;
	m_KeyBuffer.push(Keyboard::Event(Keyboard::Event::Type::PRESS, _Keycode));
	TrimBuffer(m_KeyBuffer);
}

void Keyboard::OnKeyReleased(unsigned char _Keycode)
{
	m_KeyStates[_Keycode] = false;
	m_KeyBuffer.push(Keyboard::Event(Keyboard::Event::Type::RELEASE, _Keycode));
	TrimBuffer(m_KeyBuffer);
}

void Keyboard::OnChar(char _Character)
{
	m_CharBuffer.push(_Character);
	TrimBuffer(m_CharBuffer);
}

void Keyboard::ClearState()
{
	m_KeyStates.reset();
}
