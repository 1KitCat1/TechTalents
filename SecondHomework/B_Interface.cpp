#include <bits/stdc++.h>


std::vector<int> initialiseCombination(const std::vector<int>& weightsOfGoods,
 int64_t amountOfGoods, int64_t startPosition);

void inputData(std::istream& in, int& amountOfGoods, int& maxWeight, 
	const std::vector<int>& weightsOfGoods);

void outputData(std::ostream& out, int64_t result);

void solve(){
	int amountOfGoods, maxWeight;
	std::vector<int> weightsOfGoods(amountOfGoods);

	leftComb = vi(1 << (n/2));
	rightComb = vi(1 << (n-n/2));
	
	initLeftComb(arr, n/2, 0);
	initRightComb(arr, n-n/2, n/2);

	std::sort(all(rightComb));

	int answ = 0;

	for (int i = 0; i < leftComb.size(); i++) {
		if (leftComb[i] <= C) {
			int pointer = std::upper_bound(all(rightComb), C-leftComb[i])
					 - rightComb.begin();

			if (pointer == rightComb.size() 
				|| rightComb[pointer] != (C-leftComb[i])) {
				pointer--;
			}
				
			answ += pointer + 1;		
		}
	}
	std::cout << answ;
}

signed main(){
	// TESTS
	solve();

	return 0;
}
