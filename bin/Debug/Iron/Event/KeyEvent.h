#include "Iron/Core.h"
#include "Iron/Event/Event.h"
#include "pch.h"

namespace Iron
{
    class IRON_API KeyPressEvent : public Event
    {
    private:
        int m_key;
        bool m_isRepeated;
    public:
        KeyPressEvent(int key, bool isRepeated)
            :m_key(key), m_isRepeated(isRepeated)
         { }
        inline int GetKeyEvent() { return m_key; }
        inline bool IsKeyRepeated() { return m_isRepeated; }
        inline void SetKeyRepeated(bool val) { m_isRepeated = val; }

        EVENT_CLASS_TYPE(KeyPress);
        EVENT_CLASS_CATEGORY(InputCategory | KeyboardCategory);
    };

    class IRON_API KeyReleaseEvent : public Event
    {
    private:
        int m_key;
    public:
        KeyReleaseEvent(int key)
            :m_key(key)
         { }
        inline int GetKeyEvent() { return m_key; }

        EVENT_CLASS_TYPE(KeyRelease);
        EVENT_CLASS_CATEGORY(InputCategory | KeyboardCategory);
    };
} // namespace Iron
