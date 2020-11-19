#ifndef VECTOR_SELECTION_GUI
#define VECTOR_SELECTION_GUI

class Renderer;

#include "Vector3.h"
#include "VectorFigure.h"


class VectorSelector
{
	VectorFigure* vector_;
	Vector3 vector_color_;

public:
	bool vector_selected = false;

	VectorSelector(Vector3 color);
	~VectorSelector();
	
	// to Draw vector from certain point
	void Draw(Renderer& renderer) const;
	void StartSelectVector(Vector3 start_point);
	void UpdateSelected(Vector3 endPoint) const;
	void FinishSelection(Vector3 endPoint);
	Vector3 GetResult() const;
};


#endif
