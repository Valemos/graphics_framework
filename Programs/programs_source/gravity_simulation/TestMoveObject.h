#ifndef PROGRAM_MOVE_OBJECT_FUNCTIONS
#define PROGRAM_MOVE_OBJECT_FUNCTIONS
  
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>

#include "ProgramFramework.h"
#include "ProgramInputHandler.h"
#include "UniverseConstants.h"
#include "Vector3.h"
#include "objects/CelestialBody.h"

class TestProgram : public ProgramFramework
{
	const float moveSpeed = 0.1f;
	Vector3 position;
	CelestialBody* testBody = nullptr;

public:
	TestProgram(float fps) : ProgramFramework(fps)
	{
		testBody = new CelestialBody("Test", { 0.0, 0.0, 1.0 }, new UniverseConstants{ 0.1f, 0.1f }, 10, 9.8);
	}

	int Init(ProgramInputHandler* input_handler) override
	{
		testBody->updateGlBuffer();

		ProgramInputHandler::renderer.SetScale({ 1.0 / 20, 1.0 / 20, 1.0 });

		position = { 0.f, 0.f };

		// set background color
		glClearColor(1.0, 116 / 255.f, 0.0, 1.0);
		return 0;
	}

	int Step(ProgramInputHandler* input_handler) override
	{
		// compare with zero
		if (abs(ProgramInputHandler::keyboardMoveDir->x) > VECTOR_FLOAT_ACCURACY ||
			abs(ProgramInputHandler::keyboardMoveDir->y) > VECTOR_FLOAT_ACCURACY)
		{
			// calculate projection on direction vector
			position += *ProgramInputHandler::keyboardMoveDir * moveSpeed;
			testBody->SetPosition(position);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		testBody->draw(ProgramInputHandler::renderer);

		std::cout << testBody->Position().x << " - " << testBody->Position().y << std::endl;
		return 0;
	}
};

#endif
