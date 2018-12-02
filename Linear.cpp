#include "Linear.h"
#include <cmath>
#include <cassert>
#include <algorithm>

Matrix create_matrix(const size_t n, const size_t m) {
	Matrix a;

	for (size_t i {0}; i < n; ++i)
		a.push_back(std::vector<double>(m));

	return a;
}

// counts number of leading zeroes in a row
size_t leading_zeroes(const Row& row) {
	for (size_t i {0}; i < row.size(); ++i)
		if (fabs(row[i]) > ESP)
			return i;

	return row.size();
}


Matrix rref(const Matrix& m) {
	AugmentedMatrix am {m, create_matrix(m.size(), 1)};
	return rref(am).first;
}

AugmentedMatrix rref(const AugmentedMatrix& am) {
	// coefficients and augment need to have the same amount of rows
	assert(am.first.size() == am.second.size());

	Matrix m {am.first};
	Matrix a {am.second};
	// select row
	for (size_t i {0}; i < m.size(); ++i) {
		// find leading variable
		size_t leading {leading_zeroes(m[i])};
		if (leading != m[i].size()) {
			// scale row to one
			double s {m[i][leading]};
			for (size_t j {0}; j < m[i].size(); ++j)
				m[i][j] /= s;
			for (size_t j {0}; j < a[i].size(); ++j)
				a[i][j] /= s;

			// subtract from other rows
			for (size_t j {0}; j < m.size(); ++j) {
				if (i == j)
					continue;

				double s {m[j][leading]};
				for (size_t k {0}; k < m[j].size(); ++k) 
					m[j][k] -= s * m[i][k];
				for (size_t k {0}; k < a[j].size(); ++k)
					a[j][k] -= s * a[i][k];
			}
		}
	}

	std::sort(m.begin(), m.end(), [](const Row& r1, const Row& r2) {
			return leading_zeroes(r1) < leading_zeroes(r2);
	});

	return {m, a};
}

SolutionSetType number_solutions(const AugmentedMatrix& am) {
	assert(am.first.size() == am.second.size());

	const Matrix& m {am.first};
	const Matrix& a {am.second};
	// check if there is a row in the form 0=1
	for (size_t i {0}; i < m.size(); ++i) {
		assert(m.size() <= m[i].size());
		// check if row contains all zeroes besides non-augmented matrix
		const bool zero_row {leading_zeroes(m[i]) == m[i].size()};
		// check if augmented matrix contains a non-zero
		for (size_t j {0}; j < a[i].size(); ++j)
			if (std::fabs(a[i][j]) > ESP)
				return none;
	}

	// check if we have row with a non-zero value outside of the diagonal
	for (size_t i {0}; i < m.size(); ++i) {
		for (size_t j {0}; j < m[i].size(); ++j)
			if (i != j && fabs(m[i][j]) > ESP)
				return infinite;
	}

	return unique;
}

MaybeSolution solution(const AugmentedMatrix& am) {
	assert(am.first.size() == am.second.size());

	const SolutionSetType s {number_solutions(am)};
	if (s != unique)
		return {s, {}};

	return {s, am.second};
}
