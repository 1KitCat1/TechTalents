#include <iostream>
#include <vector>
#include <algorithm>
/*Author: _KitCat_*/
/*Riabtsev Denis*/

const int NEGATIVE_INFINITY = -2100000000;
const int SHIFT = 1;
class SegmentTree2D {
 private:
    int amountOfRows, amountOfColumns;
    std::vector<std::vector<int>> tree;

 public:
    SegmentTree2D(int amountOfRows, int amountOfColumns) {
        this->amountOfRows = amountOfRows;
        this->amountOfColumns = amountOfColumns;
        int maximalSide = std::max(amountOfRows, amountOfColumns);
        int treeSize = 1;
        while (treeSize <= maximalSide) {
            treeSize *= 2;
        }
        treeSize *= 2;
        ++treeSize;
        tree = std::vector<std::vector<int>>
            (treeSize, std::vector<int>(treeSize));
    }

    void buildColumns(const std::vector<std::vector<int>>& matrix,
        const int vertexRow, const int leftRow, const int rightRow,
        const int vertexColumn, const int leftColumn, const int rightColumn) {
        if (leftColumn == rightColumn) {
            if (leftRow == rightRow) {
                if (leftRow < 0 || leftRow >= matrix.size()) {
                    throw std::invalid_argument("Index out of matrix range");
                }
                if (rightRow < 0 || !matrix.size()
                    || rightRow >= matrix[0].size()) {
                    throw std::invalid_argument("Index out of matrix range");
                }
                tree[vertexRow][vertexColumn] = matrix[leftRow][leftColumn];
            } else {
                tree[vertexRow][vertexColumn] = std::max(
                    tree[vertexRow*2][vertexColumn],
                    tree[vertexRow*2+1][vertexColumn]);
            }
        } else {
            int middleColumn = (leftColumn + rightColumn) / 2;
            buildColumns(matrix, vertexRow, leftRow,
                rightRow, vertexColumn * 2, leftColumn, middleColumn);
            buildColumns(matrix, vertexRow, leftRow,
                rightRow, vertexColumn * 2 + 1, middleColumn+1, rightColumn);
            tree[vertexRow][vertexColumn] = std::max(
                tree[vertexRow][vertexColumn * 2],
                tree[vertexRow][vertexColumn * 2 + 1]);
        }
    }

    void buildRows(const std::vector<std::vector<int>>& matrix,
         const int vertexRow, const int leftRow, const int rightRow) {
        if (leftRow != rightRow) {
            int middleRow = (leftRow + rightRow) / 2;
            buildRows(matrix, vertexRow * 2, leftRow, middleRow);
            buildRows(matrix, vertexRow * 2 + 1, middleRow + 1, rightRow);
        }
        buildColumns(matrix, vertexRow, leftRow,
            rightRow, 1, 0, amountOfColumns - 1);
    }

    int maxColumns(const int vertexRow, const int vertexColumn,
        const int currentLeftColumn, const int currentRightColumn,
        const  int leftColumn, const  int rightColumn) {
        if (leftColumn > rightColumn) {
            return NEGATIVE_INFINITY;
        }
        if (leftColumn == currentLeftColumn
         && currentRightColumn == rightColumn) {
            return tree[vertexRow][vertexColumn];
        }

        const int currentMiddleColumn =
            (currentLeftColumn + currentRightColumn) / 2;
        const int maxLeftColumn = std::max(
                    leftColumn,
                    currentMiddleColumn + 1);
        return std::max(
            maxColumns(vertexRow, vertexColumn * 2, currentLeftColumn,
                currentMiddleColumn, leftColumn,
                std::min(rightColumn, currentMiddleColumn)),
            maxColumns(vertexRow, vertexColumn * 2 + 1, currentMiddleColumn + 1,
                currentRightColumn, maxLeftColumn,
                    rightColumn));
    }

    int maxRows(const int vertexRow, const int currentLeftRow,
        const int currentRightRow, const int leftRow, const int rightRow,
        const int leftColumn, const int rightColumn) {
        if (leftRow > rightRow) {
            return NEGATIVE_INFINITY;
        }
        if (leftRow == currentLeftRow && currentRightRow == rightRow) {
            return maxColumns(vertexRow, 1, 0, amountOfColumns - 1,
                leftColumn, rightColumn);
        }

        const int currentMiddleRow = (currentLeftRow + currentRightRow) / 2;
        const int maxLeftRow = std::max(leftRow, currentMiddleRow + 1); 
        return std::max(
                    maxRows(vertexRow * 2, currentLeftRow, currentMiddleRow,
                        leftRow, std::min(rightRow, currentMiddleRow),
                        leftColumn, rightColumn),
                    maxRows(vertexRow * 2 + 1, currentMiddleRow + 1,
                        currentRightRow, maxLeftRow, rightRow,
                        leftColumn, rightColumn));
    }

