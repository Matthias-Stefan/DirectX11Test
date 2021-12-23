#include "window.h"

#include <sstream>
#include <stdlib.h>

Window::Window(int Width, int Height, const char* Name)
{
	try
	{
		// invoke App.Go()
		// return EXIT_SUCCESS;
	}
	catch (const WindowException& Except)
	{
		MessageBox(nullptr, Except.what(), Except.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& Except)
	{
		MessageBox(nullptr, Except.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	// return EXIT_FAILURE; 

	RECT WindowRect;
	WindowRect.left = 100;
	WindowRect.right = Width + WindowRect.left;
	WindowRect.top = 100;
	WindowRect.bottom = Height + WindowRect.top;
	if(FAILED(AdjustWindowRect(&WindowRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		throw HWND_LAST_EXCEPT();
	}

	WindowHandle = CreateWindow(
		WindowClass::GetName(), 
		Name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		WindowRect.right - WindowRect.left, 
		WindowRect.bottom - WindowRect.top,
		nullptr, 
		nullptr, 
		WindowClass::GetInstance(), 
		this);
	ShowWindow(WindowHandle, SW_SHOWDEFAULT);

	if (WindowHandle == nullptr)
	{
		throw HWND_LAST_EXCEPT();
	}


}

Window::~Window()
{
	DestroyWindow(WindowHandle);
}

LRESULT CALLBACK Window::HandleMessageSetup(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	if (Message == WM_NCCREATE)
	{
		const CREATESTRUCTW* const Create = reinterpret_cast<CREATESTRUCTW*>(LParam);
		Window* const Window_ = static_cast<Window*>(Create->lpCreateParams);

		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Window_));
		// set message procedure to normal handler now that setup is finished
		SetWindowLongPtr(WindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));

		return Window_->HandleMessage(WindowHandle, Message, WParam, LParam);
	}
	return DefWindowProc(WindowHandle, Message, WParam, LParam);
}

LRESULT CALLBACK Window::HandleMessageThunk(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	Window* const Window_ = reinterpret_cast<Window*>(GetWindowLongPtr(WindowHandle, GWLP_USERDATA));

	return Window_->HandleMessage(WindowHandle, Message, WParam, LParam);
}

LRESULT Window::HandleMessage(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			return 0;
		}
	}

	return DefWindowProc(WindowHandle, Message, WParam, LParam);
}


Window::WindowClass Window::WindowClass::WindowClass_;

Window::WindowClass::WindowClass() : HInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX WindowClass = { 0 };
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_OWNDC;
	WindowClass.lpfnWndProc = HandleMessageSetup;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = GetInstance();
	WindowClass.hIcon = nullptr;
	WindowClass.hCursor = nullptr;
	WindowClass.hbrBackground = nullptr;
	WindowClass.lpszMenuName = nullptr;
	WindowClass.lpszClassName = GetName();
	WindowClass.hIconSm = nullptr;

	RegisterClassEx(&WindowClass);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(WindowClassName, GetInstance());
}

const char* Window::WindowClass::GetName()
{
	return WindowClassName;
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return WindowClass_.HInstance;
}



Window::WindowException::WindowException(int Line, const char* File, HRESULT HResult)
	: Exception(Line, File), HResult(HResult)
{}

const char* Window::WindowException::what() const
{
	std::ostringstream StringStream;
	StringStream << GetType() << std::endl
				 << "[Error Code]" << GetErrorCode() << std::endl
				 << "[Description]" << GetErrorString() << std::endl
				 << GetOriginString();
	WhatBuffer = StringStream.str();
	return WhatBuffer.c_str();
}

const char* Window::WindowException::GetType() const
{
	return "Window Exception";
}

std::string Window::WindowException::TranslateErrorCode(HRESULT HResult)
{
	char* MessageBuffer = nullptr;
	DWORD MessageLength = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
										nullptr, HResult, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
										reinterpret_cast<LPTSTR>(&MessageBuffer), 0, nullptr);
	if (MessageLength == 0)
	{
		return "Undefined error code";
	}
	std::string ErrorString = MessageBuffer;
	LocalFree(MessageBuffer);
	return ErrorString;
}

HRESULT Window::WindowException::GetErrorCode() const
{
	return HResult;
}

std::string Window::WindowException::GetErrorString() const
{
	return TranslateErrorCode(HResult);
}
