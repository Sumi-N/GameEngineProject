#pragma once

#include "Define.h"

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowDefocus, WindowMoved,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, 
};

enum EventCategoty
{
	None     = 0,
	WindowEvent   = BIT(0),
	KeyboardEvent = BIT(1),
	MouseEvent    = BIT(2),
};

#define EVENT_CLASS_MACRO(type, category)   static EventType GetStaticType()               {return EventType::type;}\
											       EventType GetEventType() const override {return GetStaticType();}\
                                                   int       GetCategory()  const override {return category;}

class Event
{
public: 
	virtual ~Event() = default;

	bool Handled = false;

	virtual EventType GetEventType() const = 0;
	virtual int GetCategory() const = 0;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event): m_event(event){};

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_event.GetEventType() == T::GetStaticType())
		{
			m_event.Handled = func(static_cast<T&>(m_event));
			return true;
		}

		return false;
	}

private:
	Event& m_event;
};




