#include "window.h"

#include <sstream>
#include <stdlib.h>

Window::Window(int _Width, int _Height, const char* _Name)
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
	WindowRect.right = _Width + WindowRect.left;
	WindowRect.top = 100;
	WindowRect.bottom = _Height + WindowRect.top;
	if(FAILED(AdjustWindowRect(&WindowRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		throw HWND_LAST_EXCEPT();
	}

	m_WindowHandle = CreateWindow(
		WindowClass::GetName(), 
		_Name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		WindowRect.right - WindowRect.left, 
		WindowRect.bottom - WindowRect.top,
		nullptr, 
		nullptr, 
		WindowClass::GetInstance(), 
		this);
	ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);

	if (m_WindowHandle == nullptr)
	{
		throw HWND_LAST_EXCEPT();
	}


}

Window::~Window()
{
	DestroyWindow(m_WindowHandle);
}

LRESULT CALLBACK Window::HandleMessageSetup(HWND _WindowHandle, 
											UINT _Message, 
											WPARAM _WParam, 
											LPARAM _LParam)
{
	if (_Message == WM_NCCREATE)
	{
		const CREATESTRUCTW* const Create = reinterpret_cast<CREATESTRUCTW*>(_LParam);
		Window* const Window_ = static_cast<Window*>(Create->lpCreateParams);

		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(_WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Window_));
		// set message procedure to normal handler now that setup is finished
		SetWindowLongPtr(_WindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));

		return Window_->HandleMessage(_WindowHandle, _Message, _WParam, _LParam);
	}
	return DefWindowProc(_WindowHandle, _Message, _WParam, _LParam);
}

LRESULT CALLBACK Window::HandleMessageThunk(HWND _WindowHandle, 
											UINT _Message, 
											WPARAM _WParam, 
											LPARAM _LParam)
{
	Window* const Window_ = reinterpret_cast<Window*>(GetWindowLongPtr(_WindowHandle, GWLP_USERDATA));

	return Window_->HandleMessage(_WindowHandle, _Message, _WParam, _LParam);
}

LRESULT Window::HandleMessage(HWND _WindowHandle, 
							  UINT _Message, 
							  WPARAM _WParam, 
							  LPARAM _LParam)
{
	switch (_Message)
	{
		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			return 0;
		}
		case WM_KILLFOCUS:
		{
			m_Keyboard.ClearState();
			break;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (!(_LParam & 0x40000000) || m_Keyboard.AutorepeatIsEnabled())
			{
				m_Keyboard.OnKeyPressed(static_cast<unsigned char>(_WParam));
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			m_Keyboard.OnKeyReleased(static_cast<unsigned char>(_WParam));
			break;
		}
		case WM_CHAR:
		{
			m_Keyboard.OnChar(static_cast<unsigned char>(_WParam));
			break;
		}
	}	

	return DefWindowProc(_WindowHandle, _Message, _WParam, _LParam);
}


Window::WindowClass Window::WindowClass::m_WindowClass;

Window::WindowClass::WindowClass() : m_HInstance(GetModuleHandle(nullptr))
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
	UnregisterClass(m_WindowClassName, GetInstance());
}

const char* Window::WindowClass::GetName()
{
	return m_WindowClassName;
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return m_WindowClass.m_HInstance;
}



Window::WindowException::WindowException(int _Line, const char* _File, HRESULT _HResult)
	: Exception(_Line, _File), m_HResult(_HResult)
{}

const char* Window::WindowException::what() const
{
	std::ostringstream StringStream;
	StringStream << GetType() << std::endl
				 << "[Error Code]" << GetErrorCode() << std::endl
				 << "[Description]" << GetErrorString() << std::endl
				 << GetOriginString();
	m_WhatBuffer = StringStream.str();
	return m_WhatBuffer.c_str();
}

const char* Window::WindowException::GetType() const
{
	return "Window Exception";
}

std::string Window::WindowException::TranslateErrorCode(HRESULT _HResult)
{
	char* MessageBuffer = nullptr;
	DWORD MessageLength = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
										nullptr, _HResult, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
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
	return m_HResult;
}

std::string Window::WindowException::GetErrorString() const
{
	return TranslateErrorCode(m_HResult);
}
