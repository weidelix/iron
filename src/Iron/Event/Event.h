#pragma once

#include "Iron/Core.h"
#include "pch.h"

namespace Iron
{
    enum class EventType
    {
        None,
        KeyPress, KeyRelease, KeyRepeat, // Key events
        MouseClick, MouseRelease, MouseMove, MouseScroll, // Mouse events
        WindowResize, WindowFocus, WindowLostFocus, WindowMove, WindowMinimized, WindowClose, // Window events
        AppTick, AppUpdate, AppRender, // App events
    };

    enum EventCategory
    {
        None                =      0 ,
        WindowCategory      =  BIT(0),
        ApplicationCategory =  BIT(1),
        InputCategory       =  BIT(2),
        KeyboardCategory    =  BIT(3),
        ControllerCategory  =  BIT(4),
        MouseCategory       =  BIT(5),
        MouseButtonCategory =  BIT(6)
    };

    #define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
                                    virtual EventType GetEventType() const override { return GetStaticType(); }\
                                    virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }    

    class IRON_API Event
    {
        friend class EventDispatcher;
    protected:
        bool m_handled = false;
    public:
        virtual int GetCategoryFlags() const = 0;
        virtual const char* GetName() const = 0;
        virtual EventType GetEventType() const = 0;
        virtual std::string ToString() { return GetName(); }

        inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFunc = std::function<bool(T&)>;
    
    private: 
        Event& m_event;
    
    public:
        EventDispatcher(Event& event)
            :m_event(event)
        { }

        //? Should I call this for every type of event?
        template<typename T>
        void Dispatch(EventFunc<T>& func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.m_handled = func(*(T*)&m_event);
                return true;
            }
            return false;
            }
    };
}