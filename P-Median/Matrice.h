
#ifndef _CLASSE_Matrice_
#define _CLASSE_Matrice_

#pragma once
#include<vector>
using namespace std;

template <typename T>
class Matrice
{
public:
	/// constructeurs/destructeur
	Matrice(const int l, const int c, const T val = 0) : _iL(l), _iC(c) {
		_v.resize(l * c, val);
	}

	Matrice(const int l, const int c, const T* tab) : _iL(l), _iC(c) {
		_v.resize(l * c);
		for (int l = 0; l < _iL; l++)
			for (int c = 0; c < _iC; c++)
				_v[l*_iC + c] = tab[l*_iC + c];
	}
	Matrice(const Matrice &rhs) : _iL(rhs.X()), _iC(rhs.Y()) {
		_v.resize(_iL * _iC);
		for (int l = 0; l < _iL; l++)
			for (int c = 0; c < _iC; c++)
				_v[l*_iC + c] = rhs(l, c);
	}

	~Matrice() {}
	/// @brief accesseurs
	inline T operator()(const int l, const int c) const {
		return _v[l * _iC + c];
	}
	inline T& operator()(const int l, const int c) {
		return _v[l * _iC + c];
	}
	inline T getVal(int x, int y) const {
		return _v[x * _iC + y];
	}
	inline void setVal(int x, int y, T val) {
		_v[x * _iC + y] = val;
	}

	inline int X() const { return _iL; }
	inline int Y() const { return _iC; }
	/// opérations sur la classe

	/// @brief operateur d'assignation
	T& operator=(const T& rhs) {
		if (&rhs != this)
		{
			if (rhs.X() == _iL && rhs.Y() == _iC)
				for (int l = 0; l < _iL; ++l)
					for (int c = 0; c < _iC; ++c)
						_v[l * _iC + c] = rhs(l, c);
			else return NULL;
		}
		return (*this);
	}

	/// @brief remplit la table avec la valeur val
	inline int remplit(const T& val) {
		int nbelem(_iL * _iC);
		_v.assign(nbelem, val);
		return nbelem;
	}
	/// @brief applique la fonction f(arg) aux éléments de la table     
	template<typename ret>
	void applique(ret(*f)(T)) {
		typename vector<T>::iterator it = _v.begin();
		while (it != _v.end()) {
			*it = (*f)(*it);
			++it;
		}
	}
	/// @brief applique la fonction f(arg1, arg2) aux éléments de la table
	/// arg2 doit être du type !!! exact !!! demandé par la fonction f, aucune conversion implicite n'étant possible
	template<typename ret, typename A>
	void applique(ret(*f)(T, A), A arg2) {
		typename vector<T>::iterator it = _v.begin();
		while (it != _v.end()) {
			*it = (*f)(*it, arg2);
			++it;
		}
	}
	//friend ostream& operator<<(ostream& os, Matrice<T>& mat) const {;}
protected:
	int _iL, _iC; // lignes, colonnes
	vector<T> _v;      // notre structure d'accueil
};

#endif

/*
typedef Matrice<double> Matdbl;
ostream& operator<<(ostream& os, Matdbl & mat) {
	int L = mat.X(), C = mat.Y();
	for (int l = 0; l < L; ++l) {
		os << "[ ";
		for (int c = 0; c < C; ++c)
			os << mat(l, c) << '\t';
		os << "]" << endl;
	}
	return os;
}
double f1(double x) { return sqrt(fabs(x)); }
double f2(double x, int i) { return (x * i); }
int main(int argc, char* argv[])
{
	cout << "Matrice d'origine\n" << endl;
	Matdbl M(7, 7);
	Matdbl N(7, 7);
	cout << "fill" << endl;//M;
	M.remplit(-1.);
	cout << "Divers acces en lecture/ecriture" << endl;
	for (short i = 1; i < M.X(); i++) M(i, 0) = i;
	for (short j = 1; j < M.Y(); j++) M(0, j) = j;
	for (short j = 0; j < M.Y(); j++) M(j, j) = 1.;
	cout << "Une recopie" << endl;
	N = M;
	cout << "M =\n" << M;
	cout << "N =\n" << N;
	M.applique(&f1);
	cout << "sqrt(fabs(elem)) = \n" << M;
	M.applique(&f2, 2);
	cout << "M x 2 = \n" << M;
	return 0;
}
*/
