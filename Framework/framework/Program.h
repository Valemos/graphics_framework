#ifndef GL_PROGRAM_FRAMEWORK
#define GL_PROGRAM_FRAMEWORK

class ProgramInputHandler;

#include <string>

class Program
{
	
public:
	std::string window_name;
	static const int program_continue = 0;
	static const int program_restart = 1;
	static const int program_finish = 2;

	double desired_update_time;
	double previous_update_time;

	Program(float fps, std::string name = "Program"): window_name(name)
	{
		desired_update_time = 1.0 / fps;
		previous_update_time = 0.0;
	}
	
	virtual ~Program() = default;
	virtual int Init() = 0;
	virtual int Step() = 0;

	// "Finish" is optional
	virtual int Finish()
	{
		return 0;
	}
};

#endif
