#include <bits/stdc++.h>
#include <vector>

constexpr int64_t MODULUS = 1000000007;

struct InputData {
    int64_t amountOfSteps;
    std::vector<std::vector<int64_t>> matrix;
};

std::vector<std::vector<int64_t>> multiplyMatrices(
    const std::vector<std::vector<int64_t>>& matrixLeft,
    const std::vector<std::vector<int64_t>>& matrixRight){
    int n = matrixLeft.size();
    std::vector<std::vector<int64_t>> answ(n, std::vector<int64_t>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                answ[i][j] += (matrixLeft[i][k]*matrixRight[k][j]) % MODULUS;
                answ[i][j] %= MODULUS;
            }
        }
    }
    return answ;
}

std::vector<std::vector<int64_t>> powerMatrix(
    const std::vector<std::vector<int64_t>>& matrix,
    const int64_t exponent){

    if (exponent == 0) {
        int n = matrix.size();
        std::vector<std::vector<int64_t>> one(n, std::vector<int64_t>(n, 0));
        for (int i = 0; i < n; i++) {
            one[i][i] = 1;
        }
        return one;
    }
    std::vector<std::vector<int64_t>> answ;
    if (exponent % 2 == 0) {
        answ = powerMatrix(matrix, exponent/2);
        return multiplyMatrices(answ, answ);
    }else {
        answ = multiplyMatrices(powerMatrix(matrix, exponent-1), matrix);
    }
    return answ;
}

int64_t getNumberOfWays(
    const std::vector<std::vector<int64_t>>& matrix,
    const int64_t amountOfSteps){

    int n = matrix.size();
    std::vector<std::vector<int64_t>> answMatrix =
            powerMatrix(matrix, amountOfSteps);

    int answ = 0;
    for (int i = 0; i < n; i++) {
        answ += answMatrix[0][i];
        answ %= MODULUS;
    }
    return answ;
}

InputData inputRead(std::istream& in){
    InputData  input;
    int n, m, k;
    std::cin >> n >> m >> k;
    input.amountOfSteps = k;
    input.matrix = std::vector<std::vector<int64_t>>
                    (n, std::vector<int64_t>(n));

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        input.matrix[a][b]++;
    }
    return input;
}

void writeAnswer(std::ostream& out, int64_t result){
    out << result;
}

signed main() {
    const InputData input = inputRead(std::cin);

    // for(auto& line : input.matrix){
    //     for(auto& val : line) std::cout << val << ' ';
    //     std::cout << '\n';
    // }
    // std::cout << input.amountOfSteps << '\n';

    const int64_t result = 
            getNumberOfWays(input.matrix, input.amountOfSteps);
    writeAnswer(std::cout, result);

    return 0;
}
