#pragma once
#include "Algorithme.h"
class RechercheTabou :
	public Algorithme
{
public:
	RechercheTabou(int taille_tabou = 7);
	~RechercheTabou();

	// DON'T WORK
	virtual void nextSolution(Solution * next, Solution * current, Problem * prob) override;

private:
	vector<int> v_tabou;
	int m_taille_tabou;

	bool notPresent(int vert);
	void addCenterInQueue(int vert);
	void printTabouVector();
};

