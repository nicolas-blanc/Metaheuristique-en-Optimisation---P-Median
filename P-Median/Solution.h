#include "Problem.h"
#pragma once
class Solution
{
public:
	Solution();
	Solution(vector<int> solution, Problem * prob);
	Solution(vector<int> sol1, vector<int> sol, Problem * prob);
	Solution(Problem * prob);
	Solution(const Solution &obj);
	virtual ~Solution();

	void CreateSolution(Problem * problem);
	void copySolution(Solution * sol, Problem * prob);
	void copySolution(Solution * sol);

	void evaluateSolution(Problem * problem);
	
	void printSolution(ofstream& f_out);
	void printSolution();

	bool egal(Solution * sol);

	int getFctObj() const { return m_fctObj; }
	void resetFctObj();
	void setSolution(vector<int> * sol) { delete v_solution;  v_solution = sol; }
	vector<int> * getSolution() const { return v_solution; }
	vector<int> * addSolutionReturnFixed(vector<int> * sol);
	void addSolution(vector<int> * sol) { for each (int val in (*sol)) { v_solution->push_back(val); } }
	bool isPresent(int val) const { return find(v_solution->begin(), v_solution->end(), val) != v_solution->end(); }
	int getValue(int i) const { return v_solution->at(i); }
	void delValue(int i) { v_solution->erase(v_solution->begin() + i); }
	bool AddToValue(int i, int val, Problem * prob);
	void changeRandomCenter(Problem * prob, int vert);
	vector<int> getRangeValue(int param1, int param2);
protected:
	int m_fctObj;

	vector<int> * v_solution;
};

