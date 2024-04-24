#include "String.h"

//default constructor
String::String() {
    length = 0;
    dataPtr = new char[1];
    *dataPtr = 0;
}

//constructs a copy string object of str
String::String(const String& str) {
    length = str.Length();
    dataPtr = new char[length + 1];
    for (int i = 0; i < length; i++) {
        *(dataPtr + i) = *(str.CStr() + i);
    }
    *(dataPtr + length) = 0;
}

//constructs a string object that holds a copy of the data stored at textPtr
String::String(const char* textPtr) {
    length = 0;
    for (int i = 0; *(textPtr + i) != 0; i++) {
        length++;
    }

    dataPtr = new char[length + 1];
    for (int i = 0; i < length; i++) {
        *(dataPtr + i) = *(textPtr + i);
    }
    *(dataPtr + length) = 0;
}

//destructor clears memory at the address which the string's data is stored
String::~String() {
    delete[] dataPtr;
}

//returns length of string object excluding the null terminator in the form of int
int String::Length() const {
	return length;
}

//returns a reference to the character stored at index within the string object
char& String::CharacterAt(int index) {
    if (index > length) {
        return *(dataPtr + length); //returns null terminator
    }

    return *(dataPtr + index);
}

const char& String::CharacterAt(int index) const {
    if (index > length) {
        return *(dataPtr + length); //returns null terminator
    }

    return *(dataPtr + index);
}

//returns bool value (true if str holds the same data as string object, false otherwise)
bool String::EqualTo(const String& str) const {
    if (length != str.Length()) {
        return false;
    }
    
    for (int i = 0; i < length; i++) {
        if (*(dataPtr + i) != *(str.CStr() + i)) {
            return false;
        }
    }

    return true;
}

//appends a copy of the data stored at str to current string object and returns itself
String& String::Append(const String& str) {
    char* oldPtr = dataPtr;
    dataPtr = new char[length + str.Length() + 1];

    for (int i = 0; i < length; i++) {
        *(dataPtr + i) = *(oldPtr + i);
    }
    
    for (int i = 0; i < str.Length(); i++) {
        *(dataPtr + length + i) = *(str.CStr() + i);
    }

    length += str.Length();
    *(dataPtr + length) = 0;
    delete[] oldPtr;
    return *this;
}

String& String::Append(const char chr) {
    char* oldPtr = dataPtr;
    length++;
    dataPtr = new char[length + 1];
    memcpy(dataPtr, oldPtr, length - 1);
    /*for (int i = 0; i < length - 1; i++) {
        *(dataPtr + i) = *(oldPtr + i);
    }*/

    *(dataPtr + length - 1) = chr;
    *(dataPtr + length) = '\0';

    delete[] oldPtr;
    return *this;
}

//prepends a copy of the data stored at str to current string object and returns itself
String& String::Prepend(const String& str) {
    char* oldPtr = dataPtr;
    dataPtr = new char[length + str.Length() + 1];

    for (int i = 0; i < str.Length(); i++) {
        *(dataPtr + i) = *(str.CStr() + i);
    }
    
    for (int i = 0; i < length; i++) {
        *(dataPtr + str.Length() + i) = *(oldPtr + i);
    }

    length += str.Length();
    *(dataPtr + length) = 0;
    delete[] oldPtr;
    return *this;
}

//returns the starting address of where the string object's data is stored in memory
char* String::CStr() const {
    return dataPtr;
}

//changes all uppercase letters A-Z within string object to lowercase and returns itself
String& String::ToLower() {
    for (int i = 0; i < length; i++) {
        if (*(dataPtr + i) >= 65 && *(dataPtr + i) <= 90) {
            *(dataPtr + i) += 32;
        }
    }

    return *this;
}

//changes all lowercase letters a-z within string object to uppercase and returns itself
String& String::ToUpper() {
    for (int i = 0; i < length; i++) {
        if (*(dataPtr + i) >= 97 && *(dataPtr + i) <= 122) {
            *(dataPtr + i) -= 32;
        }
    }

    return *this;
}

//finds first occurrence of str in string and object and returns the index of where it's found (returns -1 if can't be found)
int String::Find(const String& str) {
    if (length < str.Length()) {
        return -1;
    }

    for (int i = 0; i < length; i++) {
        if (length - i < str.Length()) {
            break;
        }
        
        for (int j = 0; j < str.Length(); j++) {
            if (*(dataPtr + i + j) != *(str.CStr() + j)) {
                break;
            }

            if (j == str.Length() - 1) {
                return i;
            }
        }
    }

    return -1;
}

//find method, but starts seach at startIndex
int String::Find(int startIndex, const String& str) {
    if (length - startIndex < str.Length()) {
        return -1;
    }

    for (int i = startIndex; i < length; i++) {
        if (length - i < str.Length()) {
            break;
        }
        
        for (int j = 0; j < str.Length(); j++) {
            if (*(dataPtr + i + j) != *(str.CStr() + j)) {
                break;
            }

            if (j == str.Length() - 1) {
                return i;
            }
        }
    }

    return -1;
}

//There's probably a better way to do this