    void updateColumns(const int vertexRow, const int leftRow,
        const int rightRow, const int vertexColumn, const int leftColumn,
        const int rightColumn, const int rowUpdating,
        const int columnUpdating, const int value) {
        if (leftColumn == rightColumn) {
            if (leftRow == rightRow){
                tree[vertexRow][vertexColumn] = value;
            } else{
                tree[vertexRow][vertexColumn] = std::max(
                    tree[vertexRow * 2][vertexColumn],
                    tree[vertexRow * 2 + 1][vertexColumn]);
            }

        } else {
            const int middleColumn = (leftColumn + rightColumn) / 2;
            if (columnUpdating <= middleColumn) {
                updateColumns(vertexRow, leftRow, rightRow, vertexColumn * 2,
                    leftColumn, middleColumn, rowUpdating, columnUpdating,
                    value);
            } else {
                updateColumns(vertexRow, leftRow, rightRow,
                    vertexColumn * 2 + 1, middleColumn + 1,
                    rightColumn, rowUpdating,
                    columnUpdating, value);
            }
            tree[vertexRow][vertexColumn] = std::max(
                tree[vertexRow][vertexColumn * 2],
                tree[vertexRow][vertexColumn * 2 + 1]);
        }
    }

    void updateRows(const int vertexRow, const int leftRow, const int rightRow,
        const int rowUpdating, const int columnUpdating, const int value) {
            if (leftRow != rightRow) {
            int middleRow = (leftRow + rightRow) / 2;
            if (rowUpdating <= middleRow) {
                updateRows(vertexRow * 2, leftRow, middleRow, rowUpdating,
                    columnUpdating, value);
            } else {
                updateRows(vertexRow * 2 + 1, middleRow + 1, rightRow, rowUpdating,
                    columnUpdating, value);
            }
        }
        updateColumns(vertexRow, leftRow, rightRow, 1, 0,
            amountOfColumns - 1, rowUpdating, columnUpdating, value);
    }
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
     const int fromColumn, const int toColumn) {
        this->fromRow = fromRow;
        this->toRow = toRow;
        this->fromColumn = fromColumn;
        this->toColumn = toColumn;
        this->type = 0;
    }
    Query(const int row, const int column, const int value) {
        this->row = row;
        this->column = column;
        this->value = value;
        this->type = 1;
    }
};

struct InputData {
    int amountOfRows;
    int amountOfColumns;
    int amountOfQueries;
    std::vector<std::vector<int>> matrix;
    std::vector<Query*> queries;
};

InputData* readProblemData(std::istream& in) {
    InputData* input = new InputData();
    in >> input->amountOfRows >>
        input->amountOfColumns >> input->amountOfQueries;

    input->matrix = std::vector<std::vector<int>>(
        input->amountOfRows, std::vector<int>(input->amountOfColumns));
    for (int indexRow = 0; indexRow < input->amountOfRows; ++indexRow) {
        for (int indexColumn = 0; indexColumn < input->amountOfColumns;
            ++indexColumn) {
            in >> input->matrix[indexRow][indexColumn];
        }
    }
    for (int index = 0; index < input->amountOfQueries; ++index) {
        char type;
        in >> type;
        if (type == '?') {
            int fromRow, toRow, fromColumn, toColumn;
            in >> fromRow >> toRow >> fromColumn >> toColumn;
            input->queries.push_back(
                new Query(fromRow, toRow, fromColumn, toColumn));
        } else {
            int row, column, value;
            in >> row >> column >> value;
            input->queries.push_back(
                new Query(row, column, value));
        }
    }
    return input;
}

std::vector<int> answerQueries(const InputData* inputData) {
    SegmentTree2D segmentTree(
        inputData->amountOfRows, inputData->amountOfColumns);
    segmentTree.buildRows(
        inputData->matrix, 1, 0, (inputData->amountOfRows) - 1);
    std::vector<int> answer;
    for (auto query : inputData->queries) {
        if (query->type) {
            const int row = query->row - SHIFT;
            const int column = query->column - SHIFT;
            const int value = query->value;
            segmentTree.updateRows(
                1, 0, (inputData->amountOfRows) - 1, row,
                column, value);
        } else {
            const int fromRow = query->fromRow - SHIFT;
            const int toRow = query->toRow - SHIFT;
            const int fromColumn = query->fromColumn - SHIFT;
            const int toColumn = query->toColumn - SHIFT;

            answer.push_back(segmentTree.maxRows(
                1, 0, (inputData->amountOfRows) - 1, fromRow,
                toRow, fromColumn, toColumn));
        }
    }
    return answer;
}

void writeAnswerQueries(std::ostream& out,
    const std::vector<int>& outputData) {
    for (auto value : outputData) {
        out << value << '\n';
    }
}

signed main() {
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(0);

    const InputData* inputData = readProblemData(std::cin);

    const std::vector<int> answer = answerQueries(inputData);
    writeAnswerQueries(std::cout, answer);
    return 0;
}
