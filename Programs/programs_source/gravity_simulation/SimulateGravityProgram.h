#ifndef PROGRAM_SIMULATION_FUNCTIONS
#define PROGRAM_SIMULATION_FUNCTIONS

#include "Program.h"
#include "ProgramInputHandler.h"
#include "Simulation.h"
#include "vector_editor/VectorSelector.h"

class UniverseConstants;

class SimulationProgram : public Program
{
	int step_count_;
	int current_step_ = 0;
	UniverseConstants constants_;
	Simulation simulation_;
	ConsoleDisplay* console_;

	// set speed of one celestial body
	CelestialBody* controlled_object_;
	VectorSelector* vector_selector_;
	
public:

	// if steps count equals -1, continue simulation indefinitely
	SimulationProgram(float fps, int step_count, UniverseConstants physicalConstants) : Program(fps),
		step_count_(step_count), controlled_object_(nullptr), vector_selector_(nullptr)
	{
		constants_ = physicalConstants;
		simulation_ = Simulation();
		console_ = new ConsoleDisplay();
	}

	~SimulationProgram() override
	{
		delete console_;
		delete vector_selector_;
	}

	int Init() override
	{
		simulation_.ResetSimulation();

		// this scale defines units of measurement related to simulation objects
		constants_.coordinate_scale = { 1 / 1500.f, 1 / 1500.f , 1};
		ProgramInputHandler::renderer_.SetGlobalScale(constants_.coordinate_scale.ToGlm());
		
		
		auto* Sun = new CelestialBody(
			"Sun", 
			Vector3{250, 213, 27} / 255.f,
			&constants_,
			100.f, 
			274.f);
		
		auto* Earth = new CelestialBody(
			"Earth", 
			Vector3{27, 100, 10} / 255.f,
			&constants_,
			50.f, 
			9.8f);
		
		Sun->SetPosition({ 0.f, 0.f });
		Earth->SetPosition({ 800.f, 0.f });
		
		vector_selector_ = new VectorSelector(Vector3{200, 0, 0} / 255.f);
		vector_selector_->StartSelectVector(Earth->Position());
		controlled_object_ = Earth;
		
		simulation_.AddCelestialBody(Sun);
		simulation_.AddCelestialBody(Earth);

		// simulation_.SetOrbit(Sun, Earth, constants_);

		// show initial info
		console_->ShowGameInformation(simulation_.Objects(), constants_, "Initial position", true);

		ProgramInputHandler::SetClearColor(0, 127, 200);
		return 0;
	}

	// return 0 if want to continue, anything else will stop loop
	int Step() override
	{
		if (!vector_selector_->vector_selected)
		{
			auto mouse_pos = *ProgramInputHandler::mouse_position_;
			mouse_pos = mouse_pos.ScaleInv(Vector3::FromGlm(ProgramInputHandler::renderer_.GetGlobalScale()));
			
			// update vector gui and wait for mouse click
			if (ProgramInputHandler::clicked_position_ != nullptr)
			{
				vector_selector_->FinishSelection(mouse_pos);
				controlled_object_->SetSpeed(vector_selector_->GetResult() * 0.1);
				ProgramInputHandler::clicked_position_ = nullptr;
			}
			else
			{	
				vector_selector_->UpdateSelected(mouse_pos);
			}
		}
		else
		{
			// simulate physics or finish simulation
			if (step_count_ == -1 || current_step_ < step_count_) {
				current_step_++;
			} else {
				return 1;
			}

			if (!simulation_.SimulateStep(constants_))
			{
				return 1;
			}
		}

		// Draw objects anyway
		for (auto* object : simulation_.Objects())
		{
			object->Draw(ProgramInputHandler::renderer_);
		}
		
		if (!vector_selector_->vector_selected)
		{
			vector_selector_->Draw(ProgramInputHandler::renderer_);
		}

		console_->ShowGameInformation(simulation_.Objects(), constants_, "", true);
		return 0;
	}

	int Finish() override
	{
		//if simulation stopped early, we can look at final step
		console_->ShowGameInformation(simulation_.Objects(), constants_, "", true);
		std::cout << "\nSimulation Finished" << std::endl;
		return 0;
	}
};

#endif
