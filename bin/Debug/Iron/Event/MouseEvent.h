#pragma once

#include "Event.h"

namespace Iron
{
    class IRON_API MouseMoveEvent : public Event
    {
    private:
        double posX, posY;
    public:
        MouseMoveEvent(double x, double y)
            :posX(x), posY(y)
        { }

        double GetMousePositionX()
        {
            return posX;
        }

        double GetMousePositionY()
        {
            return posY;
        }

        EVENT_CLASS_TYPE(MouseMove);        
        EVENT_CLASS_CATEGORY(MouseCategory);

    };

    class IRON_API MouseScrollEvent : public Event
    {
    private:
        float xoffset, yoffset;
    public:
        MouseScrollEvent(float x, float y)
            :xoffset(x), yoffset(y)
        { }

        float GetMouseXOffset()
        {
            return xoffset;
        }

        float GetMouseYOffset()
        {
            return yoffset;
        }

        EVENT_CLASS_TYPE(MouseScroll);
        EVENT_CLASS_CATEGORY(MouseCategory);

    };

    class MouseButtonEvent : public Event
    {
    private:
        int m_button;
    protected:
        MouseButtonEvent(int button)
        :m_button(button) { }
        ~MouseButtonEvent() { }
    public:
        inline int GetMouseEvent() { return m_button; } 
        EVENT_CLASS_CATEGORY(MouseCategory | MouseButtonCategory);
    };

    class IRON_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            :MouseButtonEvent(button)
        { }

        ~MouseButtonPressedEvent() 
        { }


        EVENT_CLASS_TYPE(MouseClick)
    };

    class IRON_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            :MouseButtonEvent(button)
        {

        }

        ~MouseButtonReleasedEvent() 
        {

        }

        EVENT_CLASS_TYPE(MouseClick)
    };
} // namespace Iron
