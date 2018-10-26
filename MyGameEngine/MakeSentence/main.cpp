#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif // _DEBUG

#include "List.h"

char * MakeSentence(const char **);

int main(int i_argc, char ** i_argl)
{
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

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}

char * MakeSentence(const char ** strings) {
	int j = 0;
	int k = 0;
	int numberofallocation = 0;

	while (&*strings[j] != NULL) {
		while (*(&(*strings[j]) + k) != '\0') {
			numberofallocation++;
			k++;
		}
		k = 0;
		numberofallocation++;
		j++;
	}

	int arraylength = j - 1;
	char* sentence = (char*)malloc(numberofallocation);

	char* doing = sentence;

	j = 0;
	while (&*strings[j] != NULL) {
		while (*(&(*strings[j]) + k) != '\0') {
			*doing = *(&(*strings[j]) + k);
			doing++;
			k++;
		}
		k = 0;
		if (j == arraylength) {
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