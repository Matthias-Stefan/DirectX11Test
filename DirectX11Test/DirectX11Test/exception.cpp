#include "exception.h"

#include <sstream>

Exception::Exception(int Line, const char* File)
{
	this->Line = Line;
	this->File = File;
}

const char* Exception::what() const
{
	std::ostringstream StringStream;
	StringStream << GetType() << std::endl
				 << GetOriginString();
	WhatBuffer = StringStream.str();
	return WhatBuffer.c_str();
}

const char* Exception::GetType() const
{
	return "Exception";
}

int Exception::GetLine() const
{
	return Line;
}

const std::string& Exception::GetFile() const
{
	return File;
}

std::string Exception::GetOriginString() const
{
	std::ostringstream StringStream;
	StringStream << "[File]" << File << std::endl
				 << "[Line]" << Line;
	return std::string();
}
