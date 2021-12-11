#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

struct InputData {
    int amountOfNodes, amountOfEdges;
    std::vector<int> firstNode;
    std::vector<int> secondNode;
    std::vector<int> deltaBetweenNodes; 
};

struct OutputData {
    bool problemVerdict;
    std::vector<int> verdictData;
};

class DisjointSet {
 private:
     std::vector<int> parent;
     std::vector<int> deltaFromParent;
     std::vector<int> parentValues;

 public:
    DisjointSet(const int amountOfNodes);
    void join(const int firstNode, const int secondNode, const int deltaBetweenNodes);
    int findParent(const int node);
    bool check(const int firstNode, const int secondNode);
    int getDeltaFromParent(const int node);
    std::vector<int> getAnswer();
};

OutputData countAmountInBarrels(const InputData& input);

InputData inputRead(std::istream& in);

void writeAnswer(std::ostream& out, const OutputData& outData);


signed main() {
    const InputData input = inputRead(std::cin);
    const OutputData result = countAmountInBarrels(input);
    writeAnswer(std::cout, result);

    return 0;
}