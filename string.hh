#pragma once
#include "prelude.hh"
#include <string.h>

// TODO: implement strcpy
// TODO: implement strlen

class String
{
	size_t m_len;
	size_t m_cap;
	char* m_data;

public:
	String()
		: m_len(0)
		, m_cap(16)
		, m_data(new char[16]){}

	String(size_t cap)
		: m_len(0)
		, m_cap(cap)
		, m_data(new char[cap]){}

	String(const char* c_str)
		: m_len(strlen(c_str))
		, m_cap(m_len + 1)
	{
		m_data = new char[m_cap];
		strcpy(m_data, c_str);
	}

	String(const String& other)
		: m_len(other.m_len)
		, m_cap(other.m_cap)
	{
		m_data = new char[m_cap];
		m_data = strcpy(m_data, other.m_data);
	}

	String(String&& other)
	{
		m_len = other.m_len;
		m_cap = other.m_cap;
		m_data = other.m_data;
		other.m_data = nullptr;
		other.m_len = 0;
		other.m_cap = 0;
	}

	String& operator=(String&& rhs) noexcept
	{
		if (this == &rhs) {
			return *this;
		}

		delete[] m_data;
		m_len = rhs.m_len;
		m_cap = rhs.m_cap;
		m_data = rhs.m_data;
		rhs.m_data = nullptr;
		rhs.m_len = 0;
		rhs.m_cap = 0;

		return *this;
	}

	~String()
	{
		delete[] m_data;
	}

	void push(char ch)
	{
		if (m_len >= m_cap) {
			m_cap *= 2;
			m_data = (char*)realloc(m_data, m_cap);
		}
		m_data[m_len++] = ch;
	}

	void push(const String& str)
	{
		if (m_len + str.m_len > m_cap) {
			m_cap = m_len + str.m_len;
			m_data = (char*)realloc(m_data, m_cap);
		}
		m_len += str.m_len;
		strcat(m_data, str.m_data);
	}

	void push(String&& str)
	{
		if (m_len + str.m_len > m_cap) {
			m_cap = m_len + str.m_len;
			m_data = (char*)realloc(m_data, m_cap);
		}
		m_len += str.m_len;
		strcat(m_data, str.m_data);
	}

	operator const char*()
	{
		return m_data;
	}

	operator char*()
	{
		return m_data;
	}

	String& operator+=(const String& rhs)
	{
		push(rhs);
		return *this;
	}

	String& operator+=(String&& rhs)
	{
		push(rhs);
		return *this;
	}

	String& operator+=(const char* rhs)
	{
		push(rhs);
		return *this;
	}

	String& operator+=(char ch)
	{
		push(ch);
		return *this;
	}

	char operator[](size_t ch)
	{
		return m_data[ch];
	}
};

inline String operator+(const String& lhs, const String& rhs)
{
	String new_str{lhs};
	new_str.push(rhs);
	return new_str;
}

inline String operator+(const char* lhs, const String& rhs)
{
	String new_str(lhs);
	new_str.push(rhs);
	return new_str;
}

inline String operator+(const String& lhs, const char* rhs)
{
	String new_str(lhs);
	new_str.push(rhs);
	return new_str;
}
