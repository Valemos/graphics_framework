#ifndef GL_PROGRAM_FRAMEWORK
#define GL_PROGRAM_FRAMEWORK

class ProgramInputHandler;


class ProgramFramework
{
public:
	double desiredUpdateTime;
	double previousUpdateTime;

	
	ProgramFramework(float fps)
	{
		desiredUpdateTime = 1.0 / fps;
		previousUpdateTime = 0.0;
	}
	
	virtual ~ProgramFramework() = default;
	virtual int Init(ProgramInputHandler*) = 0;
	virtual int Step(ProgramInputHandler*) = 0;
	virtual int Finish(ProgramInputHandler*) { return 0; };
};

#endif
