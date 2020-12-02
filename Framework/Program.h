#ifndef GL_PROGRAM_FRAMEWORK
#define GL_PROGRAM_FRAMEWORK

class ProgramInputHandler;

#include <string>

class Program
{
	
public:
	std::string window_name;

	enum ProgramState{
		program_continue=0,
		program_restart,
		program_finish
	};

	double desired_update_time;
	double previous_update_time;

	explicit Program(float fps, std::string& name = (std::string &) "Program"): window_name(name)
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
		return program_finish;
	}
};

#endif
