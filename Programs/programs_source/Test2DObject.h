#pragma once

#include "Program.h"
#include "draw_objects/Figure2D.h"
#include "draw_objects/Quad.h"
#include "draw_objects/Triangle.h"


class Test2DProgram : public Program
{
	Figure2D* task_figure_;

public:
	Test2DProgram(float fps) : Program(fps)
	{
		task_figure_ = new Figure2D();
	}

	~Test2DProgram() override
	{
		delete task_figure_;
	}

	int Init() override
	{
		// create test object
		task_figure_->name = "Test";
		task_figure_->SetFillColor(0.0, 153 / 255.f, 37 / 255.f);
		task_figure_->SetBorderColor(0.0, 0.0, 0.0);
		task_figure_->SetScale(1.0, 1.0);

		// points for primitives
		const Vector3
			p0 = { -0.5f, -0.5f },
			p1 = { 0.5f, -0.5f },
			p2 = { 0.5f, 0.5f },
			p3 = { 1.f, 0.5f },
			p4 = { -1.f, 1.f };

		task_figure_->InitBuffers(
			{ p0, p1, p2, p3, p4 },
			{
				new Quad({ 0, 2, 3, 1 }),
				new Triangle({ 0, 2, 4 })
			});

		task_figure_->Position() = Vector3{0, 0, 0};
		
		// background color
		ProgramInputHandler::SetClearColor(255, 116, 0, 255);
		return 0;
	}

	int Step() override
	{
		// Draw test object
		ProgramInputHandler::ClearScreen();
		task_figure_->Draw(ProgramInputHandler::renderer);
		return 0;
	}
};
