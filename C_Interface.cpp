#include <bits/stdc++.h>

constexpr int64_t MODULUS = 1000000007;

struct InputData {
    int64_t amountOfSteps;
    std::vector<std::vector<int64_t>> matrix;
};

std::vector<std::vector<int64_t>> multiplyMatrices(
    const std::vector<std::vector<int64_t>>& matrixLeft, 
    const std::vector<std::vector<int64_t>>& matrixRight);

std::vector<std::vector<int64_t>> powerMatrix(
    const std::vector<std::vector<int64_t>>& matrix, 
    const int64_t exponent);

int64_t getNumberOfWays(
	const std::vector<std::vector<int64_t>>& matrix,
	const int64_t amountOfSteps);

InputData inputRead(std::istream& in);

void writeAnswer(std::ostream& out, int64_t result);

signed main() {
    const InputData input = inputRead(std::cin);
    const int64_t result = getNumberOfWays(input.matrix, input.amountOfSteps);
    writeAnswer(std::cout, result);

    return 0;
}
