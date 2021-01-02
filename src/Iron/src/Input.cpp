#include "Input.hpp"

namespace Iron
{
	Input::Input(Window* window)
		:m_window(window), m_events(window->GetEvents()) 
	{ 
		
	}

	int Input::IsPrintable(int key)
	{
		if (key >= 32 && key <= 126)
			return key;
		else
			return Key::NonPrintable;
	}

	int Input::IsControlChar(int key)
	{
		return (key >= 340 && key <= 348) ? Key::NonPrintable : key;
	}

	bool Input::Mouse(enum Mouse button)
	{
		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::MouseClick)
			{
				Iron::MouseButtonPressedEvent& m = (Iron::MouseButtonPressedEvent&)*event;
				if (m.GetMouseEvent() == button)          
				{
					return true;
				}      
			}
		}
		return false;
	}

	int Input::Mouse()
	{
		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::MouseClick)
			{
				Iron::MouseButtonPressedEvent& m = (Iron::MouseButtonPressedEvent&)*event;
				int key = m.GetMouseEvent();
				
				return key;
			}
		}
		return -1;
	}

	int Input::Key()
	{
		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::KeyPress)
			{
				KeyPressEvent& m = (KeyPressEvent&)*event;                
				int key = m.GetKeyEvent();
				return IsPrintable(key);                    
			}
		}
		return Key::No_Input;
	}

	bool Input::Key(enum Key key)
	{
		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::KeyPress)
			{
				KeyPressEvent& m = (KeyPressEvent&)*event; 
				if (m.GetKeyEvent() == key) 
				{
					return true;                    
				}
			}   
		}       
		return false;
	}

	bool Input::KeyCom(enum ModKey modkey, enum Key key)
	{
		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::CombinationKeyPress)
			{
				KeyCombinationEvent& m = (KeyCombinationEvent&)*event; 
				if (m.GetModKeyEvent() == modkey && m.GetKeyEvent() == key) 
				{
					return true;                    
				}
			}
		}
		return false;
	}

	bool Input::KeyCom(enum ModKey modkey1, enum ModKey modkey2, enum Key key)
	{
		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::CombinationKeyPress)
			{
				KeyCombinationEvent& m = (KeyCombinationEvent&)*event; 
				if (m.GetModKeyEvent() == (modkey1 + modkey2) && m.GetKeyEvent() == key) 
				{
					return true;                    
				}
			}
		}
		return false;
	}

	bool Input::KeyCom(enum ModKey modkey1, enum Key key1, enum Key key2)
	{
		static bool flag1 = false;
		static bool flag2 = false;
		static double time = 0.00;

		for(auto* event : *m_events)
		{
			if (event->GetEventType() == Iron::EventType::CombinationKeyPress)
			{
				KeyCombinationEvent& m = (KeyCombinationEvent&)*event; 
				if (m.GetModKeyEvent() == modkey1 && m.GetKeyEvent() == key1) 
				{
					time = glfwGetTime();
					flag1 = true;
				}
				if (m.GetModKeyEvent() == modkey1 && m.GetKeyEvent() == key2)
				{
					if (flag1)
					{
						time = glfwGetTime();
						flag2 = true;                    
					}
				}
			}
		}
		if (glfwGetTime() - time <= 0.50)
		{   
			if (flag1 && flag2) { flag1 = false; flag2 = false; return true; }
		}
		else
		{
			flag1 = false;
			flag2 = false;
		}
		
		return false;
	}
}
