#pragma once
#include "Solution.h"

class SolutionAlea:
	public Solution
{
public:
	SolutionAlea(Problem * prob);
	SolutionAlea(const SolutionAlea &obj);
	~SolutionAlea();

	virtual void CreateSolution(Problem * problem) override;
	virtual void evaluateSolution(Problem * problem) override;
	virtual Solution * copySolution() override;
};

