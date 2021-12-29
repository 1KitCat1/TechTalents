#include <iostream>
#include <vector>
/*Author: _KitCat_*/
/*Riabtsev Denis*/

    
const int NEGATIVE_INFINITY = -2100000000;

class SegmentTree2D{
 private:    
    const int amountOfRows, amountOfColumns;
    std::vector<std::vector<int>> tree;
    std::vector<std::vector<int>> matrix;
    
 public:
    SegmentTree2D(int amountOfRows, int amountOfColumns);
    
    void buildColumns(const int vertexRow, const int leftRow, const int rightRow,
        const int vertexColumn, const int leftColumn, const int rightColumn);

    void buildRows(const int vertexRow, const int leftRow, const int rightRow);

    int maxColumns(const int vertexRow, const int vertexColumn, const int currentLeftColumn,
        const int currentRightColumn, const int leftColumn, const int rightColumn);

    int maxRows(const int vertexRow, const int currentLeftX, const int currentRightRow,
        const int leftRow, const int rightRow, const int leftColumn, const int rightColumn);

    void updateColumns(const int vertexRow, const int leftRow, const int rightRow, const int vertexColumn,
        const int leftColumn, const int rightColumn, const int rowUpdating, const int columnUpdating, const int value);
     
    void updateRows(const int vertexRow, const int leftRow, const int rightRow, const int rowUpdating,
        const int columnUpdating, const int value);
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
    std::vector<std::vector<int>> matrix;
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
