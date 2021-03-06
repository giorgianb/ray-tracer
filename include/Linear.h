#ifndef __RAY_TRACER_LINEAR_INCLUDED
#define __RAY_TRACER_LINEAR_INCLUDED

#include <vector>
#include <utility>

using Row = std::vector<double>;
using Matrix = std::vector<Row>;
using AugmentedMatrix = std::pair<Matrix, Matrix>;
enum class SolutionSetType {none, unique, infinite};
using SolutionSet = std::pair<SolutionSetType, Matrix>;

Matrix create_matrix(const size_t n, const size_t m);
Matrix& rref_in_place(Matrix& m);
Matrix rref(Matrix m);
AugmentedMatrix& rref_in_place(AugmentedMatrix& am);
AugmentedMatrix rref(AugmentedMatrix am);
SolutionSetType number_solutions(const AugmentedMatrix& m);
SolutionSet solution(const AugmentedMatrix& m);
#endif
