#pragma once
#include "win_main.h"
#include "exception.h"


class Window
{
public:
	Window(int Width, int Height, const char* Name);
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
		static constexpr const char* WindowClassName = "Direct3D Engine Window";
		static WindowClass WindowClass_;
		HINSTANCE HInstance;
	};

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
	static LRESULT CALLBACK HandleMessageThunk(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
	LRESULT HandleMessage(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
private:
	int Width;
	int Height;
	HWND WindowHandle;

public:
	class WindowException : public Exception
	{
	public:
		WindowException(int Line, const char* File, HRESULT HResult);
		const char* what() const override;

		virtual const char* GetType() const;
		static std::string TranslateErrorCode(HRESULT HResult);
		HRESULT GetErrorCode() const;
		std::string GetErrorString() const;
	private:
		HRESULT HResult;
	};
};



#define HWND_EXCEPT( Handle ) Window::WindowException(__LINE__, __FILE__, Handle)
#define HWND_LAST_EXCEPT() Window::WindowException(__LINE__, __FILE__, GetLastError())



