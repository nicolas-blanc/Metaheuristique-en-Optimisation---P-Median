#include "stdafx.h"
#include "ReadProblem.h"

template<typename Out>
void split(const string &s, char delim, Out result) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		*(result++) = item;
	}
}

vector<int> splitAndStoI(const string &s, char delim) {
	vector<string> elems;
	vector<int> elems_Int;
	split(s, delim, back_inserter(elems));

	for each (auto var in elems)
	{
		elems_Int.push_back(stoi(var));
	}

	return elems_Int;
}

Problem * ReadProblem::readFile(string nameFile)
{
	string line;
	vector<int> tmp;
	Problem * prob = nullptr;

	ifstream myfile(nameFile);
	if (myfile.is_open())
	{
		getline(myfile, line);
		tmp = splitAndStoI(line, ' ');
		prob = new Problem(tmp[0], tmp[1], tmp[2], tmp[3]);

		getline(myfile, line);
		tmp = splitAndStoI(line, ' ');
		prob->addSolution(tmp);

		while (getline(myfile, line))
		{
			tmp = splitAndStoI(line, ' ');

			prob->addEdge(tmp[0] - 1, tmp[1] - 1, tmp[2]);
			prob->addEdge(tmp[1] - 1, tmp[0] - 1, tmp[2]);
		}

		prob->FloydWarshall();

		myfile.close();
	}

	else
	{
		cout << "Unable to open file : " << nameFile << '\n';
	}

	return prob;

}
