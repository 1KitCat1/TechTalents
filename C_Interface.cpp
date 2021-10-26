#include <bits/stdc++.h>

constexpr int64_t MODULUS = 1000000007;

struct inputData{
    int64_t n, m, k;
    std::vector<std::vector<int64_t>> matrix;
};

std::vector<std::vector<int64_t>> multiplyMatrix(
    const std::vector<std::vector<int64_t>> matrixLeft, 
    const std::vector<std::vector<int64_t>> matrixRight);

std::vector<std::vector<int64_t>> powerMatrix(
    const std::vector<std::vector<int64_t>> matrix, 
    const int64_t exponent);

int64_t getNumberOfWays(std::vector<std::vector<int64_t>> matrix, int64_t k);

inputData inputRead(std::istream& in);

signed main() {
    inputData input = inputRead(std::cin);
    std::cout << getNumberOfWays(input.matrix, input.k);

    return 0;
}
