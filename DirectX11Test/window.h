#pragma once
#include "win_main.h"
#include "exception.h"
#include "keyboard.h"

class Window
{
public:
	Window(int _Width, int _Height, const char* _Name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

private:
	class WindowClass
	{
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass() ;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr const char* m_WindowClassName = "Direct3D Engine Window";
		static WindowClass m_WindowClass;
		HINSTANCE m_HInstance;
	};

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND _WindowHandle, UINT _Message, WPARAM _WParam, LPARAM _LParam);
	static LRESULT CALLBACK HandleMessageThunk(HWND _WindowHandle, UINT _Message, WPARAM _WParam, LPARAM _LParam);
	LRESULT HandleMessage(HWND _WindowHandle, UINT _Message, WPARAM _WParam, LPARAM _LParam);
public:
	Keyboard m_Keyboard;

private:
	int m_Width;
	int m_Height;
	HWND m_WindowHandle;

public:
	class WindowException : public Exception
	{
	public:
		WindowException(int _Line, const char* _File, HRESULT _HResult);
		const char* what() const override;

		virtual const char* GetType() const;
		static std::string TranslateErrorCode(HRESULT _HResult);
		HRESULT GetErrorCode() const;
		std::string GetErrorString() const;
	private:
		HRESULT m_HResult;
	};
};



#define HWND_EXCEPT( Handle ) Window::WindowException(__LINE__, __FILE__, Handle)
#define HWND_LAST_EXCEPT() Window::WindowException(__LINE__, __FILE__, GetLastError())



