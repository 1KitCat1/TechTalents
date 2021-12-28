#include <bits/stdc++.h>
/*Author: _KitCat_*/
/*Riabtsev Denis*/

#pragma GCC optimize("O3")

// using namespace std;

class SegmentTree2D{
 private:    
    const int amountOfRows, amountOfColumns;
    std::vector<std::vector<int>> tree;
    std::vector<std::vector<int>> matrix;
    const int NEGATIVE_INFINITE = -2100000000;
 public:
    SegmentTree2D(int amountOfRows, int amountOfColumns);
    
    void buildY(const int vertexX, const int leftX, const int rightX, const int vertexY, 
        const int leftY, const int rightY);

    void buildX(const int vertexX, const int leftX, const int rightX);

    int maxY(const int vertexX, const int vertexY, const int tLeftY, const int tRightY,
        const int leftY, const int rightY);

    int maxX(const int vertexX, const int currentLeftX, const int currentRightX, const int leftX,
        const int rightX, const int leftY, const int rightY);

    void updateY(const int vertexX, const int leftX, const int rightX, const int vertexY,
        const int leftY, const int rightY, const int x, const int y, const int value);
     
    void updateX(const int vertexX, const int leftX, const int rightX, const int x,
        const int y, const int value);
};

struct Query{
    const bool type;
    const int fromRow;
    const int fromColumn;
    const int toRow;
    const int toColumn;
    const int row;
    const int column;
    const int value;
};

struct InputData{
    const int amountOfRows;
    const int amountOfColumns;
    const int amountOfQueries;
    SegmentTree2D* segmentTree;
    std::vector<Query> queries;
};

InputData readProblemData(std::istream& in);

std::vector<int> answerQueries(const InputData& inputData);

void writeAnswerQueries(std::ostream& out, const std::vector<int>& outputData);

signed main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(0);

    const InputData inputData = readProblemData(std::cin);
    std::vector<int> answer = answerQueries(inputData);
    writeAnswerQueries(std::cout, answer);
    return 0;
}
