#pragma once
#include <queue>
#include <bitset>
#include <optional>


class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			PRESS,
			RELEASE
		};

	private:
		enum class Type m_EventType;
		unsigned char m_Code;

	public:
		Event(Type _Type, unsigned char _Code)
			: m_EventType(_Type), m_Code(_Code)
		{}
		bool IsPressed() const { return m_EventType == Type::PRESS; }
		bool IsRelease() const { return m_EventType == Type::RELEASE; }
		unsigned char GetCode() const { return m_Code; }

	};
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	// NOTE(matthias): key event stuff
	bool KeyIsPressed(unsigned char _KeyCode) const;
	std::optional<Event> ReadKey();
	bool KeyIsEmpty() const;
	void FlushKey();

	// NOTE(matthias): char event stuff
	std::optional<char> ReadChar();
	bool CharIsEmpty() const;
	void FlushChar();
	void Flush();

	// NOTE(matthias): autorepeat control
	void EnableAutorepeat();
	void DisableAutorepeat();
	bool AutorepeatIsEnabled() const;
private:
	void OnKeyPressed(unsigned char _Keycode);
	void OnKeyReleased(unsigned char _Keycode);
	void OnChar(char _Character);
	void ClearState();

	template<typename T>
	static void TrimBuffer(std::queue<T>& Buffer);
private:
	static constexpr unsigned int m_nKeys = 256u;
	static constexpr unsigned int m_BufferSize = 16u;
	bool m_AutorepeatEnabled = false;
	std::bitset<m_nKeys> m_KeyStates;
	std::queue<Event> m_KeyBuffer;
	std::queue<char> m_CharBuffer;















};

template<typename T>
inline void Keyboard::TrimBuffer(std::queue<T>& Buffer)
{
}
