#include "stdafx.h"
#include "AlgorithmeGenetique.h"

AlgorithmeGenetique::AlgorithmeGenetique(Problem * prob, bool co /*= true*/, float size_Pop_Child /*= 1.0*/, float prob_Mutation /*= 0*/) :
	Algorithme(), m_prob_Mutation(prob_Mutation), m_crossover(co)
{
	m_best = nullptr;
	m_worst = nullptr;
	

	int d = ceil((double) prob->getNumberOfVertices() / prob->getNumberOfCenter());
	m_size_Of_Population = max(d * 4, (int) ceil(prob->getNumberOfVertices() / 3));
	m_size_Population_Child = (int) ceil(m_size_Of_Population * size_Pop_Child);


	if (m_crossover)
		initialisationPopulationCO(prob);
	else
		initialisationPopulation(prob);
}

AlgorithmeGenetique::~AlgorithmeGenetique()
{
	for (int i = 0; i < m_size_Of_Population; i++)
		delete population[i];
}

void AlgorithmeGenetique::nextSolution(Solution * next, Solution * current, Problem * prob)
{
	Solution * tmpSol;
	vector<Solution *> * population_Child = new vector<Solution *>;

	while (population_Child->size() < m_size_Population_Child)
	{
		if (m_crossover)
			croisementCO(prob, population_Child);
		else
		{
			tmpSol = croisement(prob);
			mutation(prob, tmpSol);
			population_Child->push_back(tmpSol);
		}
	}

	for each (Solution * var in (*population_Child))
	{
		newPopulation(prob, var);
	}

	next->copySolution(m_best);
}

Solution * AlgorithmeGenetique::getIndividuRandom(Problem * prob)
{
	int r = rand() % m_size_Of_Population;
	return population[r];
}

void AlgorithmeGenetique::initialisationPopulation(Problem * prob)
{
	int const num_Vert = prob->getNumberOfVertices();
	vector<int> tmpSol = {0};

	int center = 0;
	int addinitialisation = 1;

	int i = 0, j = 1, k = 1;
	while (i < m_size_Of_Population)
	{
		if (k % prob->getNumberOfCenter() == 0)
		{
			population.push_back(new Solution(tmpSol, prob));
			if (m_best == nullptr || m_best->getFctObj() > population[i]->getFctObj())
				m_best = population[i];
			if (m_worst == nullptr || m_worst->getFctObj() < population[i]->getFctObj())
			{
				m_worst = population[i];
				m_i_Worst = i;
			}

			tmpSol.clear();
			i++;
		}

		if (j == num_Vert)
		{
			addinitialisation++;
			j = 0;
			center = -addinitialisation;
		}

		center = center + addinitialisation;

		if (center >= num_Vert)
		{
			center = center % num_Vert;
			if (addinitialisation % 2 == 0)
				center++;
		}

		tmpSol.push_back(center);

		j++;
		k++;
	}
}

Solution * AlgorithmeGenetique::croisement(Problem * prob)
{
	Solution * tmpSol = new Solution();
	Solution * tmpBest = new Solution();
	Solution * resetSol = new Solution();
	vector<int> * fixed;

	int s, r, getS;

	tmpSol->copySolution(getIndividuRandom(prob), prob);
	fixed = tmpSol->addSolutionReturnFixed(getIndividuRandom(prob)->getSolution());
	resetSol->copySolution(tmpSol);

	while (tmpSol->getSolution()->size() != prob->getNumberOfCenter())
	{
		s = (int) ceil(tmpSol->getSolution()->size() / 4.0);
		for (int i = 0; i < s; i++)
		{
			getS = tmpSol->getSolution()->size();
			while (isPresent(fixed, tmpSol->getValue(r = rand() % getS))) {}

			tmpSol->delValue(r);
			tmpSol->evaluateSolution(prob);
			if (tmpSol->getFctObj() < tmpBest->getFctObj())
				tmpBest->copySolution(tmpSol);

			tmpSol->copySolution(resetSol);
		}
		tmpSol->copySolution(tmpBest);
		resetSol->copySolution(tmpBest);
		tmpBest->resetFctObj();
	}
	
	delete tmpBest;
	delete resetSol;
	delete fixed;

	return tmpSol;
}

void AlgorithmeGenetique::mutation(Problem * prob, Solution * sol)
{
	if (rand() / RAND_MAX < m_prob_Mutation)
	{
		int r;
		while (sol->isPresent(r = rand() % prob->getNumberOfVertices())) {}
		sol->changeRandomCenter(prob, r);
		sol->evaluateSolution(prob);
	}
}

Solution * AlgorithmeGenetique::getNewWorst()
{
	Solution * w = population[0];
	m_i_Worst = 0;
	for (int i = 1; i < m_size_Of_Population; i++)
		if (w->getFctObj() < population[i]->getFctObj())
		{
			w = population[i];
			m_i_Worst = i;
		}
	return w;
}

bool AlgorithmeGenetique::isPresent(Solution * sol)
{
	Solution * var = nullptr;
	for each (var in population)
		if (var->egal(sol))
			break;

	return var->egal(sol);
}

bool AlgorithmeGenetique::isPresent(vector<int> * fixed, int val)
{
	if (fixed->size() == 0)
		return false;
	
	int var;
	for each (var in (*fixed))
		if (var == val) 
			break;

	return var == val;
}


void AlgorithmeGenetique::newPopulation(Problem * prob, Solution * sol)
{
	if (sol->getFctObj() < m_worst->getFctObj() && !isPresent(sol))
	{
		population.push_back(sol);
		population.erase(population.begin() + m_i_Worst);
		delete m_worst;
		m_worst = getNewWorst();
		if (sol->getFctObj() < m_best->getFctObj())
			m_best = sol;
	}
	else
	{
		delete sol;
	}
}

void AlgorithmeGenetique::initialisationPopulationCO(Problem * prob)
{
	for (int i = 0; i < m_size_Of_Population; i++)
	{
		population.push_back(new Solution(prob));
		if (m_best == nullptr || m_best->getFctObj() > population[i]->getFctObj())
			m_best = population[i];
		if (m_worst == nullptr || m_worst->getFctObj() < population[i]->getFctObj())
		{
			m_worst = population[i];
			m_i_Worst = i;
		}
	}
}

void AlgorithmeGenetique::croisementCO(Problem * prob, vector<Solution *> * population_Child)
{
	Solution * p1 = new Solution();
	Solution * p2 = new Solution();

	p1->copySolution(getIndividuRandom(prob), prob);
	p2->copySolution(getIndividuRandom(prob), prob);

	int range = p1->getSolution()->size() - 1;
	int r = rand() % range + 1;

	vector<int> p1v1 = p1->getRangeValue(0, r - 1);
	vector<int> p1v2 = p1->getRangeValue(r, p1->getSolution()->size() - 1);
	vector<int> p2v1 = p2->getRangeValue(0, r - 1);
	vector<int> p2v2 = p2->getRangeValue(r, p2->getSolution()->size() - 1);

	Solution * c1 = new Solution(p1v1, p2v2, prob);
	Solution * c2 = new Solution(p2v1, p1v2, prob);

	population_Child->push_back(c1);
	population_Child->push_back(c2);
}

void AlgorithmeGenetique::printPopulation()
{
	cout << "Taille population : " << m_size_Of_Population << endl;

	cout << "Best : " << endl;
	m_best->printSolution();
	cout << "Worst : " << endl;
	m_worst->printSolution();
	cout << " ----- " << endl;

	for (int i = 0; i < m_size_Of_Population; i++)
	{
		population[i]->printSolution();
	}
}

