#ifndef __RAY_TRACER_LINEAR_INCLUDED
#define __RAY_TRACER_LINEAR_INCLUDED

#include <vector>
#include <utility>

using Row = std::vector<double>;
using Matrix = std::vector<Row>;
using AugmentedMatrix = std::pair<Matrix, Matrix>;
enum SolutionSetType {none, unique, infinite};
using MaybeSolution = std::pair<SolutionSetType, Matrix>;

Matrix create_matrix(const size_t n, const size_t m);
Matrix rref(const Matrix& m);
AugmentedMatrix rref(const AugmentedMatrix& am);
SolutionSetType number_solutions(const AugmentedMatrix& m);
MaybeSolution solution(const AugmentedMatrix& m);

constexpr double ESP {0};
#endif
