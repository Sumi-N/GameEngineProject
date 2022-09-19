#include "Assert.h"

#ifdef ENGINE_PLATFORM_WINDOWS

bool DEBUG::AssertionCheckPlatoformSpecific(std::ostringstream& io_message, bool& i_ignorethisinthefuture)
{

	io_message << "\n\n"
		"Do you want to break into the debugger?"
		" Choose \"Yes\" to break, \"No\" to continue, or \"Cancel\" to disable this assertion until the program exits.";
	const auto result = MessageBoxA(GetActiveWindow(), io_message.str().c_str(), "Assertion Failed!", MB_YESNOCANCEL);
	if ((result == IDYES)
		// MessageBox() returns 0 on failure; if this happens the code breaks rather than trying to diagnose why
		|| (result == 0))
	{
		return true;
	}
	else
	{
		if (result == IDCANCEL)
		{
			i_ignorethisinthefuture = true;
		}
		return false;
	}
}

#endif // ENGINE_PLATFORM_WINDOWS