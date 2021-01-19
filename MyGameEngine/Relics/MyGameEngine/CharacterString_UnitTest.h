#pragma once
#include "CharacterString.h"
#include <assert.h>

//Disable the original heap manager in order to execute this unit test properly
namespace UnitTest {

	void CopyConstructorTest(CharacterString,CharacterString &);

	bool CharacterString_UnitTest() {

		//String() function  
		CharacterString test1 = CharacterString("test");
		printf("The oroginal string is \"%s\"\n", test1.String());

		//Copy Constructor
		CopyConstructorTest(test1, test1);

		//Destructor
		CharacterString * test2 = new CharacterString("what's up?");
		CharacterString * test3 = test2;
		delete test2;
		
		//Assignment operator for CharacterString class
		//Assignment operator for char *
		CharacterString test4 = CharacterString("hello");
		CharacterString test5 = CharacterString();
		test5 = test4;
		test4 = "I'm the god";
		printf("The assigned string for Character String is \"%s\"\n", test5.String());
		printf("The assigned string for char * is \"%s\"\n", test4.String());

		//Random() function
		test4.Random(20);
		test5.Random(10);
		printf("The random String is \"%s\"\n", test4.String());
		printf("The random string is \"%s\"\n", test5.String());

		return true;
	}

	void CopyConstructorTest(CharacterString i_string, CharacterString & i_string2) {
		printf("The coppied string is \"%s\"\n", i_string.String());
		printf("The original address is 0x%p\n", i_string.String());
		printf("The coppied address is 0x%p\n", i_string2.String());
		assert(&i_string != &i_string2);
		return;
	}
}