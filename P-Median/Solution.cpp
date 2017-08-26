#include "stdafx.h"
#include "Solution.h"

Solution::Solution()
{
	m_fctObj = N_MAXINT;
	v_solution = new vector<int>();
}

Solution::Solution(Problem * prob)
{
	m_fctObj = 0;
	v_solution = new vector<int>();
	this->CreateSolution(prob);
	this->evaluateSolution(prob);
}

Solution::Solution(const Solution &obj)
{
	m_fctObj = obj.getFctObj();
	v_solution = new vector<int>(*(obj.getSolution()));
}

Solution::Solution(vector<int> solution, Problem * prob)
{
	m_fctObj = 0;
	v_solution = new vector<int>(solution);
	this->evaluateSolution(prob);
}

Solution::Solution(vector<int> sol1, vector<int> sol, Problem * prob)
{
	m_fctObj = 0;
	v_solution = new vector<int>(sol1);

	int r, i = 0;
	while (v_solution->size() < prob->getNumberOfCenter())
	{
		if (isPresent(sol[i]))
		{
			while (isPresent(r = rand() % prob->getNumberOfVertices())) {}
			v_solution->push_back(r);
		}
		else
		{
			v_solution->push_back(sol[i]);
		}
		i++;
	}
	this->evaluateSolution(prob);
}

Solution::~Solution()
{
	delete v_solution;
}

void Solution::CreateSolution(Problem * problem)
{
	v_solution->clear();
	m_fctObj = 0;
	int r;
	for (auto i = 0; i < problem->getNumberOfCenter(); i++)
	{
		while (isPresent(r = rand() % problem->getNumberOfVertices())) {}
		v_solution->push_back(r);
	}
}

void Solution::evaluateSolution(Problem * problem)
{
	m_fctObj = 0;
	int tmp = INT_MAX;
	for (auto i = 0; i < problem->getNumberOfVertices(); i++)
	{
		tmp = INT_MAX;
		for each (auto val in (*v_solution))
		{
			tmp = min(problem->getValueInMatrice(i, val), tmp);
		}
		m_fctObj += tmp;
	}

	problem->addNumberOfEvaluation();
}

void Solution::copySolution(Solution * sol, Problem * prob)
{
	this->m_fctObj = sol->getFctObj();
	v_solution->clear();
	for (auto i = 0; i < prob->getNumberOfCenter(); i++)
	{
		v_solution->push_back(sol->getValue(i));
	}
}

void Solution::copySolution(Solution * sol)
{
	this->m_fctObj = sol->getFctObj();
	v_solution->clear();
	for (auto i = 0; i < sol->getSolution()->size(); i++)
	{
		v_solution->push_back(sol->getValue(i));
	}
}

void Solution::printSolution(ofstream& f_out)
{
	f_out << "solution : ";

	for each (auto val in (*v_solution))
	{
		f_out << val << " - ";
	}

	f_out << "\nfonction objectif : " << m_fctObj << "\n";

}

void Solution::printSolution()
{
	cout << "solution : ";

	for each (auto val in (*v_solution))
	{
		cout << val << " - ";
	}

	cout << "\nfonction objectif : " << m_fctObj << "\n";

}

bool Solution::egal(Solution * sol)
{
	if (sol->getFctObj() != m_fctObj)
		return false;

	unsigned int i;
	for (i = 0; i < v_solution->size(); i++)
		if (!isPresent(sol->getValue(i)))
			break;

	return !(i < v_solution->size());
}

void Solution::resetFctObj()
{
	m_fctObj = N_MAXINT;
}

std::vector<int> * Solution::addSolutionReturnFixed(vector<int> * sol)
{
	vector<int> * fixed = new vector<int>;
	for each (int val in (*sol))
	{
		if (isPresent(val))
			fixed->push_back(val);
		else
			v_solution->push_back(val);
	}
	return fixed;
}

bool Solution::AddToValue(int i, int val, Problem * prob)
{
	if ((v_solution->at(i) + val) >= 0 && (v_solution->at(i) + val) < prob->getNumberOfVertices())
	{
		(*v_solution)[i] += val;
		return true;
	}
	else
	{
		return false;
	}
}

void Solution::changeRandomCenter(Problem * prob, int vert)
{
	(*v_solution)[rand() % prob->getNumberOfCenter()] = vert;
}

std::vector<int> Solution::getRangeValue(int param1, int param2)
{
	vector<int> tmp;
	for (int i = param1; i <= param2; i++)
		tmp.push_back((*v_solution)[i]);
	return tmp;
}
