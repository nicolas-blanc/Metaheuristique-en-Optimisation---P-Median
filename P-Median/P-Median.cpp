// P-Median.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#define NUMBER_OF_EXECUTION_PER_ALGO 5
#define NUMBER_OF_EXECUTION_RAND 100
#define NUMBER_OF_EXECUTION_ALGO 100

#define SETLOAD_RAND (NUMBER_OF_EXECUTION_RAND / 10)
#define SETLOAD_ALGO (NUMBER_OF_EXECUTION_ALGO / 10)

void algorithmeAleatoire(Solution * best, Solution * sol, Problem * prob);
void algorithme(RecuitSimule * algo, Solution * best, Solution * sol, Problem * prob);
void algorithme(Algorithme * algo, Solution * best, Solution * sol, Problem * prob);

void clearVector(vector<Solution * > * vec);
void writeInformation(ofstream& f_result, string nameFile, Problem * prob, vector<Solution *> * v_Alea, vector<Solution *> * v_Des, vector<Solution *> * v_RS, vector<Solution *> * v_AG);

int main()
{
	ofstream f_result("../result.csv", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	if (!f_result)
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	ofstream f_out("../out.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	if (!f_out)
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	f_result << "NomFichier;Probleme;NbVertice;NbCenter;FctObj;Initial;E1;E2;E3;E4;E5;Min;Max;Moy;Descente;E1;E2;E3;E4;E5;Min;Max;Moy;RS;E1;E2;E3;Min;Max;Moy;AG;E1;E2;E3;E4;E5;Min;Max;Moy" << endl;

	srand(std::time(0));
	vector<string> files{ "../Problems/", "pmed1n", "pmed2n", "pmed3n", "pmed4n", "pmed5n", "pmed6n", "pmed7n", "pmed8n", "pmed9n",
						  "pmed11n", "pmed12n", "pmed13n", "pmed14n", "pmed16n", "pmed17n", "pmed18n", "pmed21n", "pmed22n", "pmed23n", "pmed10n", "pmed26n", "pmed27n", "pmed31n", "pmed32n"
// 						, "pmed15n", "pmed19n", "pmed20n", "pmed24n", "pmed25n", "pmed28n", "pmed29n",
// 						  "pmed30n", "pmed33n", "pmed34n", "pmed35n", "pmed36n", "pmed37n", "pmed38n", "pmed39n", "pmed40n"
						};

// 	vector<string> files{ "../Problems/", "pmed1n" , "pmed2n" , "pmed3n" , "pmed4n" , "pmed5n" , "pmed6n", "pmed7n", "pmed8n", "pmed9n", 
// 						  "pmed11n", "pmed12n", "pmed13n", "pmed16n", "pmed17n", "pmed18n", "pmed21n", "pmed22n", "pmed23n" };

	Solution * sol = new Solution();
	Solution * SaveSol = new Solution();
	Solution * bestD = new Solution();
	Solution * bestRS = new Solution();
	Solution * bestAG = new Solution();

	vector<Solution *> * v_Best_Alea = new vector<Solution *>;
	vector<Solution *> * v_Best_Des = new vector<Solution *>;
	vector<Solution *> * v_Best_RS = new vector<Solution *>;
	vector<Solution *> * v_Best_AG = new vector<Solution *>;

	for (int i = 1; i < files.size(); i++)
	{
		Problem * prob = ReadProblem::readFile(files[0] + files[i] + ".txt");

		for (int j = 0; j < NUMBER_OF_EXECUTION_PER_ALGO; j++)
		{
			f_out << files[i] << " +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++" << endl;
			cout << files[i] << " +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++" << endl;
			algorithmeAleatoire(bestD, sol, prob);
			SaveSol->copySolution(bestD, prob);
			v_Best_Alea->push_back(new Solution(*SaveSol));

			f_out << "----- ----- ----- ----- -----" << endl;
			bestD->printSolution(f_out);
			f_out << "----- ----- ----- ----- -----" << endl;

			sol->copySolution(SaveSol, prob);
			Algorithme * algoD = new AlgorithmeDescente();
			algorithme(algoD, bestD, sol, prob);
			v_Best_Des->push_back(new Solution(*bestD));

			f_out << "\nNumber of evaluation : " << prob->getNumberOfEvaluation() << "\n";

			sol->copySolution(SaveSol, prob);
			RecuitSimule * algoRS = new RecuitSimule(50, 0.6, 8, NUMBER_OF_EXECUTION_ALGO);
			algorithme(algoRS, bestRS, sol, prob);
			v_Best_RS->push_back(new Solution(*bestRS));

 			f_out << "\nNumber of evaluation : " << prob->getNumberOfEvaluation() << "\n";

			sol->resetFctObj();
			Algorithme * algoAG = new AlgorithmeGenetique(prob, false, 0.0001, 0.1);
//   			Algorithme * algoAG = new AlgorithmeGenetique(prob, true, 0.25, 0.2);
			algorithme(algoAG, bestAG, sol, prob);
			v_Best_AG->push_back(new Solution(*bestAG));

	 		f_out << "\nNumber of evaluation : " << prob->getNumberOfEvaluation() << "\n";


			f_out << "----- ----- --   Descente    -- ----- -----\n";
			bestD->printSolution(f_out);
			f_out << "----- ----- -- Recuit Simule -- ----- -----\n";
			bestRS->printSolution(f_out);
			f_out << "----- ----- -- A. Genetique  -- ----- -----\n";
			bestAG->printSolution(f_out);
			f_out << "----- ----- ----- ------- ----- ----- -----\n";

			sol->resetFctObj();
			bestD->resetFctObj();
			bestRS->resetFctObj();
			bestAG->resetFctObj();

			delete algoD;
 			delete algoRS;
 			delete algoAG;
		}

		writeInformation(f_result, files[i], prob, v_Best_Alea, v_Best_Des, v_Best_RS, v_Best_AG);

		clearVector(v_Best_Alea);
		clearVector(v_Best_Des);
		clearVector(v_Best_RS);
		clearVector(v_Best_AG);

		delete prob;
	}

	delete sol;
	delete SaveSol;
	delete bestD;
	delete bestRS;
	delete bestAG;

	delete v_Best_Des;
	delete v_Best_RS;
	delete v_Best_AG;

 	f_result.close();

// 	system("PAUSE");
	return 0;
}

void algorithmeAleatoire(Solution * best, Solution * sol, Problem * prob)
{
	for (auto i = 0; i < NUMBER_OF_EXECUTION_RAND; i++)
	{
		sol->CreateSolution(prob);
		sol->evaluateSolution(prob);
		if (best->getFctObj() > sol->getFctObj())
		{
			best->copySolution(sol, prob);
		}
	}
}

void algorithme(RecuitSimule * algo, Solution * best, Solution * sol, Problem * prob) {
	int i = 0;
	int delta;
	Solution * next = new Solution();

	cout << algo->nameAlgo() << endl;

	while (i < NUMBER_OF_EXECUTION_ALGO)
	{
		algo->resetNumStage();
		do
		{
			algo->nextSolution(next, sol, prob);
			
			delta = next->getFctObj() - sol->getFctObj();

			algo->addNbCalculDelta();
			algo->addDelta(delta);
			algo->addTemp();

			if (delta <= 0)
			{
				sol->copySolution(next, prob);

				if (sol->getFctObj() < best->getFctObj())
				{
					best->copySolution(sol, prob);
				}

				algo->addDegradation(2);
			}
			else
			{
				if (rand() / double(RAND_MAX) < exp((-delta) / algo->getTemperature()))
				{
					sol->copySolution(next, prob);
					algo->addAcceptDegradation();
					algo->addDegradation(1);
				}
				else
				{
					algo->addDegradation(0);
				}
			}
			algo->addNumStage();

			/* ----- Affichage de l'avancement de l'algorithme ----- */
			if (i % SETLOAD_ALGO == 0)
				cout << "- ";
// 			cout << i << " - FctObj : " << sol->getFctObj() << "\n";
			/* ----- ----- ----- */
			i++;
		} while (algo->getNumStage() != algo->getNumberInStage());

		// Permet de verifier que le programme ne change pas de palier si le nombre maximum est atteint
		if (algo->getNbChangeTemp() < algo->getNumberOfStage())
		{
			algo->setTemperature();
			algo->AddNbChangeTemp();
		}
	}

	cout << endl;

	delete next;

	algo->writeInformation(NUMBER_OF_EXECUTION_ALGO);
}

void algorithme(Algorithme * algo, Solution * best, Solution * sol, Problem * prob)
{
	Solution * next = new Solution();

	cout << algo->nameAlgo() << endl;

	for (auto i = 0; i < NUMBER_OF_EXECUTION_ALGO; i++)
	{
		algo->nextSolution(next, sol, prob);

		if (next->getFctObj() < best->getFctObj())
		{
			best->copySolution(next, prob);
			sol->copySolution(next);
		}

		/* ----- Affichage de l'avancement de l'algorithme ----- */
		if (i % SETLOAD_ALGO == 0)
			cout << "- ";
// 		cout << i << " - FctObj : " << sol->getFctObj() << "\n";
		/* ----- ----- ----- */
	}
	cout << endl;

	delete next;
}

void clearVector(vector<Solution * > * vec)
{
	for (int i = 0; i < vec->size(); i++)
		delete vec->at(i);

	vec->clear();
}

bool comp(Solution * s1, Solution * s2) { return s1->getFctObj() < s2->getFctObj(); }

int moy(vector<Solution * > * vec)
{
	int t = 0;

	for (int i = 0; i < vec->size(); i++)
		t += vec->at(i)->getFctObj();

	return t / vec->size();
}

void writeInformation(ofstream& f_result, string nameFile, Problem * prob, vector<Solution *> * v_Alea, vector<Solution *> * v_Des, vector<Solution *> * v_RS, vector<Solution *> * v_AG)
{
	f_result << nameFile << ";;" << prob->getNumberOfVertices() << ";" << prob->getNumberOfCenter() << ";" << prob->getFctObj() << ";;";

	auto result = std::minmax_element(v_Alea->begin(), v_Alea->end(), comp);
	for (int i = 0; i < v_Alea->size(); i++)
		f_result << v_Alea->at(i)->getFctObj() << ";";
	f_result << (*result.first)->getFctObj() << ";" << (*result.second)->getFctObj() << ";" << moy(v_Alea) << ";;";

	result = std::minmax_element(v_Des->begin(), v_Des->end(), comp);
	for (int i = 0; i < v_Des->size(); i++)
		f_result << v_Des->at(i)->getFctObj() << ";";
	f_result << (*result.first)->getFctObj() << ";" << (*result.second)->getFctObj() << ";" << moy(v_Des) << ";;";

	result = std::minmax_element(v_RS->begin(), v_RS->end(), comp);
	for (int i = 0; i < v_RS->size(); i++)
		f_result << v_RS->at(i)->getFctObj() << ";";
	f_result << (*result.first)->getFctObj() << ";" << (*result.second)->getFctObj() << ";" << moy(v_RS) << ";;";

	result = std::minmax_element(v_AG->begin(), v_AG->end(), comp);
	for (int i = 0; i < v_AG->size(); i++)
		f_result << v_AG->at(i)->getFctObj() << ";";
	f_result << (*result.first)->getFctObj() << ";" << (*result.second)->getFctObj() << ";" << moy(v_AG) << ";;";

	f_result << endl;
}

