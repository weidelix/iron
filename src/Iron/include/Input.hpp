#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Window.hpp"
#include "Platform/Windows/WindowsWindow.hpp"
#include <GLFW/glfw3.h>

enum Key
{
	NonPrintable      =  -2,
	Unknown           =  -1,
	No_Input          =   0,
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
	Last              =  348
};

enum ModKey
{
	M_Shift           = 0x0001,
	M_Control         = 0x0002,
	M_Alt             = 0x0004,
	M_Super           = 0x0008,
	M_Caps_Lock       = 0x0010,
	M_Num_Lock        = 0x0020,
};

enum Mouse
{
	No_Click          = -1,
	Mouse_Left,
	Mouse_Right,
	Mouse_Middle    
};

namespace Iron
{
	class IRON_API Input
	{
	private:
		Window* m_window;
		std::vector<Iron::Event*>* m_events;

		 int IsPrintable(int key);
		 int IsControlChar(int key);

	public:
		Input(Window* window);
		~Input() = default;

		/**
		 * @brief Check is the specified key is pressed
		 * 
		 * @param button mouse button to check
		 * 
		 * @return returns true if the specified button is pressed
		 */
		bool Mouse(enum Mouse button);

		/**
		 * @brief Checks if any button in mouse is pressed
		 * 
		 * @return returns true if the specified button is pressed
		 */
		int Mouse();

		/**
		 * @brief Checks is the specified key is pressed
		 * 
		 * @param key Key the to check
		 * 
		 * @return returns true if the specified button is pressed
		 */
		bool Key(enum Key key);

		/**
		 * @brief Checks if any button in keyboard is pressed
		 * 
		 * @return returns the key that is pressed else returns 1 if it's a non-printable character
		 */
		int Key();

		/** 
		 * @brief Checks if key combination is pressed
		 * 
		 * -Use uppercase key if using a letter-
		 *
		 * @param modkey control key to check
		 * @param key alphanumeric key to check
		 * 
		 * @return returns true if combination is pressed
		 */
		bool KeyCom(enum ModKey modkey, enum Key key);

		/** 
		 * @brief Checks if key combination is pressed
		 * 
		 * -Use uppercase key if using a letter-
		 * 
		 * @param modkey1 first control key to check
		 * @param modkey2 second control key to check
		 * @param key alphanumeric key to check
		 *
		 * @return returns true if combination is pressed
		 */
		bool KeyCom(enum ModKey modkey1, enum ModKey modkey2, enum Key key);

		/**
		 *  @brief Checks if key combination is pressed
		 * 
		 * @note Use uppercase key if using a letter
		 * @warning This is an experimental feature and may not be included in the final product 
		 * 
		 * @param modkey control key to check
		 * @param key1 first alphanumeric key to check
		 * @param key2 second alphanumeric key to check
		 * 
		 * @return returns true if combination is pressed
		 */ 
		bool KeyCom(enum ModKey modkey, enum Key key1, enum Key key2);
	};
}
