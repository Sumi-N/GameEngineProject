#pragma once
#include "Event.h"

namespace Tempest
{

	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(VirtualKey i_vkey, unsigned int i_repeatcount) :vkey(i_vkey), repeatcount(i_repeatcount)
		{
		};

		VirtualKey GetButton()
		{
			return vkey;
		}

		EVENT_CLASS_MACRO(KeyPressed, KeyboardEvent)

	private:
		VirtualKey vkey;
		unsigned int repeatcount;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(VirtualKey i_vkey) :vkey(i_vkey)
		{
		};

		VirtualKey GetButton()
		{
			return vkey;
		}

		EVENT_CLASS_MACRO(KeyReleased, KeyboardEvent)

	private:
		VirtualKey vkey;
	};

}