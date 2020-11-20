#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Program;

enum class Key
{
	Unknown = GLFW_KEY_UNKNOWN,
	Space = GLFW_KEY_SPACE,
	Apostrophe = GLFW_KEY_APOSTROPHE,
	Comma = GLFW_KEY_COMMA,
	Minus = GLFW_KEY_MINUS,
	Period = GLFW_KEY_PERIOD,
	Slash = GLFW_KEY_SLASH,
	Number0 = GLFW_KEY_0,
	Number1 = GLFW_KEY_1,
	Number2 = GLFW_KEY_2,
	Number3 = GLFW_KEY_3,
	Number4 = GLFW_KEY_4,
	Number5 = GLFW_KEY_5,
	Number6 = GLFW_KEY_6,
	Number7 = GLFW_KEY_7,
	Number8 = GLFW_KEY_8,
	Number9 = GLFW_KEY_9,
	Semicolon = GLFW_KEY_SEMICOLON,
	Equal = GLFW_KEY_EQUAL,
	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z,
	Left_bracket = GLFW_KEY_LEFT_BRACKET,
	Backslash = GLFW_KEY_BACKSLASH,
	Right_bracket = GLFW_KEY_RIGHT_BRACKET,
	Grave_accent = GLFW_KEY_GRAVE_ACCENT
};


typedef int (*KeyHandler) (Program*);
typedef bool ButtonState;

class ButtonHandler
{
	Key key_type_ = Key::Unknown;
	KeyHandler handler_;
	ButtonState button_state_;

public:
	ButtonHandler(Key key_type, KeyHandler function_handler);

	ButtonState GetButtonState() const;
	void SetButtonState(ButtonState state);
	KeyHandler GetHandler() const;
	Key GetType() const;

	int Handle(Program* program) const;
	int Handle() const;
};
