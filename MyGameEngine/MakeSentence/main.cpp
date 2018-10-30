#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif // _DEBUG

#include "List.h"

char * MakeSentence(const char string[][256]);

void query() {
	char str2[256][256];
	int num = 0;

	std::cout << "pls type pharases. when you type done, it will proccess" << std::endl;
	while (1) {
		gets_s(str2[num], 256);
		if (str2[num][0] == '\0') break;
		num++;
	}

	char * sentence = MakeSentence(str2);

	printf("The Sentence is: %s", sentence);


	free(sentence);
}

int main(int i_argc, char ** i_argl)
{

	/*
	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};

	char * pSentence = MakeSentence(strings);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);
	*/

	query();

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}

char * MakeSentence(const char strings[][256]) {
	int j = 0;
	int k = 0;
	int numberofallocation = 0;

	while (strings[j][0] != '\0') {
		while (strings[j][k] != '\0') {
			numberofallocation++;
			k++;
		}
		k = 0;
		numberofallocation++;
		j++;
	}
	numberofallocation++;

	int arraylength = j - 1;
	char* sentence = (char*)malloc(numberofallocation);
	char* doing = sentence;

	j = 0;
	while (strings[j][0] != '\0') {
		while (strings[j][k] != '\0') {
			*doing = *(&(*strings[j]) + k);
			doing++;
			k++;
		}
		k = 0;
		if (j == arraylength) {
			*doing = '.';
			*doing ++;
			*doing = '\0';
		}
		else {
			*doing = ' ';
			doing++;
		}
		j++;
	}
	
	return sentence;
}