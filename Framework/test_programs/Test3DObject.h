#pragma once

#include "../framework/ProgramFramework.h"

class Test3DObjectsProgram : public ProgramFramework
{
public:
	explicit Test3DObjectsProgram(float fps)
		: ProgramFramework(fps)
	{

	}

	int Init(ProgramInputHandler*) override
	{
		// create vertices for primitives


		// Load them to GL buffer
		
		return 0;
	}

	int Step(ProgramInputHandler*) override
	{

		return 0;
	}
};
