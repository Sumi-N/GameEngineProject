#pragma once
#include <iostream>

class CharacterString
{
public:
	CharacterString();
	CharacterString(const char *);
	CharacterString(const CharacterString &);
	~CharacterString();

	CharacterString & operator=(const char *);
	CharacterString & operator=(const CharacterString &);

	char * String();
	void Random(int);
private:
	char * head;
	char * elements;
	int length = 0; //character length
};

inline CharacterString::CharacterString()
{
}

inline CharacterString::CharacterString(const char * string)
{
	char * arg = const_cast<char *>(string);
	while (* arg != '\0') {
		length++;
		arg++;
	}
	arg = const_cast<char *>(string);

	elements = new char[length + 1];
	head = elements;

	for (auto i = 0; i < length; i++) {
		elements[i] = *arg;
		arg++;
	}
	elements[length] = '\0';
}

inline CharacterString::CharacterString(const CharacterString & characterstring)
{
	char  * arg = const_cast<char *>(characterstring.elements);
	while (*arg != '\0') {
		length++;
		arg++;
	}
	arg = const_cast<char *>(characterstring.elements);

	elements = new char[length + 1];
	head = elements;

	for (auto i = 0; i < length; i++) {
		elements[i] = *arg;
		arg++;
	}
	elements[length] = '\0';
}

inline CharacterString::~CharacterString()
{
	delete head;
}

inline CharacterString & CharacterString::operator=(const CharacterString & characterstring)
{
	delete head;
	char  * arg = const_cast<char *>(characterstring.elements);
	while (*arg != '\0') {
		length++;
		arg++;
	}
	arg = const_cast<char *>(characterstring.elements);

	elements = new char[length + 1];
	head = elements;

	for (auto i = 0; i < length; i++) {
		elements[i] = *arg;
		arg++;
	}
	elements[length] = '\0';

	return *this;
}

inline CharacterString & CharacterString::operator=(const char * string)
{
	delete head;
	char  * arg = const_cast<char *>(string);
	while (*arg != '\0') {
		length++;
		arg++;
	}
	arg = const_cast<char *>(string);

	elements = new char[length + 1];
	head = elements;

	for (auto i = 0; i < length; i++) {
		elements[i] = *arg;
		arg++;
	}
	elements[length] = '\0';

	return *this;
}

inline char * CharacterString::String()
{
	return elements;
}

inline void CharacterString::Random(int characterlength)
{
	delete head;
	char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	elements = new char[characterlength + 1];
	head = elements;
	length = characterlength;

	for (auto i = 0; i < length; i++) {
		elements[i] = characters[rand() % (sizeof(characters) - 1)];
	}
	elements[length] = '\0';
}
