#include <bits/stdc++.h>

constexpr int MODULUS = 1000000007;

struct inputData{
    int n, m, k;
    std::vector<std::vector<int>> matrix;
};

std::vector<std::vector<int>> multiplyMatrix(
    const std::vector<std::vector<int>> matrixLeft, 
    const std::vector<std::vector<int>> matrixRight);

std::vector<std::vector<int>> powerMatrix(
    const std::vector<std::vector<int>> matrix, 
    const int exponent);

int getNumberOfWays(std::vector<std::vector<int>> matrix, int k);

inputData inputRead(std::istream& in);

signed main() {
    inputData input = inputRead(std::cin);
    std::cout << getNumberOfWays(input.matrix, input.k);

    return 0;
}
