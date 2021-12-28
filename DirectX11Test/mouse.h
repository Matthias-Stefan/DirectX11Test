#pragma once
#include <queue>
#include <optional>

class Mouse
{
	friend class Window;
public:
	struct RawDelta
	{
		int X;
		int Y;
	};
	class Event
	{
	public:
		enum class Type
		{
			L_PRESS,
			L_RELEASE,
			R_PRESS,
			R_RELEASE,
			WHEEL_UP,
			WHEEL_DOWN,
			MOVE,
			ENTER,
			LEAVE
		};
	private:
		Type m_Type;
		bool m_LeftIsPressed;
		bool m_RightIsPressed;
		int m_X;
		int m_Y;
	public:
		Event(Type _Type, const Mouse& Parent)
			: m_Type(_Type),
			m_LeftIsPressed(Parent.m_LeftIsPressed),
			m_RightIsPressed(Parent.m_RightIsPressed),
			m_X(Parent.GetPosX()),
			m_Y(Parent.GetPosY())
		{}

		Type GetType()
		{
			return m_Type;
		}

		std::pair<int, int> GetPos()
		{
			return { m_X, m_Y };
		}

		int GetPosX() const
		{
			return m_X;
		}

		int GetPos() const
		{
			return m_Y;
		}

		bool LeftIsPressed() const
		{
			return m_LeftIsPressed;
		}

		bool RightIsPressed() const
		{
			return m_RightIsPressed;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	std::optional<Mouse::Event> Read();

	bool IsEmpty() const { return m_Buffer.empty(); }
	void Flush();

	std::pair<int, int> GetPos() const;
	int GetPosX() const;
	int GetPosY() const;

	bool IsInWindow() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;

	std::optional<RawDelta> ReadRawDelta();
	void EnableRaw();
	void DisableRaw();
	bool RawEnabled();

private:
	void OnMouseMove(int _X, int _Y);
	void OnMouseLeave();
	void OnMouseEnter();

	void OnRawDelta(int _DX, int _DY);

	void OnLeftPressed(int _X, int _Y);
	void OnLeftReleased(int _X, int _Y);
	void OnRightPressed(int _X, int _Y);
	void OnRightReleased(int _X, int _Y);

	void OnWheelUp(int _X, int _Y);
	void OnWheelDown(int _X, int _Y);

	void TrimBuffer();
	void TrimRawInputBuffer();
	void OnWheelDelta(int _X, int _Y, int _Delta);

private:
	static constexpr unsigned int m_BufferSize = 16u;
	int m_X;
	int m_Y;
	bool m_LeftIsPressed = false;
	bool m_RightIsPressed = false;
	bool m_IsInWindow = false;
	int m_WheelDeltaCarry = 0;
	bool m_RawEnabled = false;
	std::queue<Event> m_Buffer;
	std::queue<RawDelta> m_RawDeltaBuffer;
};