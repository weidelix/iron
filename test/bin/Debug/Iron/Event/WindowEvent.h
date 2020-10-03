#pragma once

#include "pch.h"
#include "Iron/Core.h"
#include "Iron/Event/Event.h"

namespace Iron
{
    class IRON_API WindowResizeEvent : public Event
    {
    private:
        unsigned int width, height;
    public:
        WindowResizeEvent(unsigned int w, unsigned int h) 
            :width(w), height(h) { } 

        ~WindowResizeEvent() { }

        EVENT_CLASS_TYPE(WindowResize);
        EVENT_CLASS_CATEGORY(WindowCategory);
    };

    class IRON_API WindowMoveEvent : public Event
    {
    private:
        /* data */
    public:
        WindowMoveEvent(/* args */) { } 
        ~WindowMoveEvent() { }

        EVENT_CLASS_TYPE(WindowMove);
        EVENT_CLASS_CATEGORY(WindowCategory);
    };
    
    class IRON_API WindowCloseEvent : public Event
    {
    private:
        
    public:
        WindowCloseEvent() { }
        ~WindowCloseEvent() { }

        EVENT_CLASS_TYPE(WindowClose);
        EVENT_CLASS_CATEGORY(WindowCategory);
    };
    
    
} // namespace Iron
