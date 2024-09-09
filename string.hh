#pragma once
#include "allocs.hh"
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
		, m_cap(0)
		, m_data(nullptr){}

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
		if (this == &rhs)
			goto defer;

		delete[] m_data;
		m_len = rhs.m_len;
		m_cap = rhs.m_cap;
		m_data = rhs.m_data;
		rhs.m_data = nullptr;
		rhs.m_len = 0;
		rhs.m_cap = 0;

	defer:
		return *this;
	}

	~String()
	{
		delete[] m_data;
	}

	String& reserve(size_t additional_cap)
	{
		auto empty_space = m_cap - m_len;
		if (empty_space >= additional_cap)
			goto defer;

		m_cap += additional_cap;
		m_data = (char*)realloc(m_data, m_cap);
	defer:
		return *this;
	}

#define RESIZE(comp, new_cap) if (comp) { m_cap = new_cap; m_data = (char*)realloc(m_data, m_cap); }

	String& push(char ch)
	{
		RESIZE(m_len >= m_cap, m_cap * 2)
		m_data[m_len++] = ch;
		return *this;
	}

	String& push(const String& str)
	{
		RESIZE(m_len + str.m_len > m_cap, m_len + str.m_len)
		m_len += str.m_len;
		strcat(m_data, str.m_data);
		return *this;
	}

	String& push(String&& str)
	{
		RESIZE(m_len + str.m_len > m_cap, m_len + str.m_len)
		m_len += str.m_len;
		strcat(m_data, str.m_data);
		return *this;
	}

#undef RESIZE

#define get(type, what, which) type what() { return which; }
	get(size_t, len, m_len)
	get(size_t, cap, m_cap)
	get(char*, c_str, m_data)
#undef get

#define op(T) void operator+=(T rhs) { push(rhs); }
	op(const String&)
	op(String&&)
	op(const char*)
	op(char)
#undef op

	char operator[](size_t x)
	{
		if (x >= m_len) // segfault if out of bounds :)
			*(volatile int*)0 = 0;
		return m_data[x];
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
