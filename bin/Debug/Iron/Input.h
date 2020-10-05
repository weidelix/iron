#pragma once

#include "pch.h"
#include "Core.h"
#include "Window.h"
#include "Iron/platform/Windows/WindowsWindow.h"
#include <GLFW/glfw3.h>

enum class Key
{
    No_Input          =  -2,
    Unknown           =  -1,
    Space             =  32,
    Apostrophe        =  39, 
    Comma             =  44,  
    Minus             =  45,
    Period            =  46,
    Slash             =  47,
    Num_0             =  48,
    Num_1             =  49,
    Num_2             =  50,
    Num_3             =  51,
    Num_4             =  52,    
    Num_5             =  53,    
    Num_6             =  54,    
    Num_7             =  55,    
    Num_8             =  56,    
    Num_9             =  57,    
    Semicolon         =  59, 
    Equal             =  61, 
    A                 =  65,    
    B                 =  66,    
    C                 =  67,    
    D                 =  68,    
    E                 =  69,    
    F                 =  70,    
    G                 =  71,    
    H                 =  72,    
    I                 =  73,    
    J                 =  74,    
    K                 =  75,    
    L                 =  76,    
    M                 =  77,    
    N                 =  78,    
    O                 =  79,    
    P                 =  80,    
    Q                 =  81,    
    R                 =  82,    
    S                 =  83,    
    T                 =  84,    
    U                 =  85,    
    V                 =  86,    
    W                 =  87,    
    X                 =  88,    
    Y                 =  89,    
    Z                 =  90,    
    Left_Bracket      =  91,
    Backslash         =  92,
    Right_Bracket     =  93,
    Grave_Accent      =  96,
    a                 =  97,
    b                 =  98,
    c                 =  99,
    d                 =  100,
    e                 =  101,
    f                 =  102,
    g                 =  103,
    h                 =  104,
    i                 =  105,
    j                 =  106,
    k                 =  107,
    l                 =  108,
    m                 =  109,
    n                 =  110,
    o                 =  111,
    p                 =  112,
    q                 =  113,
    r                 =  114,
    s                 =  115,
    t                 =  116,
    u                 =  117,
    v                 =  118,
    w                 =  119,
    x                 =  120,
    y                 =  121,
    z                 =  122,
    World_1           =  161,
    World_2           =  162,
    Esc               =  256,
    Enter             =  257,
    Tab               =  258,
    Backspace         =  259,
    Insert            =  260,
    Delete            =  261,
    Right             =  262,
    Left              =  263,
    Down              =  264,
    Up                =  265,
    Page_Up           =  266,
    Page_Down         =  267,
    Home              =  268,
    End               =  269,
    Caps_Lock         =  280,
    Scroll_Lock       =  281,
    Num_Lock          =  282,
    Print_Screen      =  283,
    Pause             =  284,
    F1                =  290,
    F2                =  291,
    F3                =  292,
    F4                =  293,
    F5                =  294,
    F6                =  295,
    F7                =  296,
    F8                =  297,
    F9                =  298,
    F10               =  299,
    F11               =  300,
    F12               =  301,
    F13               =  302,
    F14               =  303,
    F15               =  304,
    F16               =  305,
    F17               =  306,
    F18               =  307,
    F19               =  308,
    F20               =  309,
    F21               =  310,
    F22               =  311,
    F23               =  312,
    F24               =  313,
    F25               =  314,
    KP_0              =  320,
    KP_1              =  321,
    KP_2              =  322,
    KP_3              =  323,
    KP_4              =  324,
    KP_5              =  325,
    KP_6              =  326,
    KP_7              =  327,
    KP_8              =  328,
    KP_9              =  329,
    KP_Decimal        =  330,
    KP_Divide         =  331,
    KP_Multiply       =  332,
    KP_Substract      =  333,
    KP_Add            =  334,
    KP_Enter          =  335,
    KP_Equal          =  336,
    Left_Shift        =  340,
    Left_Control      =  341,
    Left_Alt          =  342,
    Left_Super        =  343,
    Right_Shift       =  344,
    Right_Control     =  345,
    Right_Alt         =  346,
    Right_Super       =  347,
    Menu              =  348,
    Last              =  348,
    ControlChar       =  -2
};

enum class ModKey
{
    Shift            = 0x0001,
    Control          = 0x0002,
    Alt              = 0x0004,
    Super            = 0x0008,
    Caps_Lock        = 0x0010,
    Num_Lock         = 0x0020,
};

enum class MouseButton
{
    No_Input         = -2,
    Mouse_Left       =  0,
    Mouse_Right,
    Mouse_Middle    
};

namespace Iron
{
    class IRON_API Input
    {
    private:
        std::vector<Iron::Event*>& m_events;
        WindowsWindow& m_window;

        int IsPrintable(int key);
        int IsControlChar(int key);

    public:
        Input(WindowsWindow& window)
            :m_window(window), m_events(window.GetEvents())
        { }

        /*! @brief Check is the specified key is pressed
         * 
         *! @param button mouse button to check
         * 
         *! @return returns true if the specified button is pressed
         */
        bool Mouse(enum class MouseButton button);

        /*! @brief Checks if any button in mouse is pressed
         * 
         * ! @return returns true if the specified button is pressed
         */
        int Mouse();

        /*! @brief Checks is the specified key is pressed
         * 
         *! @param key Key the to check
         * 
         *! @return returns true if the specified button is pressed
         */
        bool Key(enum class Key key);

        /*! @brief Checks if any button in keyboard is pressed
         * 
         *! @return returns the key that is pressed else returns 1 if it's a non-printable character
         */
        int Key();

        /*! @brief Checks if key combination is pressed
         * 
         *! @note Use uppercase key if using a letter
         * 
         *! @return returns true if combination is pressed
         */
        bool KeyCombination(enum class ModKey modkey, enum class Key key);
        bool KeyCombination(enum class ModKey modkey1, enum class ModKey modkey2, enum class Key key);
        bool KeyCombination(enum class ModKey modkey, enum class Key key1, enum class Key key2);
    };
}