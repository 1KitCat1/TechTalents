#include <bits/stdc++.h>
#include <vector>

constexpr int64_t MODULUS = 1000000007;

const int indexShift = 1;

struct InputData {
    int64_t amountOfSteps;
    std::vector<std::vector<int64_t>> matrix;
};

InputData inputRead(std::istream& in){
    InputData  input;
    int amountOfCells, amountOfTunnels, amountOfSteps;
    std::cin >> amountOfCells >> amountOfTunnels >> amountOfSteps;
    input.amountOfSteps = amountOfSteps;
    input.matrix = std::vector<std::vector<int64_t>>
                    (amountOfCells, std::vector<int64_t>(amountOfCells));

    for (int i = 0; i < amountOfTunnels; i++) {
        int from;
        int to;
        in >> from >> to;
        input.matrix[from-indexShift][to-indexShift]++;
    }
    return input;
}

void writeAnswer(std::ostream& out, int64_t result){
    out << result << std::endl;
}

std::vector<std::vector<int64_t>> multiplyMatrices(
    const std::vector<std::vector<int64_t>>& matrixLeft,
    const std::vector<std::vector<int64_t>>& matrixRight){

    if (matrixLeft.size() == 0 || matrixRight.size() == 0) {
        throw std::invalid_argument("Matrix is empty");
    }

    for (int index = 1; index < matrixLeft.size(); index++) {
        if (matrixLeft[index].size() != matrixLeft[0].size()) {
            throw std::invalid_argument(
                "Vector which represent matrix is NOT rectangular");
        }
    }
    for (int index = 1; index < matrixRight.size(); index++) {
        if (matrixRight[index].size() != matrixRight[0].size()) {
            throw std::invalid_argument(
                "Vector which represent matrix is NOT rectangular");
        }
    }

    if (matrixLeft[0].size() != matrixRight.size()) {
        throw std::invalid_argument(
            "Given matrices cannot be multiplied due to their size");
    }

    std::vector<std::vector<int64_t>> answ(matrixLeft.size(),
        std::vector<int64_t>(matrixRight[0].size(), 0));

    for (int i = 0; i < matrixLeft.size(); i++) {
        for (int j = 0; j < matrixRight[0].size(); j++) {
            for (int k = 0; k < matrixLeft[0].size(); k++) {
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

    if (matrix.size() == 0) {
        throw std::invalid_argument("Matrix is empty");
    }

    for (int index = 1; index < matrix.size(); index++) {
        if (matrix[index].size() != matrix[0].size()) {
            throw std::invalid_argument(
                "Vector which represent matrix is NOT square");
        }
    }

    if (exponent < 0) {
        throw std::invalid_argument(
            "This method is NOT designed to power matrix into negative exponent");
    }


    if (exponent == 0) {
        int n = matrix.size();
        std::vector<std::vector<int64_t>> matrixE(
            matrix.size(), std::vector<int64_t>(matrix.size(), 0));

        for (int i = 0; i < matrix.size(); i++) {
            matrixE[i][i] = 1;
        }

        return matrixE;
    }

    std::vector<std::vector<int64_t>> answerMatrix;
    if (exponent % 2 == 0) {
        answerMatrix = powerMatrix(matrix, exponent/2);
        return multiplyMatrices(answerMatrix, answerMatrix);
    }else {
        answerMatrix = multiplyMatrices(
            powerMatrix(matrix, exponent-1), matrix);
    }
    return answerMatrix;
}

int64_t getNumberOfWays(
    const std::vector<std::vector<int64_t>>& matrix,
    const int64_t amountOfSteps){

    int n = matrix.size();
    std::vector<std::vector<int64_t>> answMatrix =
            powerMatrix(matrix, amountOfSteps);

    int answer = 0;
    for (int index = 0; index < matrix.size(); index++) {
        answer += answMatrix[0][index];
        answer %= MODULUS;
    }
    return answer;
}


signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    const InputData input = inputRead(std::cin);

    const int64_t result =
            getNumberOfWays(input.matrix, input.amountOfSteps);
    writeAnswer(std::cout, result);

    return 0;
}
