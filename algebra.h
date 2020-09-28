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
	if (l.size != r.size()) throw(invalid_argument("Vectors' sizes differ"));

	vector<T> res(l.size());

	for (int i = 0; i < l.size; ++i) {
		res.push_back(l[i] + r[i]);
	}

	return res;
}

template<typename T>
vector<T> operator*(const T lambda, const vector<T>& v) {

	vector<T> res(l.size());

	for (int i = 0; i < l.size; ++i) {
		res.push_back(l*r[i]);
	}

	return res;
}

template<typename T>
vector<T> operator-(const vector<T>& l, const vector<T>& r) {
	if (l.size != r.size()) throw(invalid_argument("Vectors' sizes differ"));

	return l + (-1)*r;
}

template<typename T>
ostream operator<<(ostream& os, const vector<T>& v) {
	os << "|";
	for (int i = 0; i < v.size() - 1; ++i) {
		os << v[i] << ", ";
	}
	os << v.back() << "|";

	return os;

}

template<typename T>
Matrix<T> operator+(const Matrix<T>& l, const Matrix<T>& r) {
	if (l.size != r.size()) throw(invalid_argument("Matrix' sizes differ"));

	Matrix<T> res(l.size());

	for (int i = 0; i < l.size; ++i) {
		res.push_back(l[i] + r[i]);
	}

	return res;
}

template<typename T>
Matrix<T> operator*(const T lambda, const Matrix<T>& v) {

	Matrix<T> res(l.size());

	for (int i = 0; i < l.size; ++i) {
		res.push_back((l * r[i]);
	}

	return res;
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& l, const Matrix<T>& r) {
	if (l.size != r.size()) throw(invalid_argument("Matrix' sizes differ"));

	return l + (-1) * r;
}

template<typename T>
ostream operator<<(ostream& os, const Matrix<T>& m) {
	
	for (int i = 0; i < m.size(); ++i) {
		os << "-----"
	}

	for (const auto& v : m) {
		os << setprecision(2) << setw(5) << v << endl;
	}

	for (int i = 0; i < m.size(); ++i) {
		os << "-----"
	}

	return os;

}
