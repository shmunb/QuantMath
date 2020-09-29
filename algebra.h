#pragma once

#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>

using namespace std;

// ||dx||/||x|| <= ||A-1|||A||*(||db||/||b|| + ||dA||/||A||)

template<typename T>
using Matrix = vector<vector<T>>;

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
