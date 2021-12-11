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
    bool haveWeFind;
    std::vector<int> verdictData;
};

class DisjointSet {
 private:
     std::vector<int> parent;
     std::vector<int> deltaFromParent;
     std::vector<int> parentValues;

     int findParent(const int node);

 public:
    DisjointSet(const int amountOfNodes);

    void join(const int firstNode, const int secondNode, const int deltaBetweenNodes);

    bool areNodesInSameSet(const int firstNode, const int secondNode);

    int getDeltaFromParent(const int node);

    std::vector<int> getAmountOfGold();
};

OutputData countCoinsAmount(const InputData& input);

InputData readInfoCoinsDistribution(std::istream& in);

void writeCoinsDistribution(std::ostream& out, const OutputData& outputData);


int main() {
    const InputData distribution = readInfoCoinsDistribution(std::cin);
    const OutputData result = countCoinsAmount(distribution);
    writeCoinsDistribution(std::cout, result);

    return 0;
}