#pragma once

#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>
#include <tuple>

using namespace std;

// ||dx||/||x|| <= ||A-1|||A||*(||db||/||b|| + ||dA||/||A||)

template<typename T>
using Matrix = vector<vector<T>>;

Matrix<double> ZERO(int n, int m) {

	vector<double> l(n, 0);
	Matrix<double> R(m, l);

	return move(R);
}

template<typename T>
vector<T> operator+(const vector<T>& l, const vector<T>& r) {
	if (l.size() != r.size()) throw(invalid_argument("Vectors' sizes differ"));

	vector<T> res;
	res.reserve(l.size());

	for (size_t i = 0; i < l.size(); ++i) {
		res.push_back(l[i] + r[i]);
	}

	return res;
}

template<typename T>
vector<T> operator*(const T lambda, const vector<T>& v) {

	vector<T> res;
	res.reserve(v.size());

	for (size_t i = 0; i < v.size(); ++i) {
		res.push_back(lambda*v[i]);
	}

	return res;
}

template<typename T>
vector<T> operator-(const vector<T>& l, const vector<T>& r) {
	if (l.size() != r.size()) throw(invalid_argument("Vectors' sizes differ"));

	return l + (-1.0)*r;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "|";
	for (size_t i = 0; i < v.size() - 1; ++i) {
		os << setw(6) << v[i] << ", ";
	}
	os << setw(6) << v.back() << "|";

	return os;

}

template<typename T>
Matrix<T> operator+(const Matrix<T>& l, const Matrix<T>& r) {
	if (l.size != r.size()) {
		throw(invalid_argument("Matrix' sizes differ"));
	}

	Matrix<T> res;
	res.reserve(l.size());

	for (int i = 0; i < l.size; ++i) {
		res.push_back(l[i] + r[i]);
	}

	return res;
}

template<typename T>
Matrix<T> operator*(const T lambda, const Matrix<T>& m) {

	Matrix<T> res(m.size());

	for (int i = 0; i < m.size(); ++i) {
		res.push_back(lambda * m[i]);
	}

	return res;
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& l, const Matrix<T>& r) {
	if (l.size != r.size()) throw(invalid_argument("Matrix' sizes differ"));

	return l + (-1) * r;
}

template<typename T>
ostream& operator<<(ostream& os, const Matrix<T>& m) {
	
	for (size_t i = 0; i < m.size() + 2; ++i) {
		os << "------";
	}

	os << endl;

	for (const auto& v : m) {
		os << setprecision(4) << setw(6) << v << endl;
	}

	for (size_t i = 0; i < m.size() + 2; ++i) {
		os << "------";
	}

	return os;

}


Matrix<double> operator*(const Matrix<double>& l, const Matrix<double>& r) {

	if (l[0].size() != r.size()) {
		throw(invalid_argument("Can't multiply such Matrixes"));
	}

	Matrix<double> res = ZERO(l.size(), r[0].size());

	for (int i = 0; i < res.size(); ++i) {
		for (int j = 0; j < res[0].size(); ++j) {
			for (int k = 0; k < l.size(); ++k) {
				res[i][j] += l[i][k] * r[k][j];
			}
		}
	}


	return res;
}

template<typename T>
void GaussByMainMeaning(Matrix<T>& m) {
	for (size_t i = 0; i < m.size() - 1; ++i) {

		int maxptr = i;
		double max = -1;
		/*for (size_t j = i; j < m.size(); ++j) {
			if (abs(m[i][j]) > max) {
				max = abs(m[i][j]);
				maxptr = j;
			}
		}*/

		for (size_t j = i; j < m.size(); ++j) {
			if (abs(m[j][i]) > max) {
				max = abs(m[j][i]);
				maxptr = j;
			}
		}


		if (abs(max + 1) < 0.0001) {
			throw(runtime_error("Cannot find maximal element in matrix"));
		}

		if (i != maxptr) {
			swap(m[i], m[maxptr]);
		}

		/*if (i != maxptr) { 
			for (size_t j = 0; j < m[i].size(); ++j) {
				swap(m[j][i], m[j][maxptr]);
			} 
		}*/

		for (size_t j = i + 1; j < m.size(); ++j) {
			m[j] = m[j] - (m[j][i] / m[i][i]) * m[i];
		
		}

		cout << m << endl;
		
	}
}


template <typename T>
vector<T> Resolve3D(Matrix<T>& m, vector<T>& f) {

	vector<T> X(m[0].size, 0), P, R;

	P.push_back(m[0][1] / m[0][0]);
	R.push_back(f[0] / m[0][0]);

	for (size_t i = 1; i < m[0].size() - 1; ++i) {
		P.push_back(m[i][i + 1] / (m[i][i] - m[i + 1][i] * P[i - 1]));
		R.push_back((f[i] - m[i + 1][i] * R[i - 1]) / (m[i][i] - m[i][i + 1] * P[i - 1]));
	}

	X.back() = R.back();

	for (size_t i = m[0].size() - 2; i >= 0; --i) {			//Backward resolving
		X[i] = R[i] - P[i] * X[i + 1];
	}
	
	return X;
}

tuple<Matrix<double>, Matrix<double>, Matrix<double>> LDR(const Matrix<double> M) {

	if (M.size() != M[0].size()) {
		throw(invalid_argument("Non-square matrix in LDR"));
	}

	Matrix<double> L = ZERO(M.size(), M.size()), D = ZERO(M.size(), M.size()), R = ZERO(M.size(), M.size());

	for (size_t i = 0; i < M.size(); ++i) {
		for (size_t j = 0; j < M.size(); ++j) {
			if (i == j) {
				D[i][j] = M[i][j];
			}
			else if (i < j) {
				R[i][j] = M[i][j];
			}
			else{
				L[i][j] = M[i][j];
			}
		}
	}

	cout << M << endl
		<< L << endl
		<< D << endl
		<< R << endl;

	return { L, D, R };
}