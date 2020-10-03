#include "Input.h"

namespace Iron
{
    bool Input::Mouse(int button)
    {
        int i = 0;
        for(auto& event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::MouseClick)
            {
                Iron::MouseButtonPressedEvent& m = (Iron::MouseButtonPressedEvent&)*event;
                if (m.GetMouseEvent() == button)
                {   
                    delete event;
                    m_events.erase(m_events.begin() + i);
                    return true;
                }
            }
            i++;
        }
        return false;
    }

    int Input::Mouse()
    {
        int i = 0;
        for(auto& event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::MouseClick)
            {
                Iron::MouseButtonPressedEvent& m = (Iron::MouseButtonPressedEvent&)*event;
                delete event;
                m_events.erase(m_events.begin() + i);
                return m.GetMouseEvent();
            }
            i++;
        }
        return 0;
    }

    int Input::Key()
    {
        int i = 0;
        for(auto& event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::KeyRelease)
            {
                KeyReleaseEvent& M = (KeyReleaseEvent&)*event;
                delete event;
                m_events.erase(m_events.begin() + i);
                return 0;
            }

            if (event->GetEventType() == Iron::EventType::KeyPress)
            {
               KeyPressEvent& m = (KeyPressEvent&)*event;                
                int key = m.GetKeyEvent();
                delete event;
                m_events.erase(m_events.begin() + i);
                return key;                    
                
            }
            i++;
        }
        return 0;
    }

    bool Input::Key(int key)
    {
        int i = 0;
        for(auto& event : m_events)
        {
            if (event->GetEventType() == Iron::EventType::KeyRelease)
            {
                KeyReleaseEvent& M = (KeyReleaseEvent&)*event;
                delete event;
                m_events.erase(m_events.begin() + i);
                return 0;
            }

            if (event->GetEventType() == Iron::EventType::KeyPress)
            {
                KeyPressEvent& m = (KeyPressEvent&)*event; 
                if (m.GetKeyEvent() == key) 
                {
                    delete event;
                    m_events.erase(m_events.begin() + i);
                    return key;                    
                }
                delete event;
                m_events.erase(m_events.begin() + i);
            }
            i++;
        }
        return 0;
    }
}