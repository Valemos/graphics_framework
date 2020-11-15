#ifndef GL_PROGRAM_FRAMEWORK
#define GL_PROGRAM_FRAMEWORK

class ProgramInputHandler;

class Program
{
public:
	double desiredUpdateTime;
	double previousUpdateTime;

	
	Program(float fps)
	{
		desiredUpdateTime = 1.0 / fps;
		previousUpdateTime = 0.0;
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
