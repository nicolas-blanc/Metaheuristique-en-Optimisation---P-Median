#include "stdafx.h"
#include "Problem.h"

Problem::Problem(int vert, int edge, int center, int obj)
{
	m_number_Of_Vertices = vert;
	m_number_Of_Edge = edge;
	m_number_Of_Center = center;
	m_FctObj = obj;

	m_number_Of_Evaluation = 0;

	v_Center.resize(m_number_Of_Center);
	ma_Graphe = new Matrice<int>(vert, vert, N_MAXINT);

	for (auto i = 0; i < m_number_Of_Vertices; i++)
		ma_Graphe->setVal(i, i, 0);
}

Problem::~Problem()
{
	delete ma_Graphe;
}

void Problem::addSolution(vector<int> center)
{
	for (auto i = 0; i < m_number_Of_Center; i++)
	{
		v_Center[i] = center[i] - 1;
	}
}

void Problem::addEdge(int x, int y, int poids)
{
	ma_Graphe->setVal(x, y, poids);
}

void Problem::afficher()
{
	cout << "Vertices : " << m_number_Of_Vertices << "\n";
	cout << "Edge : " << m_number_Of_Edge << "\n";
	cout << "Center : " << m_number_Of_Center << "\n";
	cout << "FctObj : " << m_FctObj << "\n";

	cout << "VectCenter :";
	for each (auto var in v_Center)
	{
		cout << " | " << var + 1;
	}
	cout << "\n";

	cout << "Matrice : \n";
//	for (auto i = 0; i < m_number_Of_Vertices; i++)
	for (auto i = 0; i < 5; i++)
	{
// 		for (auto j = 0; j < m_number_Of_Vertices; j++)
		for (auto j = 0; j < 20; j++)
		{
			cout << " | " << ma_Graphe->getVal(i, j);
		}
		cout << "\n";
	}

}

int f_zero(int a) { return (a == N_MAXINT) ? 0 : a; }

void Problem::FloydWarshall()
{
	int m = 0;
	for (auto k = 0; k < m_number_Of_Vertices; k++)
	{
		for (auto i = 0; i < m_number_Of_Vertices; i++)
		{
			for (auto j = 0; j < m_number_Of_Vertices; j++)
			{
				m = min(ma_Graphe->getVal(i, j), (ma_Graphe->getVal(i, k) + ma_Graphe->getVal(k, j)));
				ma_Graphe->setVal(i, j, m);
			}
		}
	}

	ma_Graphe->applique(&f_zero);
}

