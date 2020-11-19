#include "VectorSelector.h"

VectorSelector::VectorSelector(Vector3 color) : vector_(nullptr)
{
	vector_color_ = color;
}

VectorSelector::~VectorSelector()
{
	delete vector_;
}

void VectorSelector::Draw(Renderer& renderer) const
{
	vector_->Draw(renderer);
}

void VectorSelector::StartSelectVector(Vector3 start_point)
{
	vector_ = new VectorFigure(vector_color_);
	vector_->SetStart(start_point);
}

void VectorSelector::UpdateSelected(Vector3 endPoint) const
{
	vector_->SetEnd(endPoint);
}

void VectorSelector::FinishSelection(Vector3 endPoint)
{
	vector_->SetEnd(endPoint);
	vector_selected = true;
}

Vector3 VectorSelector::GetResult() const
{
	return vector_->GetEnd() - vector_->GetStart();
}
