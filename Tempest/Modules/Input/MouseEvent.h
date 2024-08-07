#pragma once
#include "Event.h"

namespace Tempest
{

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : xpos(x), ypos(y)
		{
		};

		float GetX() const
		{
			return xpos;
		}
		float GetY() const
		{
			return ypos;
		}

		EVENT_CLASS_MACRO(MouseMoved, MouseEvent)

	private:
		float xpos, ypos;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) : xpos(x), ypos(y)
		{
		};

		EVENT_CLASS_MACRO(MouseScrolled, MouseEvent)

	private:
		float xpos, ypos;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(VirtualKey i_vkey) : vkey(i_vkey)
		{
		};

		VirtualKey GetMouseButton() const
		{
			return vkey;
		}

		EVENT_CLASS_MACRO(MouseButtonPressed, MouseEvent)

	private:
		VirtualKey vkey;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(VirtualKey i_vkey) : vkey(i_vkey)
		{
		};

		VirtualKey GetMouseButton() const
		{
			return vkey;
		}

		EVENT_CLASS_MACRO(MouseButtonReleased, MouseEvent)

	private:
		VirtualKey vkey;
	};

}
