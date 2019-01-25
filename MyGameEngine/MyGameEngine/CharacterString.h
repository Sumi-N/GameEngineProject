#pragma once
class CharacterString
{
public:
	CharacterString();
	CharacterString(const char * string);
	CharacterString(const char & string);
	~CharacterString();
	char * String();

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

inline CharacterString::CharacterString(const char & string)
{
	char  * arg = const_cast<char *>(&string);
	while (*arg != '\0') {
		length++;
		arg++;
	}
	arg = const_cast<char *>(&string);

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

inline char * CharacterString::String()
{
	return elements;
}
