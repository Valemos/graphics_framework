#include "SimulationProgram.h"

#include <random>

bool SimulationProgram::s_pressed_space_ = false;
bool SimulationProgram::s_pressed_quit_ = false;
bool SimulationProgram::s_pressed_restart_ = false;


int planet_position_selection(SimulationProgram* program);
int planet_radius_selection(SimulationProgram* program);
int planet_speed_selection(SimulationProgram* program);
int create_planet(SimulationProgram* program);
int gravity_simulation(SimulationProgram* program);


int create_planet(SimulationProgram* program)
{
	auto* planet = new CelestialBody(
		"Planet",
		Vector3(rand() % 256, rand() % 256, rand() % 256) / 255,
		&program->constants_
	);

    planet->SetSurfaceGravity(50.f, program->constants_);

	program->simulation_->AddCelestialBody(planet);
	program->controlled_object_ = planet;

	program->state_function_ = planet_position_selection;
	
	return Program::program_continue;
}

int planet_position_selection(SimulationProgram* program)
{
	const auto mouse_pos = *ProgramInputHandler::mouse_position;
	
	program->controlled_object_->SetPosition(mouse_pos);
	
	if (ProgramInputHandler::clicked_position != nullptr)
	{
		ProgramInputHandler::clicked_position = nullptr;
		program->state_function_ = planet_radius_selection;
	}
	
	return Program::program_continue;
}

int planet_radius_selection(SimulationProgram* program)
{
	const auto radius = program->controlled_object_->GetPosition().Distance(*ProgramInputHandler::mouse_position);

	program->controlled_object_->SetRadius(radius);

	if (ProgramInputHandler::clicked_position != nullptr)
	{
		ProgramInputHandler::clicked_position = nullptr;

		program->vector_speed_->SetStart(program->controlled_object_->GetPosition());
		program->controlled_object_->SetDensity(program->planets_density_, program->constants_);
		program->state_function_ = planet_speed_selection;
	}
	
	return Program::program_continue;
}

int planet_speed_selection(SimulationProgram* program)
{
	// update vector gui and wait for mouse click
	if (ProgramInputHandler::clicked_position != nullptr)
	{
		program->vector_speed_->SetEnd(*ProgramInputHandler::mouse_position);
		const auto result_vector = program->vector_speed_->GetEnd() - program->vector_speed_->GetStart();
		program->controlled_object_->SetSpeed(0.05 * result_vector);
		ProgramInputHandler::clicked_position = nullptr;

		// change state to next
		program->state_function_ = gravity_simulation;
		return Program::program_finish;
	}

	program->vector_speed_->SetEnd(*ProgramInputHandler::mouse_position);
	return Program::program_continue;
}

int gravity_simulation(SimulationProgram* program)
{
	// simulate physics
	if (program->step_count_ == -1 || program->current_step_ < program->step_count_)
	{
		program->current_step_++;
	}
	else
	{
		return Program::program_finish;
	}

	return program->simulation_->SimulateStep(program->constants_) ? 
	       Program::program_continue : Program::program_finish;
}

int SimulationProgram::HandleSpace(Program* program)
{
	auto* sym_program = dynamic_cast<SimulationProgram*>(program);
	sym_program->state_function_ = create_planet;
	return program_continue;
}

int SimulationProgram::HandleQ(Program*)
{
	return program_finish;
}

int SimulationProgram::HandleR(Program*)
{
	return program_restart;
}

int SimulationProgram::HandleD(Program* program) {
    auto* sym_program = dynamic_cast<SimulationProgram*>(program);

    sym_program->simulation_->ShowInformation(sym_program->constants_, "", true);

    return program_continue;
}

int SimulationProgram::Init()
{
	simulation_ = new Simulation();
	current_step_ = 0;
	planets_density_ = 4.f;
	
	// this scale defines units of measurement related to simulation objects
	constants_.coordinate_scale = {1 / 1800.f, 1 / 1800.f, 1};
	ProgramInputHandler::renderer.SetGlobalScale(constants_.coordinate_scale.ToGlm());


	//auto* Sun = new CelestialBody("Sun",Vector3{250, 213, 27} / 255.f, &constants_);
	//Sun->SetRadius(300.f);
	//Sun->SetSurfaceGravity(274.f, constants_);
	//Sun->SetPosition({ 0.f, 0.f });

	auto* Earth = new CelestialBody("Earth", Vector3{27, 100, 10} / 255.f, &constants_);
	Earth->SetRadius(50.f);
	Earth->SetSurfaceGravity(50.f, constants_);
	Earth->SetPosition({900.f, 0.f});
	

	vector_speed_ = new VectorFigure(Vector3{100, 0, 0} / 255.f, 1.f, 0.1);
	vector_speed_->SetBorderWidth(4.f);

	controlled_object_ = Earth;
	state_function_ = planet_position_selection;
	
	//simulation_->AddCelestialBody(Sun);
	simulation_->AddCelestialBody(Earth);

	// simulation_.SetOrbit(Sun, Earth, constants_);

	// show initial info
	simulation_->ShowInformation(constants_, "Initial position", true);

	ProgramInputHandler::SetClearColor(0, 127, 200);

	srand(100);
	
	return 0;
}

int SimulationProgram::Step()
{
	state_function_(this);
	
	// Draw objects
	for (auto* object : simulation_->Objects())
	{
		object->Draw(ProgramInputHandler::renderer);
	}

	if (state_function_ == planet_speed_selection)
	{
		vector_speed_->Draw(ProgramInputHandler::renderer);
		vector_speed_->DrawWireframe(ProgramInputHandler::renderer);
	}

 	return ProgramInputHandler::HandleButtons(this);
}

int SimulationProgram::Finish()
{
	//if simulation stopped early, we can look at final step
	simulation_->ShowInformation(constants_, "", true);
	std::cout << "\nSimulation Finished" << std::endl;
	
	delete simulation_;
	return program_finish;
}
