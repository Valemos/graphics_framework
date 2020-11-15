#include "ButtonHandler.h"


ButtonHandler::ButtonHandler(Key key_type, KeyHandler function_handler)
{
	key_type_ = key_type;
	handler_ = function_handler;
}

KeyHandler ButtonHandler::GetHandler() const
{
	return handler_;
}

Key ButtonHandler::GetType() const
{
	return key_type_;
}

int ButtonHandler::Handle(void* parameters) const
{
	return handler_(parameters);
}

int ButtonHandler::Handle() const
{
	return handler_(0);
}
