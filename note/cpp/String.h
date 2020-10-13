#pragma once
#include <iostream>
#include <string>
using namespace std;

class String {
public:
	// 构造函数(ctor)
	String(const char* cstr = 0) {
		if (cstr == 0) {
			m_data = new char[1];
			*m_data = '\0';
		}
		else {
			m_data = new char[strlen(cstr) + 1];
			strcpy(m_data, cstr);
		}
	}
	// 拷贝构造函数(copy ctor)
	String(const String& o) {
		m_data = new char[strlen(o.m_data) + 1];
		strcpy(m_data, o.m_data);
	}
	// 拷贝赋值函数(copy assignment operator)
	String& operator = (const String& o) {
		// 检测自我赋值
		if (this == &o) return *this;

		delete[] m_data;
		m_data = new char[strlen(o.m_data) + 1];
		strcpy(m_data, o.m_data);
		return *this;
	}

	// 析构函数(dtor)
	~String() {
		delete[] m_data;
	}
	char* get_c_str() const {
		return m_data;
	}
private:
	char* m_data;
};

ostream& operator << (ostream& os, const String& s) {
	return os << s.get_c_str();
}
