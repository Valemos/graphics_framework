#pragma once

#include "../framework/ProgramFramework.h"
#include "../framework/draw_objects/Figure2D.h"
#include "../framework/draw_objects/Quad.h"
#include "../framework/draw_objects/Triangle.h"


class Test2DProgram : public ProgramFramework
{
	Figure2D* task_figure_;

public:
	Test2DProgram(float fps) : ProgramFramework(fps)
	{
		task_figure_ = new Figure2D();
	}

	~Test2DProgram() override
	{
		delete task_figure_;
	}

	int Init(ProgramInputHandler* input_handler) override
	{
		// create test object
		task_figure_->name = "Test";
		task_figure_->set_fill_color(0.0, 153 / 255.f, 37 / 255.f);
		task_figure_->set_border_color(0.0, 0.0, 0.0);
		task_figure_->set_scale(1.0, 1.0);

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

		// background color
		glClearColor(1.0, 116 / 255.f, 0.0, 1.0);
		return 0;
	}

	int Step(ProgramInputHandler* input_handler) override
	{
		// Draw test object
		glClear(GL_COLOR_BUFFER_BIT);
		task_figure_->Draw(ProgramInputHandler::renderer, Vector3());
		return 0;
	}
};
