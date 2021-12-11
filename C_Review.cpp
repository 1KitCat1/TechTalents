#include <bits/stdc++.h>
/*Author: _KitCat_*/
#pragma GCC optimize("O3")


#define int int64_t
#define f first
#define s second

#define Matrix std::vector<std::vector<int>>
// using namespace std;

const int mod = 1e9+7;

Matrix multiplyMatrix(Matrix matrix1, Matrix matrix2){
    int n = matrix1.size();
    Matrix answ(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                answ[i][j] += (matrix1[i][k]*matrix2[k][j]) % mod;
                answ[i][j] %= mod;
            }
        }
    }
    return answ;
}

Matrix powerMatrix(Matrix matrix, int ex){
    if (ex == 0) {
        int n = matrix.size();
        Matrix one(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            one[i][i] = 1;
        }
        return one;
    }
    if (ex % 2 == 0) {
        matrix = powerMatrix(matrix, ex/2);
        return multiplyMatrix(matrix, matrix);
    }else {
        matrix = multiplyMatrix(powerMatrix(matrix, ex-1), matrix);
    }
    return matrix;
}


// int brute(Matrix& matrix, int k){
//     int answ = 0;
//     int n = matrix.size();
//     std::queue<std::pair<int, int>> Q;
//     Q.push({0, 0});
//     while(!Q.empty()){
//         std::pair<int, int> current = Q.front();
//         if(current.s == k) break;
//         Q.pop();

//         for(int i = 0; i < n; i++){
//             for(int val = 0; val < matrix[current.f][i]; val++){
//                 Q.push({i, current.s+1});
//             }
//         }
//     }
//     return Q.size();

// }

int solve(Matrix matrix, int k){
    int n = matrix.size();
    matrix = powerMatrix(matrix, k);
    int answ = 0;
    for (int i = 0; i < n; i++) {
        answ += matrix[0][i];
        answ %= mod;
    }
    return answ;
}


signed main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    Matrix matrix(n, std::vector<int>(n));

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        matrix[a][b]++;
    }
    std::cout << solve(matrix, k) << '\n';
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cin >> matrix[i][j];
    //     }
    // }

    // int randomSeed;
    // std::cin >> randomSeed;
    // STRESS TEST
    // int countTestsGood = 0, countTestsBad = 0;
    // for(int test = 0; test < 1500; test++){
    //     int n = getRandom(test+randomSeed, test+9, 4)+1;
    //     int m = getRandom(test, n+randomSeed, 50);
    //     std::cout << n << ' ' << m << std::endl;
    //     Matrix matrix(n, std::vector<int>(n));
    //     for(int i = 0; i < m; i++){
    //         int a = getRandom(test+randomSeed, i, n);
    //         int b = getRandom(i, a, n);
    //         // std::cout << a << ' ' << b << std::endl;
    //         matrix[a][b]++;
    //     }
    //     int k = getRandom(test, m, 4)+1;
    //     // std::cout << n << ' '<< m << ' ' << k << std::endl;
    //     int answ1 = solve(matrix, k);
    //     int answ2 = brute(matrix, k);
    //     if(answ1 != answ2){
    //         std::cout << std::endl<< "!!!TEST FAILED: " << answ1
    // << " != " << answ2 << std::endl << std::endl;
    //         countTestsBad++;
    //     }else{
    //         std::cout << "Test #" << test+1 << " passed" << std::endl;
    //         countTestsGood++;
    //     }

    // }
    // std::cout << "All tests " << countTestsBad + countTestsGood << '\n';
    // std::cout << "Passed " << countTestsGood << '\n';
    // std::cout << "Failed " << countTestsBad << '\n';


    // STRESS OVER
    return 0;
}
