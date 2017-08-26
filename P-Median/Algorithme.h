#pragma once
class Algorithme
{
public:
	Algorithme();
	~Algorithme();

	virtual string nameAlgo() = 0;
	virtual void nextSolution(Solution * next, Solution * current, Problem * prob) = 0;
};

