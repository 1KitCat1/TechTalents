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

     int findParent(const int node) {
        if (node == parent[node]) {
            return node;
        }
        int newParent = findParent(parent[node]);
        int newDelta = deltaFromParent[parent[node]] + deltaFromParent[node];

        parent[node] = newParent;
        deltaFromParent[node] = newDelta;
        parentValues[newParent] =
            std::max(parentValues[newParent], -1*newDelta);
        return parent[node];
     }

 public:
    explicit DisjointSet(const int amountOfNodes) {
        parent = std::vector<int>(amountOfNodes);
        deltaFromParent = std::vector<int>(amountOfNodes, 0);
        parentValues = std::vector<int>(amountOfNodes, 0);

        for (int index = 0; index < amountOfNodes; index++) {
            parent[index] = index;
        }
    }

    bool join(int firstNode, int secondNode, int deltaBetweenNodes) {
        int parentFirstNode = findParent(firstNode);
        int parentSecondNode = findParent(secondNode);

        if (parentSecondNode > parentFirstNode) {
            std::swap(firstNode, secondNode);
            std::swap(parentFirstNode, parentSecondNode);
            deltaBetweenNodes *= -1;
        }
        int deltaFromParentFirstNode = deltaFromParent[firstNode];
        int deltaFromParentSecondNode = deltaFromParent[secondNode];
        int deltaBetweenParents = deltaFromParentSecondNode -
         deltaFromParentFirstNode + deltaBetweenNodes;

        parent[parentFirstNode] = parentSecondNode;

        parentValues[parentSecondNode] = std::max(parentValues[parentSecondNode],
            (-1)*(deltaBetweenParents-parentValues[parentFirstNode]));
        deltaFromParent[parentFirstNode] = deltaBetweenParents;

        if (parentValues[0] != 0) {
            return false;
        }
        return true;
    }

    bool areNodesInDifferentSet(const int firstNode, const int secondNode) {
        return findParent(firstNode) != findParent(secondNode);
    }

    int getDeltaFromParent(const int node) {
        return deltaFromParent[node];
    }

    std::vector<int> getCoinsDistribution() {
        std::vector<int> answer;
        for (int index = 0; index < parent.size(); index++) {
            int parentOfNode = findParent(index);
            int value = parentValues[parentOfNode] + deltaFromParent[index];
            answer.push_back(value);
        }
        return answer;
    }
};

OutputData countCoinsAmount(const InputData& input) {
    OutputData out;
    DisjointSet disjointSet(input.amountOfNodes);
    for (int index = 0; index < input.amountOfEdges; index++) {
        int firstNode = input.firstNode[index], secondNode = input.secondNode[index],
            deltaBetweenNodes = input.deltaBetweenNodes[index];
            
        if (disjointSet.areNodesInDifferentSet(firstNode, secondNode)) {
            bool noErrorOccured =
             disjointSet.join(firstNode, secondNode, deltaBetweenNodes);

            if (noErrorOccured != true) {
                out.couldDistribute = false;
                out.errorOccuredOn = index+1;
                return out;
            }
        } else {
            int deltaA = disjointSet.getDeltaFromParent(firstNode);
            int deltaB = disjointSet.getDeltaFromParent(secondNode);
            if (deltaA != deltaB + deltaBetweenNodes) {
                out.couldDistribute = false;
                out.errorOccuredOn = index+1;
                return out;
            }
        }
    }
    out.coinsDistribution = disjointSet.getCoinsDistribution();
    out.couldDistribute = true;
    return out;
}

InputData readInfoCoinsDistribution(std::istream& in) {
    InputData input;
    in >> input.amountOfNodes >> input.amountOfEdges;
    input.firstNode = std::vector<int>(input.amountOfEdges);
    input.secondNode = std::vector<int>(input.amountOfEdges);
    input.deltaBetweenNodes = std::vector<int>(input.amountOfEdges);

    for (int index = 0; index < input.amountOfEdges; index++) {
        int firstNode, secondNode, deltaBetweenNodes;
        in >> firstNode >> secondNode >> deltaBetweenNodes;
        input.firstNode[index] = firstNode;
        input.secondNode[index] = secondNode;
        input.deltaBetweenNodes[index] = deltaBetweenNodes;
    }
    return input;
}

void writeCoinsDistribution(std::ostream& out, const OutputData& outputData) {
    if (outputData.couldDistribute) {
        out << "YES\n";
        for (int coinsInChest : outputData.coinsDistribution) {
            out << coinsInChest << ' ';
        }
    } else {
        out << "NO\n";
        out << outputData.errorOccuredOn;
    }
}


int main() {
    const InputData distribution = readInfoCoinsDistribution(std::cin);
    const OutputData result = countCoinsAmount(distribution);
    writeCoinsDistribution(std::cout, result);

    return 0;
}
