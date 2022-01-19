#include "exception.h"

#include <sstream>

Exception::Exception(int _Line, const char* _File)
	: m_Line(_Line), m_File(_File)
{}

const char* Exception::what() const
{
	std::ostringstream StringStream;
	StringStream << GetType() << std::endl
				 << GetOriginString();
	m_WhatBuffer = StringStream.str();
	return m_WhatBuffer.c_str();
}

const char* Exception::GetType() const
{
	return "Exception";
}

int Exception::GetLine() const
{
	return m_Line;
}

const std::string& Exception::GetFile() const
{
	return m_File;
}

std::string Exception::GetOriginString() const
{
	std::ostringstream StringStream;
	StringStream << "[File]" << m_File << std::endl
				 << "[Line]" << m_Line;
	return std::string();
}
