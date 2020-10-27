#include "framework/ProgramFramework.h"
#include "framework/ProgramInputHandler.h"
#include "framework/draw_objects/Figure.h"
#include "framework/draw_objects/Quad.h"
#include "framework/draw_objects/Triangle.h"


class TestProgram : public ProgramFramework
{
	Figure* task_figure_;
	
public:
	TestProgram(float fps) : ProgramFramework(fps)
	{
		task_figure_ = new Figure();
	}

	~TestProgram() override
	{
		delete task_figure_;
	}
	
	int Init(ProgramInputHandler* input_handler) override
	{
		// create test object
		task_figure_->set_fill_color(0.0, 153 / 255.f, 37 / 255.f);
		task_figure_->set_border_color(0.0, 0.0, 0.0);
		task_figure_->set_scale(1.0, 1.0);

		// points for primitives
		const Vector3
			p0 = { -0.5f, -0.5f },
			p1 = { 0.5f, -0.5f },
			p2 = { 0.f,  0.5f },
			p3 = { 1.f, 1.f };
		
		task_figure_->set_vertices({ p0, p1, p2, p3 });
		task_figure_->set_primitives({
			new Quad({ 0, 1, 2, 3 })
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

	int Finish(ProgramInputHandler*) override
	{
		return 0;
	}
};

int main()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance("../DrawLoop/framework/shaders/main_shaders.shader", 800,600);
	return program->RunProgram(new TestProgram(60.f));
}