//finds all instances of find within string object and replaces them with replace, then returns itself
String& String::Replace(const String& find, const String& replace) {
    String oldStr = *this;
    
    delete[] dataPtr;
    dataPtr = new char[0];
    length = 0;

    for (int i = 0; i < oldStr.Length(); i++) {
        if (i == oldStr.Find(i, find)) {
            Append(replace);
            i += find.Length() - 1;
        }
        else {
            char* temp = new char[2];
            *temp = oldStr.CharacterAt(i);
            *(temp + 1) = 0;
            Append(temp);
            delete[] temp;
        }
    }

    return *this;
}

//asks for iostream input through console and then stores all chars in buffer into string object and returns itself
String& String::ReadFromConsole() {
    char dummyChar;
    std::cin.get(dummyChar);
    std::cin.putback(dummyChar);
    std::streamsize bufferSize = std::cin.rdbuf()->in_avail();
    
    length = bufferSize - 1;
    delete[] dataPtr;
    dataPtr = new char[length + 1];
    for (int i = 0; i < bufferSize; i++) {
        std::cin.get(*(dataPtr + i));
    }
    *(dataPtr + length) = 0;

    return *this;
}

//outputs data stored within string object to console and returns itself
String& String::WriteToConsole() {
    std::cout << dataPtr;

    return *this;
}

//returns true if lhs == rhs
bool String::operator==(const String& str) {
    return EqualTo(str);
}

bool String::operator==(const String& str) const {
    return EqualTo(str);
}

//returns false if lhs == rhs
bool String::operator!=(const String& str) {
    return !EqualTo(str);
}

//assigns value of str to string object
String& String::operator=(const String& str) {
    delete[] dataPtr;
    length = str.Length();

    dataPtr = new char[length + 1];
    for (int i = 0; i < length; i++) {
        *(dataPtr + i) = str.CharacterAt(i);
    }
    *(dataPtr + length) = 0;

    return *this;
}

//finds character stored in string object at index (e.g obj[i] returns character stored at i)
char& String::operator[](int index) {
    return CharacterAt(index);
}

const char& String::operator[](int index) const {
    return CharacterAt(index);
}

//returns true if string object comes before str in alphabetic order
//returns true if string object is same as str
//cases like ("josephine" < "joseph") will return true;
bool String::operator<(const String& str) {
    if (EqualTo(str)) {
        return true;
    }
    
    for (int i = 0; i < length && i < str.Length(); i++) {
        char a = *(dataPtr + i);
        char b = *(str.CStr() + i);
        
        if ((a < 65 || a > 90) && (a < 97 || a > 122)) {
            continue;
        }
        if ((b < 65 || b > 90) && (b < 97 || b > 122)) {
            continue;
        }

        if (a >= 97) {
            a -= 32;
        }
        if (b >= 97) {
            b -= 32;
        }

        if (a < b) {
            return true;
        }
        if (a > b) {
            return false;
        }
    }

    return true;
}

bool String::operator<(const String& str) const {
    if (EqualTo(str)) {
        return true;
    }

    for (int i = 0; i < length && i < str.Length(); i++) {
        char a = *(dataPtr + i);
        char b = *(str.CStr() + i);

        if ((a < 65 || a > 90) && (a < 97 || a > 122)) {
            continue;
        }
        if ((b < 65 || b > 90) && (b < 97 || b > 122)) {
            continue;
        }

        if (a >= 97) {
            a -= 32;
        }
        if (b >= 97) {
            b -= 32;
        }

        if (a < b) {
            return true;
        }
        if (a > b) {
            return false;
        }
    }

    return true;
}

//appends rhs to lhs and returns lhs
String& String::operator+=(const String& str) {
    Append(str);
    return *this;
}

String& String::operator+=(const char chr) {
    Append(chr);
    return *this;
}

String toString(int x) {
    bool isNegative = false;
    int totalChars = 1;

    //-2147483648 can't be multiplied by negative 1
    if (x == 0x80000000) {
        return "-2147483648";
    }

    if (x < 0) {
        isNegative = true;
        totalChars++;
        x = x * -1;
    }
    
    for (int i = 1; x / (int)pow(10, i) > 0; i++) {
        totalChars++;
    }

    // int can have a max of 11 chars (e.g -2147483648) plus room for null terminator
    char chars[12]; 
    for (int i = 0; i < totalChars; i++) {
        if (i == 0) {
            if (isNegative) {
                chars[0] = '-';
                continue;
            }
        }
        chars[i] = ((x / (int)pow(10, totalChars - 1 - i)) % 10) + 48;
    }
    chars[totalChars] = 0;

    return chars;
}

//breaks apart at numbers would go over 2146483647
//might fix later
int toInt(const String& str) {
    int finalInt = 0;
    
    if (str.Length() > 11) {
        return 0x80000000;
    }

    for (int i = 0; i < str.Length(); i++) {
        if (str[i] < 48 || str[i] > 57) {
            if (i == 0 && str[0] == '-') {
                continue;
            }

            return 0x80000000;
        }

        finalInt += ((int)str[i] - 48) * ((int)pow(10, str.Length() - 1 - i));
    }

    if (str[0] == '-') {
        finalInt = finalInt * -1;
    }

    return finalInt;
}

//returns a separate string object which stores the data of lhs + rhs
String operator+(const String& lhs, const String& rhs) {
    String newStr = lhs.CStr();
    newStr.Append(rhs);
    return newStr;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    return out << str.CStr();
}