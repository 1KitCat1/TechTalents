#include <iostream>
#include <vector>
#include <algorithm>
/*Author: _KitCat_*/
/*Riabtsev Denis*/

const int NEGATIVE_INFINITY = -2100000000;

class SegmentTree2D{
 private:
    int amountOfRows, amountOfColumns;
    std::vector<std::vector<int>> tree;

 public:
    SegmentTree2D(int amountOfRows, int amountOfColumns);

    void buildColumns(const std::vector<std::vector<int>>& matrix,
        const int vertexRow, const int leftRow, const int rightRow,
        const int vertexColumn, const int leftColumn, const int rightColumn);

    void buildRows(const std::vector<std::vector<int>>& matrix,
         const int vertexRow, const int leftRow, const int rightRow);

    int maxColumns(const int vertexRow, const int vertexColumn,
        const int currentLeftColumn, const int currentRightColumn,
        const  int leftColumn, const  int rightColumn);

    int maxRows(const int vertexRow, const int currentLeftRow,
        const int currentRightRow, const int leftRow, const int rightRow,
        const int leftColumn, const int rightColumn);

    void updateColumns(const int vertexRow, const int leftRow,
        const int rightRow, const int vertexColumn, const int leftColumn,
        const int rightColumn, const int rowUpdating,
        const int columnUpdating, const int value);

    void updateRows(const int vertexRow, const int leftRow, const int rightRow,
        const int rowUpdating, const int columnUpdating, const int value);
};

class Query{
 public:
    bool type;
    int fromRow;
    int fromColumn;
    int toRow;
    int toColumn;
    int row;
    int column;
    int value;
    Query(const int fromRow, const int toRow,
     const int fromColumn, const int toColumn);
    Query(const int row, const int column, const int value);
};

struct InputData {
    int amountOfRows;
    int amountOfColumns;
    int amountOfQueries;
    std::vector<std::vector<int>> matrix;
    std::vector<Query*> queries;
};

InputData* readProblemData(std::istream& in);

std::vector<int> answerQueries(const InputData* inputData);

void writeAnswerQueries(std::ostream& out, const std::vector<int>& outputData);

signed main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(0);

    const InputData* inputData = readProblemData(std::cin);

    const std::vector<int> answer = answerQueries(inputData);
    writeAnswerQueries(std::cout, answer);
    return 0;
}
