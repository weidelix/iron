#pragma once

#include "Event/Event.hpp"

namespace Iron
{
	class IRON_API KeyPressEvent : public Event
	{
	private:
		int m_key;
		bool m_isRepeated;
	public:
		KeyPressEvent(int key, bool isRepeated)
				:m_key(key), m_isRepeated(isRepeated) { }
		~KeyPressEvent() override { }
		inline int GetKeyEvent() { return m_key; }
		inline bool IsKeyRepeated() { return m_isRepeated; }
		inline void SetKeyRepeated(bool val) { m_isRepeated = val; }
		EVENT_CLASS_TYPE(EventType::KeyPress);
		EVENT_CLASS_CATEGORY(InputCategory | KeyboardCategory);
	};

	class IRON_API KeyCombinationEvent : public Event
	{
	private:
		int m_modkey;
		int m_key;
		bool m_isRepeated;
	public:
		KeyCombinationEvent(int key, int modkey)
				:m_modkey(modkey), m_key(key) { }
		~KeyCombinationEvent() override { }
		inline int GetKeyEvent() { return m_key; }
		inline int GetModKeyEvent() { return m_modkey; }
		inline bool IsKeyRepeated() { return m_isRepeated; }
		inline void SetKeyRepeated(bool val) { m_isRepeated = val; }
		EVENT_CLASS_TYPE(EventType::CombinationKeyPress);
		EVENT_CLASS_CATEGORY(InputCategory | KeyboardCategory);
	};
	
	class IRON_API KeyReleaseEvent : public Event
	{
	private:
		int m_key;
	public:
		KeyReleaseEvent(int key)
			:m_key(key) { }
		~KeyReleaseEvent() override { }
		inline int GetKeyEvent() { return m_key; }
		EVENT_CLASS_TYPE(EventType::KeyRelease);
		EVENT_CLASS_CATEGORY(InputCategory | KeyboardCategory);
	};
}
