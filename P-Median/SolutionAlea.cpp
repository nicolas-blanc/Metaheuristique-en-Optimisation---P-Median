#include "stdafx.h"
#include "SolutionAlea.h"

SolutionAlea::SolutionAlea(Problem * prob)
{
	this->CreateSolution(prob);
	this->evaluateSolution(prob);
}

SolutionAlea::SolutionAlea(const SolutionAlea &obj)
{
	m_fctObj = obj.getFctObj();
	v_solution = new vector<int>(*(obj.getSolution()));
}

SolutionAlea::~SolutionAlea()
{
}

void SolutionAlea::CreateSolution(Problem * problem)
{
	v_solution->clear();
	m_fctObj = 0;
	for (auto i = 0; i < problem->getNumberOfCenter(); i++)
	{
		v_solution->push_back(rand() % problem->getNumberOfVertices() + 1);
	}
}

void SolutionAlea::evaluateSolution(Problem * problem)
{
	int tmp = INT_MAX;
	for (auto i = 0; i < problem->getNumberOfVertices(); i++)
	{
		tmp = INT_MAX;
		for each (auto val in (*v_solution))
		{
			tmp = min(problem->getValueInMatrice(i, val - 1), tmp);
		}
		m_fctObj += tmp;
	}	
}

Solution * SolutionAlea::copySolution()
{
	return new SolutionAlea(*this);
}
