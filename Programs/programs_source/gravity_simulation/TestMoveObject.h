#ifndef PROGRAM_MOVE_OBJECT_FUNCTIONS
#define PROGRAM_MOVE_OBJECT_FUNCTIONS
  
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>

#include "Program.h"
#include "ProgramInputHandler.h"
#include "UniverseConstants.h"
#include "Vector3.h"
#include "objects/CelestialBody.h"

class TestProgram : public Program
{
	const float moveSpeed = 0.1f;
	Vector3 position;
	CelestialBody* testBody = nullptr;

public:
	TestProgram(float fps) : Program(fps)
	{
	}

	int Init() override
	{
		testBody = new CelestialBody("Test", { 0.0, 0.0, 1.0 }, new UniverseConstants{ 0.1f, 0.1f });
		
		ProgramInputHandler::renderer.SetGlobalScale({ 1.0 / 20, 1.0 / 20, 1.0 });

		position = { 0.f, 0.f };

		// set background color
		glClearColor(1.0, 116 / 255.f, 0.0, 1.0);
		return 0;
	}

	int Step() override
	{
		// compare with zero
		if (abs(ProgramInputHandler::keyboard_move_dir->x) > VECTOR_FLOAT_ACCURACY ||
			abs(ProgramInputHandler::keyboard_move_dir->y) > VECTOR_FLOAT_ACCURACY)
		{
			// calculate projection on direction vector
			position += *ProgramInputHandler::keyboard_move_dir * moveSpeed;
			testBody->SetPosition(position);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		testBody->Draw(ProgramInputHandler::renderer);

		std::cout << testBody->GetPosition().x << " - " << testBody->GetPosition().y << std::endl;
		return 0;
	}
};

#endif
