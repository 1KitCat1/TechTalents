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

     int findParent(const int node){
        if (node == parent[node]) return node;
        int newParent = findParent(parent[node]);
        int newDelta = deltaFromParent[parent[node]] + deltaFromParent[node];
        parent[node] = newParent;
        deltaFromParent[node] = newDelta;
        parentValues[newParent] = 
            std::max(parentValues[newParent], -1*newDelta);
        return parent[node];
     }

 public:
    explicit DisjointSet(const int amountOfNodes){
        parent = std::vector<int>(amountOfNodes);
        deltaFromParent = std::vector<int>(amountOfNodes, 0);
        parentValues = std::vector<int>(amountOfNodes, 0);
        for (int i = 0; i < amountOfNodes; i++) parent[i] = i;
    }

    bool join(int firstNode, int secondNode, int deltaBetweenNodes){
        int parentA = findParent(firstNode);
        int parentB = findParent(secondNode);
        if (parentB > parentA){
            std::swap(firstNode, secondNode);
            std::swap(parentA, parentB);
            deltaBetweenNodes *= -1;
        }
        int deltaA = deltaFromParent[firstNode];
        int deltaB = deltaFromParent[secondNode];
        int deltaXY = deltaB - deltaA + deltaBetweenNodes; 
        parent[parentA] = parentB;
        parentValues[parentB] = std::max(parentValues[parentB],
            -1*(deltaXY-parentValues[parentA]));
        deltaFromParent[parentA] = deltaXY;
        if (parentValues[0] != 0){
            return false;
        }
        return true;
    }

    bool areNodesInDifferentSet(const int firstNode, const int secondNode){
        return findParent(firstNode) != findParent(secondNode);
    }

    int getDeltaFromParent(const int node){
        return deltaFromParent[node];
    }

    std::vector<int> getCoinsDistribution(){
        std::vector<int> answ;
        for (int i = 0; i < parent.size(); i++) {
            int p = findParent(i);
            int value = parentValues[p] + deltaFromParent[i];
            answ.push_back(value);
        }
        return answ;
    }
};

OutputData countCoinsAmount(const InputData& input){
    OutputData out;
    DisjointSet ds(input.amountOfNodes);
    for (int i = 0; i < input.amountOfEdges; i++){
        int a = input.firstNode[i], b = input.secondNode[i], 
            delta = input.deltaBetweenNodes[i];
        if (ds.areNodesInDifferentSet(a, b)){
            bool isGood = ds.join(a, b, delta);
            if (!isGood){
                out.couldDistribute = false;
                out.errorOccuredOn = i+1;
                return out;
            }
        } else {
            int deltaA = ds.getDeltaFromParent(a);
            int deltaB = ds.getDeltaFromParent(b);
            if (deltaA != deltaB + delta){
                out.couldDistribute = false;
                out.errorOccuredOn = i+1;
                return out;
            }
        }
    }
    out.coinsDistribution = ds.getCoinsDistribution();
    out.couldDistribute = true;
    return out;
}

InputData readInfoCoinsDistribution(std::istream& in){
    InputData input;
    in >> input.amountOfNodes >> input.amountOfEdges;
    input.firstNode = std::vector<int>(input.amountOfEdges);
    input.secondNode = std::vector<int>(input.amountOfEdges);
    input.deltaBetweenNodes = std::vector<int>(input.amountOfEdges);

    for (int i = 0; i < input.amountOfEdges; i++){
        int a, b, c;
        in >> a >> b >> c;
        input.firstNode[i] = a;
        input.secondNode[i] = b;
        input.deltaBetweenNodes[i] = c;
    }
    return input;
}

void writeCoinsDistribution(std::ostream& out, const OutputData& outputData){
    if (outputData.couldDistribute){
        out << "YES\n";
        for (int coinsInChest : outputData.coinsDistribution){
            out << coinsInChest << ' ';
        }
    } else{
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
