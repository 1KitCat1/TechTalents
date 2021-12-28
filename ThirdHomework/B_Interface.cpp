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
    bool couldDistribute;
    std::vector<int> coinsDistribution;
    int errorOccuredOn;
};

class DisjointSet {
 private:
     std::vector<int> parent;
     std::vector<int> deltaFromParent;
     std::vector<int> parentValues;

     int findParent(const int node);

 public:
    DisjointSet(const int amountOfNodes);

    bool join(const int firstNode, const int secondNode, const int deltaBetweenNodes);

    bool areNodesInDifferentSet(const int firstNode, const int secondNode);

    int getDeltaFromParent(const int node);

    std::vector<int> getCoinsDistribution();
};

OutputData countCoinsAmount(const InputData& input);

InputData readCoinsDistributionData(std::istream& in);

void writeCoinsDistribution(std::ostream& out, const OutputData& outputData);


int main() {
    const InputData distribution = readCoinsDistributionData(std::cin);
    const OutputData result = countCoinsAmount(distribution);
    writeCoinsDistribution(std::cout, result);

    return 0;
}