#include <bits/stdc++.h>

#define int int64_t

#define Matrix std::vector<std::vector<int>>

constexpr int MODULUS = 1000000007;

Matrix multiplyMatrix(Matrix matrix1, Matrix matrix2);

Matrix powerMatrix(Matrix matrix, int exponent);

int getNumberOfWays(Matrix matrix, int k);

signed main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    Matrix matrix(n, std::vector<int>(n));

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        matrix[a-1][b-1]++;
    }
    std::cout << getNumberOfWays(matrix, k) << '\n';

    return 0;
}
