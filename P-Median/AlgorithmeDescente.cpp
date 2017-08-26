#include "stdafx.h"
#include "AlgorithmeDescente.h"


AlgorithmeDescente::AlgorithmeDescente() :
	Algorithme()
{
	pred = new Solution();
}


AlgorithmeDescente::~AlgorithmeDescente()
{
}

void AlgorithmeDescente::nextSolution(Solution * next, Solution * current, Problem * prob)
{
	Solution tmpSol;
	Solution * best = new Solution();

	int val, calc = 1;

	if (pred->egal(current))
	{
		int r;
		best->copySolution(current, prob);
		while (best->isPresent(r = rand() % prob->getNumberOfVertices())) {}
		best->changeRandomCenter(prob, r);
		best->evaluateSolution(prob);
	}
	else
	{
		for (auto i = 0; i < prob->getNumberOfCenter() * 2; i++)
		{
			tmpSol.copySolution(current, prob);
			if (i == prob->getNumberOfCenter())
			{
				calc = -calc;
			}

			val = i % prob->getNumberOfCenter();
			if (!tmpSol.isPresent(val + calc))
			{
				if (tmpSol.AddToValue(val, calc, prob))
				{
					tmpSol.evaluateSolution(prob);
				}

				if (tmpSol.getFctObj() < best->getFctObj())
				{
					best->copySolution(&tmpSol, prob);
				}
			}
		}
	}
	
	next->copySolution(best, prob);
	pred->copySolution(current, prob);

	delete best;
}
