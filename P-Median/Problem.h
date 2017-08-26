#pragma once
#include <vector>
class Problem
{
public:
	Problem(int vert, int edge, int center, int obj);
	~Problem();
	void addSolution(vector<int> center);
	void addEdge(int x, int y, int poids);
	void afficher();
	void FloydWarshall();

	int getNumberOfVertices() { return m_number_Of_Vertices; }
	int getNumberOfCenter() { return m_number_Of_Center; }
	int getValueInMatrice(int i, int j) { return ma_Graphe->getVal(i, j); }
	int getCenter(int i) { return v_Center[i]; }

	int getFctObj() { return m_FctObj; }

	void addNumberOfEvaluation() { m_number_Of_Evaluation++; }
	int getNumberOfEvaluation() { return m_number_Of_Evaluation; }
private:
	int m_number_Of_Vertices;
	int m_number_Of_Edge;
	int m_number_Of_Center;
	int m_FctObj;
	vector<int> v_Center;
	Matrice<int> * ma_Graphe;

	int m_number_Of_Evaluation;
};

