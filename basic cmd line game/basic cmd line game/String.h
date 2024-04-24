#pragma once
#include <iostream>

class String {
	private:
		char* dataPtr;
		int length;

	public:
		String();

		String(const String& str);
		
		String(const char* textPtr);

		~String();

		int Length() const;
		char& CharacterAt(int index);
		const char& CharacterAt(int index) const;

		bool EqualTo(const String& str) const;

		String& Append(const String& str);
		String& Append(const char chr);
		String& Prepend(const String& str);

		char* CStr() const;

		String& ToLower();
		String& ToUpper();

		int Find(const String& str);
		int Find(int startIndex, const String& str);

		String& Replace(const String& find, const String& replace);

		String& ReadFromConsole();
		String& WriteToConsole();

		bool operator==(const String& str);
		bool operator==(const String& str) const;
		bool operator!=(const String& str);

		String& operator=(const String& str);

		char& operator[](int _index);
		const char& operator[](int _index) const;

		bool operator<(const String& str);
		bool operator<(const String& str) const;

		String& operator+=(const String& str);
		String& operator+=(const char chr);
};

String toString(int x);

int toInt(const String& str);

String operator+(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& out, const String& str);