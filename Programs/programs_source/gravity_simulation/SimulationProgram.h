#ifndef PROGRAM_SIMULATION_FUNCTIONS
#define PROGRAM_SIMULATION_FUNCTIONS

class UniverseConstants;

#include "Program.h"
#include "ProgramInputHandler.h"
#include "Simulation.h"
#include "vector_editor/VectorFigure.h"


class SimulationProgram : public Program
{
	int step_count_;
	int current_step_ = 0;
	UniverseConstants constants_;
	Simulation* simulation_;
	float planets_density_;

	// set speed of one celestial body
	CelestialBody* controlled_object_;
	VectorFigure* vector_speed_;

	// state function depends on inner state of 
	
	static bool s_pressed_space_;
	static bool s_pressed_quit_;
	static bool s_pressed_restart_;

	int (*state_function_) (SimulationProgram* program);
	
public:

	// if steps count equals -1, continue simulation indefinitely
	SimulationProgram(float fps, int step_count, UniverseConstants physicalConstants) : Program(fps),
		step_count_(step_count), simulation_(nullptr), planets_density_(1), controlled_object_(nullptr),
		vector_speed_(nullptr),
		state_function_(nullptr)
	{
		window_name = R"("R" to restart, "Space" to place new planet)";
		constants_ = physicalConstants;

		ProgramInputHandler::AddButtonHandlers({
			ButtonHandler(Key::Space, HandleSpace),
			ButtonHandler(Key::Q, HandleQ),
			ButtonHandler(Key::R, HandleR),
			ButtonHandler(Key::D, HandleD),
		});
	}

	~SimulationProgram() override
	{
		delete vector_speed_;
		delete simulation_;
	}

	static int HandleSpace(Program* program);
	static int HandleQ(Program* program);
	static int HandleR(Program* program);
	static int HandleD(Program* program);

	friend int create_planet(SimulationProgram* program);
	friend int planet_position_selection(SimulationProgram* program);
	friend int planet_radius_selection(SimulationProgram* program);
	friend int planet_speed_selection(SimulationProgram* program);
	friend int gravity_simulation(SimulationProgram* program);
	
	int Init() override;
	int Step() override;
	int Finish() override;
};

#endif
