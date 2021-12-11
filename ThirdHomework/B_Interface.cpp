#include <bits/stdc++.h>

struct InputData{
	int amountOfNodes, amountOfEdges;
	std::vector<int> firstNode;
	std::vector<int> secondNode;
	std::vector<int> deltaBetweenNodes;	
};

struct DisjointSet{
 	std::vector<int> parent;
 	std::vector<int> deltaFromParent;
 	std::vector<int> parentValues;

 	DisjointSet(int n);
 	void join(int firstNode, int secondNode, int deltaBetweenNodes);
 	int findParent(int node);
 	bool check(int firstNode, int secondNode);
 	std::vector<int> getAnswer();
};

std::pair<bool, std::vector<int>> countAmountInBarrels(const InputData& input);

InputData inputRead(std::istream& in);

void writeAnswer(std::ostream& out, const std::pair<bool, std::vector<int>>& outData);


signed main() {
	const InputData input = inputRead(std::cin);
    const std::pair<bool, std::vector<int>> result = countAmountInBarrels(input);
    writeAnswer(std::cout, result);

	return 0;
}