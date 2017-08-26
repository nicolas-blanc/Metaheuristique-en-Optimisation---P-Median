#pragma once
#include "Algorithme.h"
class AlgorithmeDescente :
	public Algorithme
{
public:
	AlgorithmeDescente();
	~AlgorithmeDescente();

	virtual string nameAlgo() override { return "Descente"; }

	virtual void nextSolution(Solution * next, Solution * current, Problem * prob) override;
protected:
	Solution * pred;
};

