#include "stdafx.h"
#include "RechercheTabou.h"


RechercheTabou::RechercheTabou(int taille_tabou /*= 7*/) :
	Algorithme(), m_taille_tabou(taille_tabou)
{
}

RechercheTabou::~RechercheTabou()
{
}

void RechercheTabou::nextSolution(Solution * next, Solution * current, Problem * prob)
{
	Solution tmpSol;
	Solution * best = new Solution();

	int calc = 1;
	int r = -1;

	for (auto i = 0; i < prob->getNumberOfCenter() * 2; i++)
	{
		tmpSol.copySolution(current, prob);
		if (i == prob->getNumberOfCenter())
		{
			calc = -calc;
		}

		if (notPresent(i % prob->getNumberOfCenter()))
		{
			if (tmpSol.AddToValue((i % prob->getNumberOfCenter()), calc, prob))
			{
				tmpSol.evaluateSolution(prob);
			}

			// 		tmpSol.printSolution();

			if (tmpSol.getFctObj() < best->getFctObj())
			{
				best->copySolution(&tmpSol, prob);
			}
		}

	}

	if (best->egal(current))
	{
		while (true)
		{
			r = rand() % prob->getNumberOfVertices();

			best->changeRandomCenter(prob, r);
			best->evaluateSolution(prob);

			if (notPresent(r) || best->getFctObj() < current->getFctObj())
				break;
		}
	}

	if (r != -1)
	{
		addCenterInQueue(r);
	}

// 	printTabouVector();
}


bool RechercheTabou::notPresent(int vert)
{
	int i;
	for (i = 0; i < v_tabou.size(); i++)
		if (v_tabou[i] == vert)
			break;
	return i == v_tabou.size();
}

void RechercheTabou::addCenterInQueue(int vert)
{
	if (notPresent(vert))
	{
		v_tabou.push_back(vert);

		if (v_tabou.size() > m_taille_tabou)
		{
			v_tabou.erase(v_tabou.begin());
		}
	}
}


void RechercheTabou::printTabouVector()
{
	cout << "Vector tabou : ";
	for each (auto val in v_tabou)
		cout << val << " - ";
	cout << "\n";
}
