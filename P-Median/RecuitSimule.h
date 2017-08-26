#pragma once
#include "Algorithme.h"
class RecuitSimule :
	public AlgorithmeDescente
{
public:
	RecuitSimule(int starting_Temperature = 100, double alpha = 0.9, int number_Of_Stage = 4, int number_Of_Iteration = 100);
	~RecuitSimule();

	virtual string nameAlgo() override { return "Recuit Simule"; }

	void writeInformation(int nb_eval_max);

	int getNumberOfStage() { return m_number_Of_Stage; }
	int getNumberInStage() { return m_number_In_Stage; }

	double getTemperature() { return m_temperature; }
	void setTemperature() { m_temperature = m_alpha * m_temperature; }
	int getNumStage() { return m_num_Stage; }
	void addNumStage() { m_num_Stage++; }
	void resetNumStage() { m_num_Stage = 0; }

	int getNbChangeTemp() { return m_nbChangeTemp; }
	void AddNbChangeTemp() { m_nbChangeTemp++; }
	void addAcceptDegradation() { m_nbAcceptDegradation++; }
	void addNbCalculDelta() { m_nbCalculDelta++; }
	void addDelta(int delta) { m_delta.push_back(delta); }
	void addTemp() { m_temp.push_back(m_temperature); }
	void addDegradation(int param1) { m_degradation.push_back(param1); }
private:
	int m_starting_Temperature;
	double m_alpha;
	int m_number_Of_Stage;
	int m_number_In_Stage;

	double m_temperature;
	int m_num_Stage = 0;

	// Variable permmetant de recuperer le nmaximun d'information du programme
	int m_nbChangeTemp = 1;
	int m_nbAcceptDegradation = 0;
	int m_nbCalculDelta = 0;
	vector<int> m_delta;
	vector<double> m_temp;
	vector<int> m_degradation;
};

