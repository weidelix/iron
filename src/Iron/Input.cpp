#include "Input.h"

namespace Iron
{
    inline int Input::IsPrintable(int key)
    {
        if (key >= 32 && key <= 126)
            return key;
        else
            return false;
    }

    inline int Input::IsControlChar(int key)
    {
        return (key >= 340 && key <= 348) ? (int)Key::ControlChar : key;
    }

    bool Input::Mouse(enum class MouseButton button)
    {
        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::MouseClick)
            {
                Iron::MouseButtonPressedEvent& m = (Iron::MouseButtonPressedEvent&)*event;
                if (m.GetMouseEvent() == (int)button)          
                {
                    return true;
                }      
            }
        }
        return false;
    }

    int Input::Mouse()
    {
        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::MouseClick)
            {
                Iron::MouseButtonPressedEvent& m = (Iron::MouseButtonPressedEvent&)*event;
                int key = m.GetMouseEvent();
                
                return key;
            }
        }
        return (int)MouseButton::No_Input;
    }

    int Input::Key()
    {
        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::KeyPress)
            {
                KeyPressEvent& m = (KeyPressEvent&)*event;                
                int key = m.GetKeyEvent();
                return IsControlChar(IsPrintable((int)key));                    
            }
        }
        return (int)Key::No_Input;
    }

    bool Input::Key(enum class Key key)
    {
        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::KeyPress)
            {
                KeyPressEvent& m = (KeyPressEvent&)*event; 
                if (m.GetKeyEvent() == (int)key) 
                {
                    return true;                    
                }
            }   
        }       
        return false;
    }

    bool Input::KeyCombination(enum class ModKey modkey, enum class Key key)
    {
        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::CombinationKeyPress)
            {
                KeyCombinationEvent& m = (KeyCombinationEvent&)*event; 
                if (m.GetModKeyEvent() == (int)modkey && m.GetKeyEvent() == (int)key) 
                {
                    return true;                    
                }
            }
        }
        return false;
    }

    bool Input::KeyCombination(enum class ModKey modkey1, enum class ModKey modkey2, enum class Key key)
    {
        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::CombinationKeyPress)
            {
                KeyCombinationEvent& m = (KeyCombinationEvent&)*event; 
                if (m.GetModKeyEvent() == ((int)modkey1 + (int)modkey2) && m.GetKeyEvent() == (int)key) 
                {
                    return true;                    
                }
            }
        }
        return false;
    }

    bool Input::KeyCombination(enum class ModKey modkey1, enum class Key key1, enum class Key key2)
    {
        static bool flag1 = false;
        static bool flag2 = false;
        static double time = 0.00;

        for(auto* event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::CombinationKeyPress)
            {
                KeyCombinationEvent& m = (KeyCombinationEvent&)*event; 
                if (m.GetModKeyEvent() == (int)modkey1 && m.GetKeyEvent() == (int)key1) 
                {
                    time = glfwGetTime();
                    flag1 = true;
                }
                if (m.GetModKeyEvent() == (int)modkey1 && m.GetKeyEvent() == (int)key2)
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