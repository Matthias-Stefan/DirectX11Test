#pragma once

#include <exception>
#include <string>


class Exception : public std::exception
{
public:
	Exception(int _Line, const char* _File);
	const char* what() const override;

	virtual const char* GetType() const;
	int GetLine() const;
	const std::string& GetFile() const;
	std::string GetOriginString() const;
protected:
	mutable std::string m_WhatBuffer;

private:
	int m_Line;
	std::string m_File;
};


