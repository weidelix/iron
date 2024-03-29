#pragma once

#include "Event/Event.hpp"

namespace Iron
{
	class IRON_API WindowResizeEvent : public Event
	{
	private:
		unsigned int width, height;
	public:
		WindowResizeEvent(unsigned int w, unsigned int h) 
			:width(w), height(h) 
		{ } 
		
		~WindowResizeEvent() override { }
		float GetWidth() { return width; }
		float GetHeight() { return height; }
		EVENT_CLASS_TYPE(EventType::WindowResize);
		EVENT_CLASS_CATEGORY(WindowCategory);
	};
	
	class IRON_API WindowMoveEvent : public Event
	{
	private:
	public:
		WindowMoveEvent() { } 
		~WindowMoveEvent() override { }
		
		EVENT_CLASS_TYPE(EventType::WindowMove);
		EVENT_CLASS_CATEGORY(WindowCategory);
	};
	
	class IRON_API WindowCloseEvent : public Event
	{
	private:		
	public:
		WindowCloseEvent() { }
		~WindowCloseEvent() override { }
		EVENT_CLASS_TYPE(EventType::WindowClose);
		EVENT_CLASS_CATEGORY(WindowCategory);
	};	
}