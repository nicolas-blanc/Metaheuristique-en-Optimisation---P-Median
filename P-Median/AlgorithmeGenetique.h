#pragma once
#include "Algorithme.h"
class AlgorithmeGenetique :
	public Algorithme
{
public:
	AlgorithmeGenetique(Problem * prob, bool co = true, float size_Pop_Child = 1.0, float prob_Mutation = 0);
	~AlgorithmeGenetique();

	virtual string nameAlgo() override { return "Genetique"; }

	virtual void nextSolution(Solution * next, Solution * current, Problem * prob) override;

private:
	bool m_crossover;

	float m_prob_Mutation;

	int m_size_Of_Population;
	int m_size_Population_Child;

	Solution * m_best;
	int m_i_Worst;
	Solution * m_worst;

	vector<Solution *> population;

	Solution * getIndividuRandom(Problem * prob);

	void initialisationPopulation(Problem * prob);
	Solution * croisement(Problem * prob);

	void initialisationPopulationCO(Problem * prob);
	void croisementCO(Problem * prob, vector<Solution *> * population_Child);

	void mutation(Problem * prob, Solution * sol);
	
	Solution * getNewWorst();
	bool isPresent(Solution * sol);
	void newPopulation(Problem * prob, Solution * sol);

	bool isPresent(vector<int> * fixed, int val);
	void printPopulation();
};

