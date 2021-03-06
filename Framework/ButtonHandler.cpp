#include "ButtonHandler.h"
#include "Program.h"


ButtonHandler::ButtonHandler(Key key_type, KeyHandler function_handler):
	key_type_(key_type), handler_(function_handler), button_state_(false)
{
}

ButtonState ButtonHandler::GetButtonState() const
{
	return button_state_;
}

void ButtonHandler::SetButtonState(ButtonState state)
{
	button_state_ = state;
}

KeyHandler ButtonHandler::GetHandler() const
{
	return handler_;
}

Key ButtonHandler::GetType() const
{
	return key_type_;
}

Program::ProgramState ButtonHandler::Handle(Program* program) const
{
	return handler_(program);
}

Program::ProgramState ButtonHandler::Handle() const
{
	return handler_(nullptr);
}
