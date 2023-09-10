#include "Assert.h"


bool LOG::AssertionCheck(const unsigned int i_linenumber, const char* const i_file, const char* const i_message, bool& i_ignorethisinthefuture, ...)
{
	std::ostringstream message;
	{
		message << "An assertion failed on line" << i_linenumber << "of" << i_file;
		constexpr size_t buffersize = 512;
		char buffer[buffersize];
		int formattingresult;
		{
			va_list insertions;
			va_start(insertions, i_message);
			formattingresult = vsnprintf(buffer, buffersize, i_message, insertions);
			if (formattingresult != 0)
			{
				message << ":\n\n";
				if (formattingresult > 0)
				{
					message << buffer;
					if (formattingresult >= buffersize)
					{
						message << "\n\n"
							"(The internal buffer of size " << buffersize
							<< " was not big enough to hold the formatted message of length " << (formattingresult + 1) << ")";
					}
				}
				else
				{
					message << "An encoding error occurred! The unformatted message is: \"" << i_message << "\"!";
				}
			}
			else
			{
				message << "!";
			}
		}
	}
	return AssertionCheckPlatoformSpecific(message, i_ignorethisinthefuture);
}
