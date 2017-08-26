#include "stdafx.h"
#include "RecuitSimule.h"


RecuitSimule::RecuitSimule(int starting_Temperature /*= 100*/, double alpha /*= 0.9*/, int number_Of_Stage /*= 4*/, int number_Of_Iteration /*= 100*/) :
	AlgorithmeDescente(),
	m_starting_Temperature(starting_Temperature),
	m_alpha(alpha),
	m_number_Of_Stage(number_Of_Stage),
	m_number_In_Stage(number_Of_Iteration / number_Of_Stage),
	m_temperature(starting_Temperature)
{
}

RecuitSimule::~RecuitSimule()
{
}

void RecuitSimule::writeInformation(int nb_eval_max)
{
	ofstream f_testDelta("../testDelta.csv", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	if (!f_testDelta)
		cout << "Impossible d'ouvrir le fichier !" << endl;

	auto result = std::minmax_element(m_delta.begin(), m_delta.end());

	int moyenneDelta = 0;
	double moyenneExp = 0;
	int nbPositif = 0;
	for (int i = 0; i < m_delta.size(); i++)
	{
		if (m_delta[i] > 0)
		{
			moyenneDelta += m_delta[i];
			moyenneExp += exp((-m_delta[i]) / m_temp[i]);
			nbPositif++;
		}
	}

	if (nbPositif == 0)
	{
		moyenneDelta = 0;
		moyenneExp = 0;
	}
	else
	{
		moyenneDelta /= nbPositif;
		moyenneExp /= nbPositif;
	}

	f_testDelta << "t0;" << m_starting_Temperature << ";;Nombre Delta;" << m_nbCalculDelta << ";;Max Delta;" << m_delta[result.second - m_delta.begin()] << endl;
	f_testDelta << "alpha;" << m_alpha << ";;Nombre Degradation;" << m_nbAcceptDegradation << ";;Moyenne Exp;" << moyenneExp << endl;
	f_testDelta << "nbPalier;" << m_number_Of_Stage << ";;Nombre Temperature;" << m_nbChangeTemp << ";;Moyenne Delta;" << moyenneDelta << endl;
	f_testDelta << "nbEvalMax;" << nb_eval_max << endl;

	f_testDelta << endl;
	f_testDelta << "Temp;Delta < 0;Delta > 0 && Non;Delta > 0 && Oui" << endl;

	double temp = m_temp[0];
	array<int, 3> nbdeg;
	nbdeg.fill(0);

	for (int i = 0; i < m_degradation.size(); i++)
	{
		nbdeg[m_degradation[i]]++;

		if (m_degradation[i] == 2)
			m_degradation[i] = -1;

		if (temp != m_temp[i])
		{
			f_testDelta << temp << ";" << nbdeg[2] << ";" << nbdeg[0] << ";" << nbdeg[1] << endl;
			nbdeg.fill(0);
			temp = m_temp[i];
		}
	}
	f_testDelta << temp << ";" << nbdeg[2] << ";" << nbdeg[0] << ";" << nbdeg[1] << endl;

	for (int i = m_number_Of_Stage + 1; i < 12; i++)
		f_testDelta << endl;

	f_testDelta << "numInc;Delta;Temp;exp(-d/T);degradation" << endl;

	double expo = 0;
	for (int i = 0; i < m_delta.size(); i++)
	{
		if (m_delta[i] != 0)
		{
			if (m_delta[i] < 0)
			{
				f_testDelta << i << ";" << m_delta[i] << ";" << m_temp[i] << ";-1;" << m_degradation[i] << endl;
			}
			else
			{
				expo = exp((-m_delta[i]) / m_temp[i]);
				f_testDelta << i << ";" << m_delta[i] << ";" << m_temp[i] << ";" << expo << ";" << m_degradation[i] << endl;
			}
		}
	}

	f_testDelta.close();
}
